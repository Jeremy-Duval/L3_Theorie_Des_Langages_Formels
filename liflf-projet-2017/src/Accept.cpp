//******************************************************************************

#include <iostream>
#include <algorithm>

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
    //TODO définir cette fonction

}

////////////////////////////////////////////////////////////////////////////////

etatset_t Delta(const sAutoNDE& at, const etatset_t& e, symb_t c)
{
    //TODO :
    //  récup elem de e et stocker
    //  pour chaque espsilon/trans[elem_e] (pour la lettre si trans) stocker dans r elem d'arrivé



    std::set<etat_t>::const_iterator itr, itr2;
    unsigned int symb_ascii;
    etatset_t r;

    symb_ascii = c-96;

    if(symb_ascii>at.nb_symbs)
    {
        //la lettre est une epsilon transition

        for(itr = e.begin(); itr!=e.end(); itr++)
        {
            if(*itr<at.epsilon.size())
            {
                std::cout<< "epsilon itr : " << at.epsilon[*itr] << std::endl;
                itr2 = at.epsilon[*itr].begin();
                if(at.epsilon[*itr].size()!=0)
                {
                    r.insert(*itr2);//dans le cas d'une epsilon transition, on doit ajouter l'indice car l'élément lu est en fait l'état dans lequel ont arrive par E-transition
                }
            }
        }
    }
    else
    {
        //la lettre doit être taitée normalement

        for(itr = e.begin(); itr!=e.end(); itr++)
        {
            itr2 = at.trans[*itr][symb_ascii-1].begin();
            if(at.trans[*itr][symb_ascii-1].size()!=0)
            {
                r.insert(*itr2);//dans le cas d'une epsilon transition, on doit ajouter l'indice car l'élément lu est en fait l'état dans lequel ont arrive par E-transition
            }
        }

    }

    return r;
}

////////////////////////////////////////////////////////////////////////////////

bool Accept(const sAutoNDE& at, std::string str)
{
    //TODO définir cette fonction

    return false;
}

//******************************************************************************
