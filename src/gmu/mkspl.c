/*
  Program  : mkspl
  Purpose  : Galaxu Model Utility.
             Make a spline fit to data.
  History  : Began: 27 February 1994. Last edit: 28 June 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. Output goes to stdout.
             2. Reads from stdin if no file given.
	     3. Other parameters are mandatory.
*/

#include "gmutil.h"
#define USAGE fprintf(stderr,"Usage: mkspl [-l|-e] min max del [file]\n")

void main(int argc, char **argv)
{
  int    n;
  int    a = 0;
  int    l = FALSE, e = FALSE;
  double *x, *y, *d2;
  double min, max, del, i;
  double s1, z1, sN, zN, val;
  char   file[81];
  FILE   *inp;

  /** parse command line **/
  if (argc > 1) {
    if (!strcmp(argv[1],"-l")) { 
      l = TRUE; argc--; a = 1;
    } else if (!strcmp(argv[1],"-e")) { 
      e = TRUE; argc--; a = 1;
    }
  }

  if (argc < 4 || argc > 5) { USAGE; exit(1); }

  min = atof(argv[a+1]);
  max = atof(argv[a+2]);
  del = atof(argv[a+3]);

  /** check args **/
  if (max <= min || del <= 0.0) { USAGE; exit(1); }

  /** read input **/
  if (argc == 5) {
    strcpy(file,argv[a+4]);
  } else {
    strcpy(file,"\0");
  }

  n = readdata(file, &x, &y);

  /** find 2nd derivatives for spline **/
  Alloc(d2, n); 
  spline(x, y, n, 1.0e30, 1.0e30, d2);

  /** find slopes for extrapolation at ends **/
  if (l == TRUE) {
    s1 = (y[1] - y[0])/(x[1] - x[0]);
    z1 = (x[1]*y[0] - x[0]*y[1])/(x[1] - x[0]);
    sN = (y[n-1] - y[n-2])/(x[n-1] - x[n-2]);
    zN = (x[n-1]*y[n-2] - x[n-2]*y[n-1])/(x[n-1] - x[n-2]);
  }

  /** print out spline fit **/
  for (i=min; i<=max; i+=del) {
    val = splint(x, y, d2, n, i);

    if (l == TRUE) {
      if (i < x[0]) {
	val = (s1 * i) + z1;
      } else if (i > x[n-1]) {
	val = (sN * i) + zN;
      }
    } else if (e == TRUE) {
      if (i < x[0]) {
	val = y[0];
      } else if (i > x[n-1]) {
	val = y[n-1];
      }
    }

    printf("%8.5f %8.5f\n", i, val);
  }

  exit(0);
}
/*---------------------------------------------------------------------------*/
