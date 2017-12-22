//******************************************************************************

#include <iostream>

#include "Determinize.h"
#include "FA_tools.h"
#include "Accept.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
sAutoNDE Determinize(const sAutoNDE& at){
    if(!EstDeterministe(at)){
        //Initialisation de l'automate de travail
        sAutoNDE r;
        r.initial = 0;
        r.nb_etats=1;
        r.nb_symbs=at.nb_symbs;
        r.nb_finaux=0;

        etatset_t prec;
        etatset_t cour;
        std::vector<etatset_t> nouvVector;
        std::vector<etatset_t> etatCree;

        prec.insert(at.initial);
            Fermeture(at, prec);

        etatCree.push_back(prec);

        for(int indexExit= 0; (unsigned int)indexExit < etatCree.size(); indexExit++){
            r.trans.push_back(nouvVector);
            prec = etatCree[indexExit];
            Fermeture(at,prec);
            for ( size_t i = 0; i < at.nb_symbs ; i++){
                cour = Delta(at, prec, (char) ASCII_A+i);
                Fermeture(at,cour);
                auto itEC = etatCree.begin();
                bool existe = false;
                etat_t id;
                for ( id = 0 ; id<(etat_t)etatCree.size() ; id++ ){

                    if (cour == *itEC){

                      etatset_t nouvEtat;
                      nouvEtat.insert(id);
                      r.trans[indexExit].push_back(nouvEtat);
                      itEC++;
                      existe=true;
                      break;

                    }
                itEC++;

                }
                if (!existe){

                  etatset_t nouvEtat;
                  nouvEtat.insert(id);
                  etatCree.push_back(cour);
                  r.trans[indexExit].push_back(nouvEtat);
                  r.nb_etats++;

                }
              }


                }
          for(int i=0; i < (int)etatCree.size();i++){
                     for(auto it=etatCree[i].begin(); it!=etatCree[i].end();it++){
                             for(auto itT=at.finaux.begin(); itT!=at.finaux.end();itT++){
                                      if(*it==*itT) {
                                                r.finaux.insert((etat_t)i);
                        }
                    }
                }
            }
              r.nb_etats = r.trans.size();
              r.nb_finaux = r.finaux.size();
          return r;
    }else return at;


/*
sAutoNDE Determinize(const sAutoNDE& at)
{
    sAutoNDE atD;
    if (EstDeterministe(at)){
        return at;
    }else{
        unsigned int i;
        set<etatset_t> newEtatSets;
        map_t newMap;
        set<etatset_t>::const_iterator itr_newEtatSets;
        sAutoNDE atD;


        /// 1. ajout dans newEtatSets de l'etat initial fermé
        etatset_t etatSetInitial;
        etatSetInitial.insert(at.initial);
        Fermeture(at, etatSetInitial);
        newEtatSets.insert(etatSetInitial);

        /// 2. Boucle sur newEtatSets
        for (itr_newEtatSets = newEtatSets.begin() ; itr_newEtatSets != newEtatSets.end() ; itr_newEtatSets++){
            /// 3. Boucle sur nb_symbs
            for ( i = 0 ; i<at.nb_symbs ; i++){
                symb_t symboleEnCours = ASCII_A + i;
                cout << "Symbole : " << (char)(ASCII_A + i) << endl;
                cout << "Etat en cours : " << *itr_newEtatSets << endl;
                ///3.1 Delta de l'etatSetEnCours par symboleEnCours
                etatset_t etatsAtteignables = Delta(at, *itr_newEtatSets, symboleEnCours);
                ///3.2 Fermeture des etatsAtteignables
                if (!etatsAtteignables.empty()){
                    Fermeture(at, etatsAtteignables);
                }
                cout << "Etats atteignables : " << etatsAtteignables << endl;
                ///3.3 Insertion des etatsAtteignables fermés dans newEtatSets
                unsigned int ancienneTaille = newEtatSets.size();
                cout << "Ancienne taille : " << ancienneTaille << endl;
                newEtatSets.insert(etatsAtteignables);
                ///3.4 Insertion du nouvel état et de sa transition
                cout << "Nouveaux Etats : " << endl;
                set<etatset_t>::const_iterator itr3;
                for (itr3 = newEtatSets.begin() ; itr3 != newEtatSets.end() ; itr3++){
                    cout << *itr3 << endl;
                }
                cout << endl;
                cout << "Nouvelle taille : " << newEtatSets.size() << endl;
                if (newEtatSets.size() > ancienneTaille){
                    atD.nb_etats++;
                    etat_t origine;
                    etatset_t temp;
                    temp = *itr_newEtatSets;
                    cout << "Temp : " << temp << endl;
                    set<etat_t>::const_iterator itr2;
                    for (itr2 = temp.begin() ; itr2 != temp.end() ; itr2++){
                        origine = *itr2;
                        cout << "Origine : " << origine << endl;
                    }

                    set<etatset_t>::const_iterator itr3;
                    itr3 = newEtatSets.begin();
                    while (*itr3 != etatsAtteignables){
                        itr3++;
                    }
                    newMap.insert(pair<etatset_t,etat_t>(etatsAtteignables,origine));
                    cout << "newMap : " << newMap << endl;
                    //etat_t destination;
                    //destination = distance(newEtatSets.begin(), newEtatSets.find(etatsAtteignables));
                    //atD.trans[origine][symboleEnCours] = destination;
                }
            }
        }
    }
    return atD;
}*/

//******************************************************************************
