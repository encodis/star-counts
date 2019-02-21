/*
  Program  : mkalf.c
  Purpose  : Galaxy Model Utility.
             Make an analytic luminosity function.
  History  : Began: 23 March 1992. Last edit: 26 April 1995.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. Must be compiled with the following definition:
                -DBAND_DATA=\"/home/hodder/lib/bsm/bvrijk.dat\"
	     2. Wielen and DaCosta modifications not yet enabled.
*/

#include "gmutil.h"
#include "bvrijk.h"
#define USAGE fprintf(stderr,"Usage: mkalf filter|file bright faint del\n")

void main(int argc, char **argv)
{
  int    i, f = NF;
  double m, lf;
  double mb, mf, dm;
  double ns, Ms, a, b, d, Mb, Mc, Md, ul;
  char   file[81];
  FILE   *inp;

  /** parse command line **/
  if (argc != 5) { USAGE; exit(1); }

  mb = atof(argv[2]);
  mf = atof(argv[3]);
  dm = atof(argv[4]);

  /** check args **/
  if (mb >= mf || dm <= 0.0) { USAGE; exit(1); }

  switch(argv[1][0]) {
  case 'B' :
    f = B;
    break;
  case 'V' :
    f = V;
    break;
  case 'R' :
    f = R;
    break;
  case 'I' :
    f = I;
    break;
  case 'J' :
    f = J;
    break;
  case 'K' :
    f = K;
    break;
  default :
    strcpy(file,argv[1]);
  }

  /** try to read file if not a filter **/
  if (f == NF) {
    if ((inp = fopen(file,"r"))) {
      fscanf(inp, "%lf %lf %lf %lf %lf %lf %lf %lf %lf \n",
	     &ns, &Ms, &a, &b, &d, &Mb, &Mc, &Md, &ul);
      fclose(inp);
    } else {
      fprintf(stderr,"Error: %s not found\n", argv[1]);
      USAGE; exit(1);
    }
  } else {
    ns = Data[f][0];
    Ms = Data[f][1];
    a  = Data[f][2];
    b  = Data[f][3];
    d  = Data[f][4];
    Mb = Data[f][5];
    Mc = Data[f][6];
    Md = Data[f][7];
    ul = Data[f][8];
  }

  /** make production note **/
  printf("#"); for (i=0; i<argc; i++) printf("%s ",argv[i]); printf("\n");

  /** print out luminosity function **/
  for (m=mb; m<=mf; m+=dm) {
    if (m >= Mb && m <= Mc) {
      lf = ns*pow(10.0, b*(m-Ms))/pow(1.0+pow(10.0,-(a-b)*(1.0/d)*(m-Ms)),d);
      if (lf > ul) lf = ul;
      lf = log10(lf);
    } else if (m > Mc && m <= Md) {
      lf = log10(ul);
    } else if (m < Mb || m > Md) {
      continue;                                 /* can't have 0.0 == 1 star! */
    }
    printf("%6.3f %8.5f\n", m, lf);
  }

  exit(0);
}
/*---------------------------------------------------------------------------*/
