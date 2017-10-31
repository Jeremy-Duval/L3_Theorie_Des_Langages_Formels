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
    unsigned int symb_ascii, i;
    etatset_t r;

    symb_ascii = c-96;

    std::cout<< "sym : " << symb_ascii << std::endl;

    if(symb_ascii>at.nb_symbs){
        //la lettre est une epsilon transition

        i=0;
        while(i<at.epsilon.size()){
            std::cout<< "eps : " << at.epsilon[i] << std::endl;
            if(at.epsilon[i].size()!=0){
                std::cout<< "eps > 0 " << std::endl;
                r.insert(i);//dans le cas d'une epsilon transition, on doit ajouter l'indice car l'élément lu est en fait l'état dans lequel ont arrive par E-transition
            }
            i++;
        }
        std::cout<< "r : " << r << std::endl;
    }
    else {
        //la lettre doit être taitée normalement


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
