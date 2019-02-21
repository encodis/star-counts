/*
  Function : obscure.c
  Purpose  : Bahcall - Soneira Galaxy Model.
             Calculate absorption along the line of sight.
  History  : Began: 25 June 1991. Last edit: 28 April 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. Calculates three kinds of absorption:
		(a) no absorption (mode = NA),
		(b) cosec law (mode = CS),
                (c) Sandage Obscuration Model (mode = SA)
*/

#include "bsm.h"

REAL obscure(int mode, REAL b, REAL r, REAL *a)
{
  REAL absm;
  REAL sinb, tanb;

  sinb = sin(fabs(b)*PI/180.0);
  tanb = tan(fabs(b)*PI/180.0);

  switch (mode) {
  case NA :
    absm = 0.0;
    break;
    
  case CS :
    absm = a[1] / sinb;
    break;
    
  case SA :
    absm = (fabs(b) > 50.0) ? 0.0 : a[2] * (a[3] - tanb) / sinb;  
    break;
  }
  
  return absm*(1.0 - exp(-sinb/a[0]*r));  
}
/*---------------------------------------------------------------------------*/
