/*
  Function : solve4r.c
  Purpose  : MU space. Bahcall - Soneira Galactic Model. 
             Solve for r given mu and A(r).
  History  : Began: 2 June 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. Basically a wrapper around zbrent().
*/

#include "mubsm.h"
#define TOL 1e-6

REAL solve4r(Param *pm, Model *ml, REAL mu)
{
  REAL r;

  r = zbrent(pm, ml, mu, TOL);

  if (r > 0.0) {
    return r;
  } else {
    quit_bsm(ERR_MATH,"Negative r","solve4r()");
  }
}
/*---------------------------------------------------------------------------*/
