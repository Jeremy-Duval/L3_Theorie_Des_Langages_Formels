//******************************************************************************

#include <iostream>
#include <algorithm>
#include <string>

#include "Accept.h"
#include "FA_tools.h"

////////////////////////////////////////////////////////////////////////////////

bool EstDeterministe(const sAutoNDE& at)
{
    bool deterministe = true;
    unsigned int i,j;

    /*
    * Un automate est non-deterministe si :
    *     Il a des epsilon transition
    *     Il a plusieurs transition d'un point A à un point B avec la même lettre
    */
    i = 0;
    while((i<at.epsilon.size())&&(deterministe==true))
    {
        if(at.epsilon[i].size())
        {
            deterministe = false;
        }
        i++;
    }
    i = 0;
    while((i<at.trans.size())&&(deterministe==true))
    {
        j = 0;
        while((j<at.trans[i].size())&&(deterministe==true))
        {
            if(at.trans[i][j].size()>1)
            {
                deterministe = false;
            }
            j++;
        }
        i++;
    }

    return deterministe;
}

////////////////////////////////////////////////////////////////////////////////

void Fermeture(const sAutoNDE& at, etatset_t& e)
{

    symb_t c;
    etatset_t depuis_E_trans, e_prec;
    std::set<etat_t>::const_iterator itr;

    c = at.nb_symbs + ASCII_A;  //Calcule d'une lettre E-transition

    do
    {
        depuis_E_trans = e;
        e_prec = e;
        depuis_E_trans = Delta(at, e, c);   //On récupère les etat accessible depuis chaque état de e grâce à des E-transitions

        //on ajoute chaque élément de la liste obtenue à celle passée en pramètre
        for(itr = depuis_E_trans.begin(); itr!=depuis_E_trans.end(); itr++)
        {
            e.insert(*itr);
        }

    }
    while(e_prec.size()!=e.size());

}

////////////////////////////////////////////////////////////////////////////////

etatset_t Delta(const sAutoNDE& at, const etatset_t& e, symb_t c)
{

    std::set<etat_t>::const_iterator itr, itr2;
    unsigned int symb_ascii;
    etatset_t r;

    symb_ascii = c-(ASCII_A-1); //donne la place de la lettre dans l'alphabet (c-96)

    if(symb_ascii>at.nb_symbs)
    {
        //la lettre est une epsilon transition

        for(itr = e.begin(); itr!=e.end(); itr++)
        {
            if(*itr<at.epsilon.size())
            {
                if(at.epsilon[*itr].size()!=0)
                {
                    for(itr2 = at.epsilon[*itr].begin(); itr2!=at.epsilon[*itr].end(); itr2++)
                    {
                        r.insert(*itr2);
                    }
                }
            }
        }
    }
    else
    {
        //la lettre doit être taitée normalement

        for(itr = e.begin(); itr!=e.end(); itr++)
        {

            if(*itr<at.trans.size())
            {
                //itr2 = at.trans[*itr][symb_ascii-1].begin();
                if(at.trans[*itr][symb_ascii-1].size()!=0)
                {
                    for(itr2 = at.trans[*itr][symb_ascii-1].begin(); itr2!=at.trans[*itr][symb_ascii-1].end(); itr2++)
                    {
                        r.insert(*itr2);
                    }
                }
            }
        }

    }

    return r;
}

////////////////////////////////////////////////////////////////////////////////

