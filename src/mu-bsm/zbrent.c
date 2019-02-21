/*
  Function : zbrent.c
  Purpose  : MU space. Bahcall - Soneira Galaxy Model.
             Find roots using van Wijngaarden-Dekker-Brent method.
  History  : Began modification: 2 June 1994.
  Author   : Original: Press, Flannery, Teukolsky & Vetterling (Numerical
                       Recipes in C).
             Modified: P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. Original code from Numerical Recipes in C (Press, Flannery, 
                Teukolsky & Vetterling, Cambridge Univeristy Press, 1989).
             2. Modified by PJCH to avoid use of other NR constructs and 
                functions.
	     3. Hacked a bit to get around "pointer-to-function" crap which I
	        don't fully understand yet!
*/

#include "mubsm.h"

#define ITMAX 100
#define EPS 3.0e-8
#define FUNC(R) \
       (5.0*log10( (R) ) - 5.0 - mu + obscure(pm->amode, ml->b2, (R), pm->a))

REAL zbrent(Param *pm, Model *ml, REAL mu, REAL tol)
{
  int iter;
  REAL a,b,c,d,e,min1,min2,x1,x2;
  REAL fa,fb,fc,p,q,r,s,tol1,xm;

  x1 = 1.0; x2 = 5.0e6;       /* min and max r that solution is in */
  
  a=x1; b=x2;
  fa = FUNC(a); fb=FUNC(b);

  if (fb*fa > 0.0) quit_bsm(ERR_MATH,"Root must be bracketed","zbrent()");
  fc=fb;
  for (iter=1;iter<=ITMAX;iter++) {
    if (fb*fc > 0.0) {
      c=a;
      fc=fa;
      e=d=b-a;
    }
    if (fabs(fc) < fabs(fb)) {
      a=b;
      b=c;
      c=a;
      fa=fb;
      fb=fc;
      fc=fa;
    }
    tol1=2.0*EPS*fabs(b)+0.5*tol;
    xm=0.5*(c-b);
    if (fabs(xm) <= tol1 || fb == 0.0) return b;
    if (fabs(e) >= tol1 && fabs(fa) > fabs(fb)) {
      s=fb/fa;
      if (a == c) {
	p=2.0*xm*s;
	q=1.0-s;
      } else {
	q=fa/fc;
	r=fb/fc;
	p=s*(2.0*xm*q*(q-r)-(b-a)*(r-1.0));
	q=(q-1.0)*(r-1.0)*(s-1.0);
      }
      if (p > 0.0)  q = -q;
      p=fabs(p);
      min1=3.0*xm*q-fabs(tol1*q);
      min2=fabs(e*q);
      if (2.0*p < (min1 < min2 ? min1 : min2)) {
	e=d;
	d=p/q;
      } else {
	d=xm;
	e=d;
      }
    } else {
      d=xm;
      e=d;
    }
    a=b;
    fa=fb;
    if (fabs(d) > tol1)
      b += d;
    else
      b += (xm > 0.0 ? fabs(tol1) : -fabs(tol1));
    fb=FUNC(b);
  }
  quit_bsm(ERR_MATH,"Maximum number of iterations exceeded","zbrent()");
}
/*---------------------------------------------------------------------------*/
