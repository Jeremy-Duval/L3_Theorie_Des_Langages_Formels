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
        unsigned int i,j;
        etatset_t nouveauEtats;
        set<etat_t>::const_iterator itr;
        sAutoNDE atD;


        Fermeture(at, nouveauEtats); ///Obligé de faire la fermeture une fois au début car la fonction ne renvoie pas la fermeture mais complète l'automate, donc il faut compléter l'automate de départ au début
        nouveauEtats.insert(at.initial); ///Insertion de l'état 0, considéré comme l'état de départ


        for (itr = nouveauEtats.begin() ; itr != nouveauEtats.end() ; itr++){
            for ( i = 0 ; i<at.nb_symbs ; i++){
                cout << "Symbole : " << (char)(ASCII_A + i) << endl;
            }
        }


        atD.initial = at.initial;
        cout << "Nouvel etat initial : " << atD.initial << endl;
        //TODO : Ajouter les états finaux et le nombre d'états

        return atD;
    }
}

//******************************************************************************
