/*
  Function : obscure.c
  Purpose  : External Galxy Model.
             Calculate absorption along the line of sight.
  History  : Began: 6 October 1992.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. Calculates three kinds of absorption:
		(a) no absorption (mode = NA),
		(b) cosec law (mode = CS),
                (c) Sandage Obscuration Model (mode = SA)
	     2. "r" is the distance from the plane of the galaxy.
*/

#include "egm.h"

double obscure(int mode, double b, double r, double *a)
{
  double absm;

  switch (mode) {
  case NA :
    absm = 0.0;
    break;

  case CS :
    absm = a[1]/sin(b);
    break;

  case SA :
    absm = (fabs(180.0/PI*b) > 50.0) ? 0.0 : a[2]*(a[3]-tan(b))/sin(b);  
    break;
  }
  
  return absm*(1.0-exp( (-sin(b)/a[0])*r) );
}
/*---------------------------------------------------------------------------*/