bool Accept( sAutoNDE& at, std::string str)
{
    bool est_accepte;
    unsigned int i, place_ascii;
    char symb_ascii;
    etatset_t etat_accessible;
    std::set<etat_t>::const_iterator itr, itr2;

    //insertion de l'etat initial
    etat_accessible.insert(at.initial);
    Fermeture(at,etat_accessible);

    est_accepte = true;
    i=0;
    while((i<str.size())&&(est_accepte))
    {
        symb_ascii = str.at(i); //extraction d'une lettre
        place_ascii = symb_ascii-(ASCII_A-1); //donne la place de la lettre dans l'alphabet

        if(place_ascii<=at.nb_symbs) //dans le cas contraire, la lettre n'est pas reconnue comme E-transition
        {
            etat_accessible = Delta(at,etat_accessible,symb_ascii);
            Fermeture(at,etat_accessible);
        }
        else
        {
            est_accepte = false;
        }

        i++;
    }

    if(est_accepte) //si on a pas déjà reconnu une lettre non acceptée
    {
        //chercher si un des etat est final
        est_accepte = false;
        itr = etat_accessible.begin();
        while((itr!=etat_accessible.end())&&(est_accepte==false))
        {
            itr2 = at.finaux.begin();
            while((itr2!=at.finaux.end())&&(est_accepte==false))
            {
                if(*itr==*itr2)
                {
                    est_accepte = true;
                }
                itr2++;
            }
            itr++;
        }
    }







std::cout << "****************************************" <<std::endl;
std::cout << "****************************************" <<std::endl;
std::cout << "****************************************" <<std::endl;




    /* CODER DANS ACCEPT ; A LA FIN ! */

  std::string sr, A, B, C, D;
  unsigned int j, k;
  std::vector<etatset_t> tmp_vect_es;
  etatset_t tmp_es, tmp_copie_es;
  std::vector<std::vector<std::string>> transitions;
  std::vector<std::string> tmp_vect_str;
  bool trans_ijk;
    //unsigned int i;

  std::cout << "nb_etats : " << at.nb_etats <<std::endl;
  std::cout << "nb_symbs : " << at.nb_symbs <<std::endl;
  std::cout << "initial : " << at.initial <<std::endl;
  std::cout << "finaux : " << at.finaux <<std::endl;
  std::cout << "trans : " << at.trans <<std::endl;
  std::cout << "epsilon : " << at.epsilon <<std::endl;
  std::cout << "****************************************" <<std::endl;

  /* ******************************************************* */
  /* **********Arrangement de l'automate en entrée********** */
  /* ******************************************************* */

    /* ***Décalage des symbole et ajout d'un état de départ  générique***/
    at.nb_etats++;

    //décalage de at.trans
    i=0;
    while(i<at.nb_symbs)
    {
        tmp_vect_es.push_back(tmp_es);
        i++;
    }
    at.trans.insert(at.trans.begin(),tmp_vect_es);
    std::cout<<"at.trans : "<<at.trans<<std::endl;

    //décalage des e-trans
    auto itr_ie=at.epsilon.begin();
    i=0;
    while(itr_ie<at.epsilon.end())
    {

            //init etat_set
            tmp_copie_es.clear();

            auto itr_set=at.epsilon[i].begin();
            while(itr_set!=at.epsilon[i].end())
            {
                tmp_copie_es.insert(itr_set,*itr_set+1);
                itr_set++;

            }

        //clean at.trans[i][j]
        at.epsilon.erase(itr_ie);
        at.epsilon.insert(itr_ie,tmp_copie_es);
        i++;
        itr_ie++;
    }
    std::cout << "epsilon : " << at.epsilon <<std::endl;
    //on ajoute la E-transition du nouvel état de départ vers l'ancien
    tmp_es.insert(at.initial+1);
    at.epsilon.insert(at.epsilon.begin(), tmp_es);
    std::cout << "epsilon : " << at.epsilon <<std::endl;

    at.initial=0;
    std::cout << "initial : " << at.initial <<std::endl;
    //on décale les liaisons
    auto itr_i=at.trans.begin();
    itr_i++;//on ne veux pas l'état qui viens d'être ajouté
    i=1;
    while(itr_i<at.trans.end())
    {
        tmp_vect_es.clear();
        j=0;
        while(j<at.trans[i].size())
        {
            //init etat_set
            tmp_copie_es.clear();

            auto itr_set=at.trans[i][j].begin();
            while(itr_set!=at.trans[i][j].end())
            {
                tmp_copie_es.insert(itr_set,*itr_set+1);
                itr_set++;

            }
            std::cout<<"at.trans["<<i<<"]["<<j<<"] : "<<at.trans[i][j]<<std::endl;
            std::cout<<"tmp_copie_es : "<<tmp_copie_es<<std::endl;

            //re insere nouveau etat_set
            tmp_vect_es.push_back(tmp_copie_es);
            j++;
        }
        //clean at.trans[i][j]
        at.trans.erase(itr_i);
        //remplacement de l'ancien vecteur d'etat_set
        at.trans.insert(itr_i,tmp_vect_es);
        //std::cout<<"tmp_vect_es : "<<tmp_vect_es<<std::endl;
        i++;
        itr_i++;
    }
    std::cout<<"at.trans : "<<at.trans<<std::endl;

    //ajout de l'état final générique
    at.nb_etats++;

    tmp_es.clear();
    tmp_vect_es.clear();
    i=0;
    while(i<at.nb_symbs)
    {
        tmp_vect_es.push_back(tmp_es);
        i++;
    }
    at.trans.insert(at.trans.end(),tmp_vect_es);
    std::cout<<"at.trans : "<<at.trans<<std::endl;


    at.epsilon.insert(at.epsilon.end(), tmp_es);

    //ajout d'une e-transition des anciens etats finaux vers le nouveau
    auto itr_finaux=at.finaux.begin();
    while(itr_finaux!=at.finaux.end())
    {
        at.epsilon[*itr_finaux+1].insert(at.epsilon[*itr_finaux+1].end(),at.nb_etats-1);//le +1 est là à cause du décalage fait précedemment pour ajouter l'état de départ générique ; at.trans et at.epsilon ont été mis à jour mais pas at.finaux
        itr_finaux++;
    }
    std::cout << "epsilon : " << at.epsilon <<std::endl;

    //mise à jour de at.nb_finaux et at.finaux
    std::cout << "nb_finaux : " << at.nb_finaux <<std::endl;
    std::cout << "at.finaux : " << at.finaux <<std::endl;
    at.nb_finaux=1;
    at.finaux.clear();
    at.finaux.insert(at.finaux.begin(), at.nb_etats-1);
    std::cout << "nb_finaux : " << at.nb_finaux <<std::endl;
    std::cout << "at.finaux : " << at.finaux <<std::endl;


    /* ******************************************************* */
    /* *******Construction de l'expression rationnelle ******* */
    /* ******************************************************* */

    //initialisation de la matrice
    //-1
    i=0;
    while(i<at.nb_etats)
    {
        tmp_vect_str.push_back("-1");
        i++;
    }
    i=0;
    while(i<at.nb_etats)
    {
        transitions.push_back(tmp_vect_str);
        i++;
    }
    //ajout des transition
    i=0;
    while(i<at.nb_etats)
    {
        j=0;
        while(j<at.nb_symbs)
        {
            auto itr_set=at.trans[i][j].begin();
            while(itr_set!=at.trans[i][j].end())
            {
                transitions[i][*itr_set]=j+ASCII_A;
                itr_set++;

            }
            j++;
        }
        i++;
    }
    //ajout des e-transition
    i=0;
    while(i<at.nb_etats)
    {
        auto itr_set=at.epsilon[i].begin();
        while(itr_set!=at.epsilon[i].end())
        {
            transitions[i][*itr_set]="E";
            itr_set++;
        }
        i++;
    }

    std::cout << "transitions: " << transitions <<std::endl;

    i=0; //après arrangement, l'état initial sera toujours 0

    k=1;
    while(k<at.nb_etats-1)//k symbolise les état supprimables, on ne doit pas prendre le dernier, ni le premier
    {
        j=1;
        while(j<at.nb_etats)
        {
            if(j!=k)
            {
                std::cout << "----------" <<std::endl;
                std::cout << "transitions["<<i<<"]["<<k<<"]: " << transitions[i][k] <<std::endl;
                std::cout << "transitions["<<k<<"]["<<j<<"]: " << transitions[k][j] <<std::endl;
                //test l'existance d'une transition de i à j par k
                trans_ijk = false;
                if(transitions[i][k]!="-1")
                {
                    if(transitions[k][j]!="-1")
                    {
                        std::cout << "true" << std::endl;
                        trans_ijk=true;
                    }
                }
                if(trans_ijk)
                {
                    //transitions[i][j]=D|A.C*.B;
                    A="";
                    B="";
                    C="";
                    D="";
                    if(transitions[i][j]!="-1")
                    {
                        std::cout << "D" << std::endl;
                        D=transitions[i][j];
                    }
                    if(transitions[k][k]!="-1")
                    {
                        std::cout << "C" << std::endl;
                        C=transitions[k][k]+"*";
                    }
                    if(transitions[i][k]!="E")
                    {
                        std::cout << "A" << std::endl;
                        A=transitions[i][k];
                    }
                    if(transitions[k][j]!="E")
                    {
                        std::cout << "B" << std::endl;
                        B=transitions[k][j];
                    }

                    if(D!="")
                    {
                        transitions[i][j]=D;
                        if((A!="")||(B!="")||(C!=""))
                        {
                            transitions[i][j]=transitions[i][j]+"|";
                        }
                    }
                    else
                    {
                        transitions[i][j]="";
                    }
                    if(A!="")
                    {
                        transitions[i][j]=transitions[i][j]+A;
                        if((B!="")||(C!=""))
                        {
                            transitions[i][j]=transitions[i][j]+".";
                        }
                    }
                    if(C!="")
                    {
                        transitions[i][j]=transitions[i][j]+C;
                        if((B!=""))
                        {
                            transitions[i][j]=transitions[i][j]+".";
                        }
                    }
                    if(B!="")
                    {
                        transitions[i][j]=transitions[i][j]+B;
                    }
                    std::cout << "transitions[i][j] : "<< transitions[i][j] << std::endl;
                    setTransition(at.nb_etats, transitions, j, k);
                }
                //transitions[k][j]="-1";
                //transitions[j][k]="-1";
            }// end if(j!=k)
            j++;
        }// end while(j<at.nb_etats)
        transitions[k][k]=-1; //transition d'un etat vers lui-même
        j=0;
        while(j<at.nb_etats) //suppression des transition vers/depuis l'état k
        {
            transitions[k][j]="-1";
            transitions[i][k]="-1";
            j++;
        }
        k++;
    }// end while(k<at.nb_etats-1)

    sr = transitions[0][at.nb_etats-1];


    std::cout<<"Sr : "<<sr<<std::endl;











    return est_accepte;
}

