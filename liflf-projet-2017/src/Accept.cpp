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

  std::string sr;
  int epsilon_trans, j;
  std::vector<etatset_t> tmp_vect_es;
  etatset_t tmp_es, tmp_copie_es;
  etat_t tmp_e;
    //int i;

  std::cout << "nb_etats : " << at.nb_etats <<std::endl;
  std::cout << "nb_symbs : " << at.nb_symbs <<std::endl;
  std::cout << "initial : " << at.initial <<std::endl;
  std::cout << "finaux : " << at.finaux <<std::endl;
  std::cout << "trans : " << at.trans <<std::endl;
  std::cout << "epsilon : " << at.epsilon <<std::endl;
  std::cout << "****************************************" <<std::endl;

    /* ***Décalage des symbole et ajout d'un état de départ  générique***/
    epsilon_trans = at.nb_symbs+1;
    at.nb_etats++;

    //décalage de at.trans

    //pour chaque lettre, on ajoute une E-transition partant du nouvel etat 0
    i=0;
    while(i<at.nb_symbs)
    {
        tmp_vect_es.push_back(tmp_es);
        i++;
    }
    at.trans.insert(at.trans.begin(),tmp_vect_es);
    std::cout<<"at.trans : "<<at.trans<<std::endl;

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


    //TODO :
    //ajout d'un unique etat final (nb etat++)
    //transition spontanée des anciens etat finaux vers le nouveau
    //changer at.nb_finaux et at.finaux

  std::cout<<"Sr : "<<sr<<std::endl;












    return est_accepte;
}

//******************************************************************************
