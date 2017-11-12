//******************************************************************************

#include <iostream>

#include "Determinize.h"
#include "FA_tools.h"
#include "Accept.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////

sAutoNDE Determinize(const sAutoNDE& at)
{
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
                //nouveauxEtats.insert(*itr2); ///Stockage de l'état en cours
                /*cout << "Etat ajoute : " <<  *itr2 << endl << endl;
                cout << "Avec *itr2 : " << *itr2 << endl;
                cout << "Avec *(etatAtteignables.begin()) : " << *(etatAtteignables.begin()) << endl;
                cout << "Avec *(etatAtteignables.end()) : " << *(etatAtteignables.end()) << endl;
                cout << "Avec *(etatAtteignables.set()) : " << *(etatAtteignables.set()) << endl;
                cout << "Avec etatAtteignables.set( : " << etatAtteignables.set() << endl;
                cout << "Avec for :";
                for ()*/

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
    }
}

//******************************************************************************