////////////////////////////////////////////////////////////////////////////////

void setTransition(unsigned int nb_etats, std::vector<std::vector<std::string>> &transitions, unsigned int i, unsigned int k)
{
    std::string A, B, C, D;
    unsigned int j;
    bool trans_ijk;

     while(j<nb_etats)
        {
            if((j!=k)&&(j!=i))
            {
                std::cout << "__________" <<std::endl;
                std::cout << "transitions["<<i<<"]["<<k<<"]: " << transitions[i][k] <<std::endl;
                std::cout << "transitions["<<k<<"]["<<j<<"]: " << transitions[k][j] <<std::endl;
                //test l'existance d'une transition de i à j par k
                trans_ijk = false;
                if(transitions[i][k]!="-1")
                {
                    if(transitions[k][j]!="-1")
                    {
                        std::cout << "true" << std::endl;
                        trans_ijk=true;
                    }
                }
                if(trans_ijk)
                {
                    //transitions[i][j]=D|A.C*.B;
                    A="";
                    B="";
                    C="";
                    D="";
                    if(transitions[i][j]!="-1")
                    {
                        std::cout << "D" << std::endl;
                        D=transitions[i][j];
                    }
                    if(transitions[k][k]!="-1")
                    {
                        std::cout << "C" << std::endl;
                        C=transitions[k][k]+"*";
                    }
                    if(transitions[i][k]!="E")
                    {
                        std::cout << "A" << std::endl;
                        A=transitions[i][k];
                    }
                    if(transitions[k][j]!="E")
                    {
                        std::cout << "B" << std::endl;
                        B=transitions[k][j];
                    }

                    if(D!="")
                    {
                        transitions[i][j]=D;
                        if((A!="")||(B!="")||(C!=""))
                        {
                            transitions[i][j]=transitions[i][j]+"|";
                        }
                    }
                    else
                    {
                        transitions[i][j]="";
                    }
                    if(A!="")
                    {
                        transitions[i][j]=transitions[i][j]+A;
                        if((B!="")||(C!=""))
                        {
                            transitions[i][j]=transitions[i][j]+".";
                        }
                    }
                    if(C!="")
                    {
                        transitions[i][j]=transitions[i][j]+C;
                        if((B!=""))
                        {
                            transitions[i][j]=transitions[i][j]+".";
                        }
                    }
                    if(B!="")
                    {
                        transitions[i][j]=transitions[i][j]+B;
                    }
                    std::cout << "transitions[i][j] : "<< transitions[i][j] << std::endl;
                }
                //transitions[k][j]="-1";
                //transitions[j][k]="-1";
            }// end if(j!=k)
            j++;
        }// end while(j<at.nb_etats)
}

//******************************************************************************
