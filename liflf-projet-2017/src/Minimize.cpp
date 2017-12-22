//******************************************************************************

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

#include "Minimize.h"
#include "Determinize.h"
#include "Accept.h"
using namespace std;

////////////////////////////////////////////////////////////////////////////////

sAutoNDE Minimize(const sAutoNDE& aOrigine)
{
    ///Initialisation
    sAutoNDE aMinimal;
    vector<etatset_t> VeSAvant;
    vector<etatset_t> VeSApres;
    etatset_t finaux;
    etatset_t nonFinaux;
    map<etat_t,vector<etatset_t> > transMap;

    ///On déterminise l'automate
    if(!EstDeterministe(aOrigine))Determinize(aOrigine);

    ///On sépare les états en finaux/non-finaux
    VeSAvant.insert(VeSAvant.end(),aOrigine.finaux);
    for(etat_t etat = 0 ; etat<aOrigine.nb_etats ; etat++){
        if(finaux.find(etat) != finaux.end()) {
            nonFinaux.insert(nonFinaux.end(),etat);
        }
    }
    do{

        vector<etatset_t>::iterator etatsetIt;
        for(etatsetIt = VeSAvant.begin() ; etatsetIt != VeSAvant.end() ; etatsetIt++){
            ///On associe chaque état au "groupe d'état" qu'il peut atteindre
            etatset_t etatSetEnCours = *etatsetIt;
            etatset_t::iterator etatIt;
            for (etatIt = etatSetEnCours.begin() ; etatIt != etatSetEnCours.end() ; etatIt++){
                vector<etatset_t> etatSetsAtteignables;
                for(int numSymbol=0 ; numSymbol < aOrigine.nb_symbs ; numSymbol++){
                    symb_t symboleEnCours = ASCII_A + numSymbol;
                    etatSetsAtteignables.insert(etatSetsAtteignables.end(),Delta(aOrigine,*etatsetIt,symboleEnCours));
                }
                pair<etat_t,vector<etatset_t> > transitionsEtat;
                transitionsEtat.first = *etatIt;
                transitionsEtat.second = etatSetsAtteignables;
                transMap.insert(transMap.begin(),transitionsEtat);
            }
        }
        etatset_t classe;
        while(!transMap.empty()){
            classe.clear();
            ///On va regrouper les états par classes d'équivalences, on commence par sortir le premier état de la transMap
            pair<etat_t,vector<etatset_t> > premieresTransitions = *(transMap.begin());
            etat_t premierEtat = premieresTransitions.first;
            classe.insert(classe.end(),premierEtat);
            transMap.erase(transMap.begin());
            ///Et on le compare à ceux restant
            map<etat_t,vector<etatset_t> >::iterator transIt = transMap.begin();
            while(transIt != transMap.end()){
                pair<etat_t,vector<etatset_t> > pairEnCours = *transIt;
                ///Si les deux états ont des transitions équivalentes, on les regroupe et on allège la transMap
                if(premieresTransitions.second == pairEnCours.second){
                    classe.insert(classe.end(),pairEnCours.first);
                    transMap.erase(pairEnCours.first); //erase() incrémente tout seul après avoir supprimé la paire
                }else{
                    transIt++;
                }
            }
            ///On ajoute alors la classe ainsi trouvée à notre nouvelle liste d'etatSets
            VeSApres.insert(VeSApres.end(),classe);
            /*(map<etat_t,vector<etatset_t> >::iterator transIt = transMap.begin() ; transIt != transMap.end() ; transIt++){
                pair<etat_t,vector<etatset_t> > pairEnCours = *transIt;
                ///Si les deux états ont des transitions équivalentes, on les regroupe
                if(premieresTransitions.second == pairEnCours.second){
                    classe.insert(classe.end(),pairEnCours.first);
                }
            }*/

        }
    }while(VeSAvant != VeSApres);

    ///Assemblage de l'automate minimal
    aMinimal.initial = aOrigine.initial;
    aMinimal.nb_symbs = aOrigine.nb_symbs;
    map<int, etatset_t> groupeEtats;
    int i=0;
    ///On associe à chaque nouvel classe un numéro dont on va se servir pour créer les états de l'automate minimal
    for(vector<etatset_t>::iterator etatSetIt = VeSApres.begin() ; etatSetIt != VeSApres.end() ; etatSetIt++){
        pair<int,etatset_t> paireEnCours;
        paireEnCours.first = i;
        paireEnCours.second = *etatSetIt;
        groupeEtats.insert(groupeEtats.end(),paireEnCours);

        i++;
    }
    ///On parcours cette liste pour trouver les nouveaux états finaux
    for(map<int,etatset_t>::iterator pairIt = groupeEtats.begin() )
    aMinimal.nb_finaux = aMinimal.finaux.size();

    return aMinimal;
}

//******************************************************************************
