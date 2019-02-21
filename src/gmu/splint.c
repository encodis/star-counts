/*
  Function : splint.c
  Purpose  : Spline interpolation.
  History  : Began modification: 22 November 1991. Last edit: 24 May 1993.
  Author   : Original: Press, Flannery, Teukolsky & Vetterling (Numerical
                       Recipes in C).
	     Modified: P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. Original code from Numerical Recipes in C (Press, Flannery, 
                Teukolsky & Vetterling,  Cambridge Univeristy Press, 1989).
	     2. Modified by PJCH to  avoid use of  other NR  constructs and 
	        functions.
*/

#include "gmutil.h"

double splint(double *xa, double *ya, double *y2a, int n, double x)
{
  int    klo, khi, k;
  double h, b, a, y;
  
  klo = 0;
  khi = n-1;

  while (khi-klo > 1) {
    k = (khi+klo) >> 1;

    if (xa[k] > x)
      khi = k;
    else 
      klo = k;
  }

  h = xa[khi] - xa[klo];
  if (h == 0.0) {
    fprintf(stderr,"\n Bad XA input to routine splint()");
    exit(1);
  }

  a = (xa[khi]-x)/h;
  b = (x-xa[klo])/h;
  y = a*ya[klo]+b*ya[khi]+((a*a*a-a)*y2a[klo]+(b*b*b-b)*y2a[khi])*(h*h)/6.0;

  return y;
}
/*---------------------------------------------------------------------------*/
