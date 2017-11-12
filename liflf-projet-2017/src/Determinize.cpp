//******************************************************************************

#include <iostream>

#include "Determinize.h"
#include "FA_tools.h"
#include "Accept.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////

sAutoNDE Determinize(const sAutoNDE& at)
{
    sAutoNDE atD;
    /*
    if (EstDeterministe(at)){
        return at;
    }else{
        unsigned int i;
        etatset_t nouveauxEtats;
        set<etat_t>::const_iterator itr, itr2, itr3;
        sAutoNDE atD;

        nouveauxEtats.insert(at.initial); ///Insertion de l'état initial
        cout << "Nouveaux etats apres initialisation : "<< nouveauxEtats << endl;

        for (itr = nouveauxEtats.begin() ; itr != nouveauxEtats.end() ; itr++){
            for ( i = 0 ; i<at.nb_symbs ; i++){
                cout << "Symbole : " << (char)(ASCII_A + i) << endl;
                symb_t symboleEnCours = ASCII_A + i; ///Recupération du symbole en cours
                //etat_t etatEnCours; ///Etat de at qui va être traité
                etatset_t etatEnCours;
                etatEnCours.insert(*itr);
                cout << "itr : " << *itr << endl;
                cout << "Etat en cours : " << etatEnCours << endl;
                etatset_t etatAtteignables = Delta(at, etatEnCours, symboleEnCours); ///Ajout de tous les états atteignables depuis etatEnCours par symboleEnCours
                cout << "Etats atteignables : " << etatAtteignables << endl;
                Fermeture(at, etatAtteignables); ///Fermeture de l'état en cours
                cout << "Etats atteignables apres fermeture : " << etatAtteignables << endl;
                for (itr2 = etatAtteignables.begin() ; itr2!= etatAtteignables.end() ; itr2++){
                    nouveauxEtats.insert(*itr2); ///Stockage de l'état en cours

                }
//                nouveauxEtats.insert(*itr2); ///Stockage de l'état en cours
//                cout << "Etat ajoute : " <<  *itr2 << endl << endl;
//                cout << "Avec *itr2 : " << *itr2 << endl;
//                cout << "Avec *(etatAtteignables.begin()) : " << *(etatAtteignables.begin()) << endl;
//                cout << "Avec *(etatAtteignables.end()) : " << *(etatAtteignables.end()) << endl;
//                cout << "Avec *(etatAtteignables.set()) : " << *(etatAtteignables.set()) << endl;
//                cout << "Avec etatAtteignables.set( : " << etatAtteignables.set() << endl;
//                cout << "Avec for :";
//                for ()

                ///TODO : Ajouter le nouvel état à l'algorithme, avec ses liens

                //////////////////////////////////////
                cout << "Nouveaux Etats : " << endl;
                for (itr3 = nouveauxEtats.begin() ; itr3 != nouveauxEtats.end() ; itr3++){
                    cout << *itr3 << endl;
                }
                cout << endl;

                //////////////////////////////////////
            }
        }


        atD.initial = at.initial;
        cout << "Nouvel etat initial : " << atD.initial << endl;
        //TODO : Ajouter les états finaux et le nombre d'états

        return atD;

    }*/
    if (EstDeterministe(at)){
        return at;
    }else{
        unsigned int i;
        set<etatset_t> newEtatSets;

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
                //unsigned int ancienneTaille = newEtatSets.size();
                newEtatSets.insert(etatsAtteignables);
                ///3.4 Insertion du nouvel état et de sa transition
                /*if (newEtatSets.size() > ancienneTaille){
                    atD.nb_etats++;
                    etatset_t newEtat;
                    newEtat = *itr_newEtatSets;
                    set<etat_t>::const_iterator itr_newEtat;
                    for (itr_newEtat = newEtat.begin() ; itr_newEtat = newEtat.end() ; itr_newEtat++){
                        atD.trans[compteur][symboleEnCours] = *(newEtatSets.find(etatsAtteignables));
                    }
                }*/
                cout << "Nouveaux Etats : " << endl;
                set<etatset_t>::const_iterator itr3;
                for (itr3 = newEtatSets.begin() ; itr3 != newEtatSets.end() ; itr3++){
                    cout << *itr3 << endl;
                }
                cout << endl;
            }
        }

    }
    return atD;
}

//******************************************************************************
