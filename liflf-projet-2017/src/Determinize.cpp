//******************************************************************************

#include <iostream>

#include "Determinize.h"
#include "FA_tools.h"
#include "Accept.h"

////////////////////////////////////////////////////////////////////////////////

sAutoNDE Determinize(const sAutoNDE& at){
  //TODO définir cette fonction

  sAutoNDE r;

    etatset_t Nes;
    Nes.insert(0);
    Nes.insert(1);
    Nes.insert(3);
    std::cout << "Nes : " << Nes <<std::endl;

    Fermeture(at, Nes);

  return r;
}

//******************************************************************************
