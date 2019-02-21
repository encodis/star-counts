/*
  Program  : mknlf
  Purpose  : Galaxy Model Utility.
             Normalize a luminosity function.
  History  : Began: 20 May 1992. Last edit: 26 April 1995.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. Output goes to stdout.
             2. Reads from stdin if no file given.
	     3. Other parameters (and their order) are mandatory.
*/

#include "gmutil.h"
#define USAGE fprintf(stderr,"Usage: mknlf norm bright faint [lf]\n")

void main(int argc, char **argv)
{
  int    i, nlf;
  double *mag, *num, *d2;
  double norm, mb, mf, sum;
  char   file[81] = "\0";
  FILE   *inp;

  /** parse command line **/
  if (argc < 4 || argc > 5) { USAGE; exit(1); }

  norm = atof(argv[1]);
  mb   = atof(argv[2]);
  mf   = atof(argv[3]);

  /** check args **/
  if (norm <= 0.0 || mb > mf) { USAGE; exit(1); }

  /** read input lf **/
  if (argc == 5) strcpy(file,argv[4]);

  nlf = readdata(file, &mag, &num);

  /** set num = 10^num **/
  for (i=0; i<nlf; i++) num[i] = pow(10.0,num[i]);

  /** get sum of lf between limits **/
  if (mf == mb) {
    /** use 1 bin only **/
    for (i=0; i<nlf; i++) if (mag[i] == mf) sum = num[i];
  } else {
    /** find 2nd derivatives for spline **/
    Alloc(d2, nlf); 
    spline(mag, num, nlf, 1.0e30, 1.0e30, d2);

    /** find mag. limits **/
    mb = (mb < mag[0])     ? mag[0] : mb;
    mf = (mf > mag[nlf-1]) ? mag[nlf-1] : mf;

    /** integrate function **/
    sum = qsimp(mag, num, d2, nlf, mb, mf);
  }

  fprintf(stderr,"%g\n",sum);

  /** make production note **/
  printf("#"); for (i=0; i<argc; i++) printf("%s ",argv[i]); printf("\n");

  /** print out new lf - normalize and return to log scale **/
  for (i=0; i<nlf; i++) 
    printf("%8.5f %8.5f\n", mag[i], log10(num[i]*norm/sum));

  exit(0);
}
/*---------------------------------------------------------------------------*/
