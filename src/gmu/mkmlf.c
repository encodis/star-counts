/*
  Program  : mkmlf.c
  Purpose  : Galaxy Model Utility.
             Make a luminosity function from a mass function and a 
	     mass-luminosity relation.
  History  : Began: 24 March 1992. Last edit: 26 April 1995.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1.
*/

#include "gmutil.h"
#define USAGE fprintf(stderr,"Usage: mkmlf x a bright faint del [mlr] \n")

void main(int argc, char **argv)
{
  int    i, npt;
  double *mag, *mass, *d2;
  double x, a, mb, mf, dm;
  double upp_m, low_m;
  double l, m;
  char   file[81];

  /** parse command line **/
  if (argc < 6 || argc > 7) { USAGE; exit(1); }

  x  = atof(argv[1]);
  a  = atof(argv[2]);
  mb = atof(argv[3]);
  mf = atof(argv[4]);
  dm = atof(argv[5]);

  /** check args **/
  if (mb >= mf || a <= 0.0 || dm <= 0.0 ) { USAGE; exit(1); }

  /** read input lf **/
  if (argc == 7) {
    strcpy(file,argv[7]);
  } else {
    strcpy(file,"\0");
  }

  npt = readdata(file, &mag, &mass);

  /** find 2nd derivatives for spline **/
  Alloc(d2, npt);
  spline(mag, mass, npt, 1.0e30, 1.0e30, d2);

  low_m = mass[npt-1]; upp_m = mass[0];
      
  /** make production note **/
  printf("#"); for (i=0; i<argc; i++) printf("%s ",argv[i]); printf("\n");

  /** print out luminosity function **/
  for (l=mb; l<mf; l+=dm) {
    m = splint(mag, mass, d2, npt, l);
    
    if (m < low_m || m > upp_m) continue;

    printf("%6.3f %8.5f\n", l, log(a) - (1.0+x)*log(m));
  }

  exit(0);
}
/*---------------------------------------------------------------------------*/
