/*
  Function : trapzd.c
  Purpose  : Trapezoidal rule for integration.
  History  : Began modification: 20 May 1992. Last edit: 18 May 1994.
  Author   : Original: Press, Flannery, Teukolsky & Vetterling (Numerical
                       Recipes in C).
	     Modified: P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. Original code from Numerical Recipes in C (Press, Flannery, 
                Teukolsky & Vetterling, Cambridge Univeristy Press, 1989).
*/

#include "gmutil.h"
#define FUNC(X) (splint(mag,num,d2,nlf,(X)))

double trapzd(double *mag, double *num, double *d2, int nlf,
	      double a, double b, int n)
{
  double        x, tnm, sum, del;
  static double s;
  static int    it;
  int           j;

  if (n == 1) {
    it = 1;
    s = 0.5*(b-a)*(FUNC(a)+FUNC(b));
    return s;
  } else {
    tnm = it;
    del = (b-a)/tnm;
    x = a + 0.5*del;
    for (sum=0.0, j=0; j<it; j++, x+=del) sum += FUNC(x);
    it *= 2;
    s = 0.5 * (s + (b-a)*sum/tnm);
    return s;
  }
}
/*---------------------------------------------------------------------------*/
