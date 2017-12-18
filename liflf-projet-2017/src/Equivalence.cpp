//******************************************************************************

#include <iostream>
#include <cassert>

#include "Equivalence.h"

////////////////////////////////////////////////////////////////////////////////

std::string Automate2ExpressionRationnelle(sAutoNDE &at){

  std::string sr, A, B, C, D;
  unsigned int i, j, k;
  std::vector<etatset_t> tmp_vect_es;
  etatset_t tmp_es, tmp_copie_es;
  std::vector<std::vector<std::string>> transitions;
  std::vector<std::string> tmp_vect_str;
  bool trans_ijk;

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
    //on ajoute la E-transition du nouvel état de départ vers l'ancien
    tmp_es.insert(at.initial+1);
    at.epsilon.insert(at.epsilon.begin(), tmp_es);

    at.initial=0;
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
            //re insere nouveau etat_set
            tmp_vect_es.push_back(tmp_copie_es);
            j++;
        }

        //clean at.trans[i][j]
        at.trans.erase(itr_i);
        //remplacement de l'ancien vecteur d'etat_set
        at.trans.insert(itr_i,tmp_vect_es);
        i++;
        itr_i++;
    }

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


    at.epsilon.insert(at.epsilon.end(), tmp_es);

    //ajout d'une e-transition des anciens etats finaux vers le nouveau
    auto itr_finaux=at.finaux.begin();
    while(itr_finaux!=at.finaux.end())
    {
        at.epsilon[*itr_finaux+1].insert(at.epsilon[*itr_finaux+1].end(),at.nb_etats-1);//le +1 est là à cause du décalage fait précedemment pour ajouter l'état de départ générique ; at.trans et at.epsilon ont été mis à jour mais pas at.finaux
        itr_finaux++;
    }

    //mise à jour de at.nb_finaux et at.finaux
    at.nb_finaux=1;
    at.finaux.clear();
    at.finaux.insert(at.finaux.begin(), at.nb_etats-1);


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

    i=0; //après arrangement, l'état initial sera toujours 0

    k=1;
    while(k<at.nb_etats-1)//k symbolise les état supprimables, on ne doit pas prendre le dernier, ni le premier
    {
        j=1;
        while(j<at.nb_etats)
        {
            if(j!=k)
            {
                //test l'existance d'une transition de i à j par k
                trans_ijk = false;
                if(transitions[i][k]!="-1")
                {
                    if(transitions[k][j]!="-1")
                    {
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
                        D=transitions[i][j];
                    }
                    if(transitions[k][k]!="-1")
                    {
                        C=transitions[k][k]+"*";
                    }
                    if(transitions[i][k]!="E")
                    {
                        A=transitions[i][k];
                    }
                    if(transitions[k][j]!="E")
                    {
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
                     setTransition(at.nb_etats, transitions, j, k);
                }
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

  return sr;
}

////////////////////////////////////////////////////////////////////////////////

bool PseudoEquivalent(const sAutoNDE& a1, const sAutoNDE& a2, unsigned int word_size_max) {
  //TODO définir cette fonction

  return true;
}

////////////////////////////////////////////////////////////////////////////////

bool Equivalent(const sAutoNDE& a1, const sAutoNDE& a2) {
  //TODO définir cette fonction

  return true;
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
                //test l'existance d'une transition de i à j par k
                trans_ijk = false;
                if(transitions[i][k]!="-1")
                {
                    if(transitions[k][j]!="-1")
                    {
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
                        D=transitions[i][j];
                    }
                    if(transitions[k][k]!="-1")
                    {
                        C=transitions[k][k]+"*";
                    }
                    if(transitions[i][k]!="E")
                    {
                        A=transitions[i][k];
                    }
                    if(transitions[k][j]!="E")
                    {
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
                }
            }// end if(j!=k)
            j++;
        }// end while(j<at.nb_etats)
}

//******************************************************************************
