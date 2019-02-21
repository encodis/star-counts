/*
  Function : splint.c
  Purpose  : MU space. Bahcall - Soneira Galaxy Model.
             Spline interpolation.
  History  : Began modification: 22 November 1991. Last edit: 28 April 1994.
  Author   : Original: Press, Flannery, Teukolsky & Vetterling (Numerical
                       Recipes in C).
	     Modified: P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. Original code from Numerical Recipes in C (Press, Flannery, 
                Teukolsky & Vetterling, Cambridge Univeristy Press, 1989).
	     2. Modified by PJCH to avoid use of other NR constructs and 
	        functions.
	     3. Function is now a REAL function - it returns the value of y 
	        directly rather than through an address. This fits better with 
		the way it is used in init_col() and init_lum().
*/

#include "mubsm.h"

REAL splint(REAL *xa, REAL *ya, REAL *y2a, int n, REAL x)
{
  int klo, khi, k;
  REAL h, b, a, y;
  
  klo = 0;
  khi = n-1;

  while (khi-klo > 1) {
    k = (khi+klo) >> 1;
    
    if (xa[k] > x) {
      khi = k;
    } else {
      klo = k;
    }
  }

  h = xa[khi] - xa[klo];
  if (h == 0.0) {
    quit_bsm(ERR_MATH,"Bad XA input","splint()");
  }

  a = (xa[khi]-x)/h;
  b = (x-xa[klo])/h;
  y = a*ya[klo]+b*ya[khi]+((a*a*a-a)*y2a[klo]+(b*b*b-b)*y2a[khi])*(h*h)/6.0;
  
  return y;
}
/*---------------------------------------------------------------------------*/
