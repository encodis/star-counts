/*
  Program  : mkfms.c
  Purpose  : Galaxy Model Utilities.
             Make a file containing data on fraction of stars on ms.
  History  : Began: 24 March 1992. Last edit: 26 April 1995.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. 
*/

#include "gmutil.h"
#include "bvrijk.h"
#define USAGE fprintf(stderr,"Usage: mkfms filter|file bright faint del\n")

void main(int argc, char **argv)
{
  int    i, f = NF;
  double m, fms;
  double mb, mf, dm;
  double c, a, b, g, ma;
  char   file[81];
  FILE   *inp;

  /** parse command line **/
  if (argc != 5) { USAGE; exit(1); }

  mb = atof(argv[2]);
  mf = atof(argv[3]);
  dm = atof(argv[4]);

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
      fscanf(inp, "%lf %lf %lf %lf %lf \n", &c, &a, &b, &g, &ma);
      fclose(inp);
    } else {
      fprintf(stderr,"Error: %s not found\n", argv[1]);
      USAGE; exit(1);
    }
  } else {
    c  = Data[f][9];
    a  = Data[f][10];
    b  = Data[f][11];
    g  = Data[f][12];
    ma = Data[f][13];
  }

  /** make production note **/
  printf("#"); for (i=0; i<argc; i++) printf("%s ",argv[i]); printf("\n");

  /** print out fraction of stars on ms **/
  for (m=mb; m<(mf+dm); m+=dm)  {
    if (m < ma) {
      fms = c*exp(a*pow((m+b),g));
      if (fms > 1.0) fms = 1.0;
    } else {
      fms = 1.0;
    }    
    printf("%6.3f %8.5f\n", m, fms);
  }

  exit(0);
}
/*---------------------------------------------------------------------------*/
