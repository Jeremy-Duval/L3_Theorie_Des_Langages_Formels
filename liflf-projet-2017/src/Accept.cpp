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
        std::cout << "first ep while : "<< at.epsilon[i] << std::endl;
        if(at.epsilon[i].size())
        {
            deterministe = false;
        }
        i++;
    }
    i = 0;
    while((i<at.trans.size())&&(deterministe==true))
    {
        std::cout << "first while : " << std::endl;
        j = 0;
        while((j<at.trans[i].size())&&(deterministe==true))
        {
            std::cout << "second while : info :" << at.trans[i][j].size() << std::endl;
            if(at.trans[i][j].size()>1)
            {
                deterministe = false;
            }
            j++;
        }
        i++;
    }

    std::cerr << "det ? : " << deterministe << std::endl;
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
    //TODO définir cette fonction

    etatset_t r;

    return r;
}

////////////////////////////////////////////////////////////////////////////////

bool Accept(const sAutoNDE& at, std::string str)
{
    //TODO définir cette fonction

    return false;
}

//******************************************************************************
