//******************************************************************************

#include <iostream>
#include <algorithm>
#include <string>

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
    //TODO :
    //V-Calculer une lettre E-transition : c
    //V-appeler r = Delta(at, e, c)
    //pour chaque r : l'ajouter à e
    //afficher r pour le test

    symb_t c;
    etatset_t depuis_E_trans, e_prec;
    std::set<etat_t>::const_iterator itr;

    c = at.nb_symbs + ASCII_A;  //Calcule d'une lettre E-transition

    do
    {
        depuis_E_trans = e;
        e_prec = e;
        std::cout<<"e : "<<e<<std::endl;
        std::cout<<"dep : "<<depuis_E_trans<<std::endl;
        std::cout<<"dep p : "<<e_prec<<std::endl;
        depuis_E_trans = Delta(at, e, c);   //On récupère les etat accessible depuis chaque état de e grâce à des E-transitions
        std::cout<<"dep : "<<depuis_E_trans<<std::endl;

        std::cout<<"!= "<<std::endl;

        //on ajoute chaque élément de la liste obtenue à celle passée en pramètre
        for(itr = depuis_E_trans.begin(); itr!=depuis_E_trans.end(); itr++)
        {
            e.insert(*itr);
        }

    }
    while(e_prec.size()!=e.size());

}

////////////////////////////////////////////////////////////////////////////////

etatset_t Delta(const sAutoNDE& at, const etatset_t& e, symb_t c)
{

    std::set<etat_t>::const_iterator itr, itr2;
    unsigned int symb_ascii;
    etatset_t r;

    symb_ascii = c-(ASCII_A-1); //donne la place de la lettre dans l'alphabet (c-96)

    if(symb_ascii>at.nb_symbs)
    {
        //la lettre est une epsilon transition

        for(itr = e.begin(); itr!=e.end(); itr++)
        {
            if(*itr<at.epsilon.size())
            {
                if(at.epsilon[*itr].size()!=0)
                {
                    for(itr2 = at.epsilon[*itr].begin(); itr2!=at.epsilon[*itr].end(); itr2++)
                    {
                        r.insert(*itr2);
                    }
                }
            }
        }
    }
    else
    {
        //la lettre doit être taitée normalement

        for(itr = e.begin(); itr!=e.end(); itr++)
        {

            if(*itr<at.trans.size())
            {
                //itr2 = at.trans[*itr][symb_ascii-1].begin();
                if(at.trans[*itr][symb_ascii-1].size()!=0)
                {
                    for(itr2 = at.trans[*itr][symb_ascii-1].begin(); itr2!=at.trans[*itr][symb_ascii-1].end(); itr2++)
                    {
                        r.insert(*itr2);
                    }
                }
            }
        }

    }

    return r;
}

////////////////////////////////////////////////////////////////////////////////

bool Accept(const sAutoNDE& at, std::string str)
{
    bool est_accepte;
    unsigned int i;
    char symb_ascii;
    etatset_t etat_accessible;
    std::set<etat_t>::const_iterator itr, itr2;


    std::cout<<"Trans : "<<at.trans<<std::endl;
    std::cout<<"str : "<<str<<std::endl;

    //insertion de l'etat initial
    etat_accessible.insert(at.initial);
    Fermeture(at,etat_accessible);

    i=0;
    while(i<str.size())
    {
        std::cout<<"str i : "<<str.at(i)<<std::endl;
        symb_ascii = str.at(i); //extraction d'une lettre
        std::cout<<"etat_ac av : "<<etat_accessible<<std::endl;

        etat_accessible = Delta(at,etat_accessible,symb_ascii);
        std::cout<<"etat_ac ap : "<<etat_accessible<<std::endl;
        Fermeture(at,etat_accessible);
        std::cout<<"etat_ac ap E : "<<etat_accessible<<std::endl;

        i++;
    }

    //chercher si un des etat est final
    est_accepte = false;
    std::cout<<"finaux : "<<at.finaux<<std::endl;
    itr = etat_accessible.begin();
    while((itr!=etat_accessible.end())&&(est_accepte==false))
    {
        itr2 = at.finaux.begin();
        while((itr2!=at.finaux.end())&&(est_accepte==false))
        {
            if(*itr==*itr2)
            {
                est_accepte = true;
            }
            itr2++;
        }
        itr++;
    }
    std::cout<<"est ec : "<<est_accepte<<std::endl;
    return est_accepte;
}

//******************************************************************************
