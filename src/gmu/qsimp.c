/*
  Function : qsimp.c
  Purpose  : Controller for trapzd.c
  History  : Began modification: 20 May 1992. Last edit: 18 May 1994.
  Author   : Original: Press, Flannery, Teukolsky & Vetterling (Numerical
                       Recipes in C).
	     Modified: P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. Original code from Numerical Recipes in C (Press, Flannery, 
                Teukolsky & Vetterling, Cambridge Univeristy Press, 1989).
*/

#include "gmutil.h"
#define EPS  1.0e-5
#define JMAX 20

double qsimp(double *mag, double *num, double *d2, int nlf, double a, double b)
{
  int    j;
  double s, st, ost, os;
  
  ost = os = 1.0e-30;
  for (j=0; j<JMAX; j++) {
    st = trapzd(mag, num, d2, nlf, a, b, j+1);
    s = (4.0*st-ost)/3.0;
    if (fabs(s-os) < EPS*fabs(os)) return s;
    os = s;
    ost = st;
  }

   fprintf(stderr," Error: too many steps in qsimp().\n");
   exit(1);
}
/*---------------------------------------------------------------------------*/
