/*
  Program  : mkxlf
  Purpose  : Galaxy Model Utility.
             Make LF with slope -(1+x).
  History  : Began: 24 June 1994. Last edit: 26 April 1995.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. Output goes to stdout.
	     2. Other parameters (and their order) are mandatory.
	     3. Output is "M log10(N)"
*/

#include "gmutil.h"
#define USAGE fprintf(stderr,"Usage: mkxlf x bright faint del\n")

void main(int argc, char **argv)
{
  double x, mb, mf, dm, m, lf;
  int i;

  /** parse command line **/
  if (argc != 5) { USAGE; exit(1); }

  x  = atof(argv[1]);
  mb = atof(argv[2]);
  mf = atof(argv[3]);
  dm = atof(argv[4]);

  /** check args **/
  if (mb >= mf || dm <= 0.0) { USAGE; exit(1); }

  /** make production note **/
  printf("#"); for (i=0; i<argc; i++) printf("%s ",argv[i]); printf("\n");

  /** print out luminosity function **/
  for (m=mb; m<=mf; m+=dm) {
    lf = x * m;
    printf("%6.3f %8.5f\n", m, lf);
  }

  exit(0);
}
/*---------------------------------------------------------------------------*/
