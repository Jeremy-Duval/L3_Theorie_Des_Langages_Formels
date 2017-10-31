//******************************************************************************

#include <iostream>

#include "Determinize.h"
#include "FA_tools.h"
#include "Accept.h"

////////////////////////////////////////////////////////////////////////////////

sAutoNDE Determinize(const sAutoNDE& at){
  //TODO définir cette fonction

  sAutoNDE r;

  Delta(at, at.trans[0][0], 'a');

  return r;
}

//******************************************************************************
