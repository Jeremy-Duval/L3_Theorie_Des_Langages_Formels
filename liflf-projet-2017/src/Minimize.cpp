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
                for(unsigned int numSymbol=0 ; numSymbol < aOrigine.nb_symbs ; numSymbol++){
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
        ///On en profite pour ajouter les états finaux à l'automate minimal
        etatset_t etatSetEnCours = *etatSetIt;
        for(etatset_t::iterator etatIt = etatSetEnCours.begin() ; etatIt != etatSetEnCours.end() ; etatIt++){
            for(etatset_t::iterator etatIt2 = aOrigine.finaux.begin() ; etatIt2 != aOrigine.finaux.end() ; etatIt2++){
                if (*etatIt == *etatIt2){
                    aMinimal.finaux.insert(aMinimal.finaux.end(),i);
                    aMinimal.nb_finaux++;
                }
            }
        }
        i++;
    }
    ///On ajoute les transitions
    for(map<int, etatset_t>::iterator pairIt = groupeEtats.begin() ; pairIt != groupeEtats.end() ; pairIt++){
        ///On commence par trouver la "cible d'origine" de chaque classe pour chaque lettre
        pair<int,etatset_t> paireEnCours;
        etatset_t eSEnCours = paireEnCours.second;
        etat_t eEnCours = *(eSEnCours.begin());
        for(unsigned int numSymbol=0 ; numSymbol < aOrigine.nb_symbs ; numSymbol++){
            symb_t symboleEnCours = ASCII_A + numSymbol;
            ///(Delta ne fonctionne qu'avec un etatSet, alors on met l'etat seul dans un nouvel etatSet)
            etatset_t eSEnCoursFiltre; eSEnCoursFiltre.insert(eSEnCoursFiltre.begin(),eEnCours);
            etatset_t eSCibleOrigine = Delta(aOrigine,eSEnCoursFiltre,symboleEnCours);
            etat_t  eCibleOrigine = *(eSCibleOrigine.begin());
            ///Puis on en déduit la "cible minimale"
            etatset_t cibleMinimale;
            for(map<int, etatset_t>::iterator pairIt2 = groupeEtats.begin() ; pairIt2 != groupeEtats.end() ; pairIt2++){
                pair<int,etatset_t> paireEnCours2;
                etatset_t eSEnCours2 = paireEnCours2.second;
                etat_t eEnCours2 = *(eSEnCours2.begin());
                if(eEnCours2 == eCibleOrigine){
                    cibleMinimale.insert(eEnCours2);
                    aMinimal.trans[eEnCours][numSymbol] = cibleMinimale;
                }
            }
        }
    }
    /*for(map<int, etatset_t>::iterator pairIt = groupeEtats.begin() ; pairIt != groupeEtats.end() ; pairIt++){
        pair<int,etatset_t> paireEnCours;
        etatset_t eSEnCours = paireEnCours.second;
        etat_t eEnCours = *(eSEnCours.begin());
        for(int numSymbol=0 ; numSymbol < aOrigine.nb_symbs ; numSymbol++){
            symb_t symboleEnCours = ASCII_A + numSymbol;
            ///Delta ne fonctionne qu'avec un etatSet, alors on met l'etat seul dans un nouvel etatSet
            etatset_t eSEnCoursFiltre; eSEnCoursFiltre.insert(eSEnCoursFiltre.begin(),eEnCours);
            etatset_t eSCible = Delta(aOrigine,eSEnCoursFiltre,symboleEnCours);
            etat_t  eCible = *(eSCible.begin());
        }
    }*/
    return aMinimal;
}

//******************************************************************************
