/*
   Program : add2egm
   Function: External Galaxy Model.
             Add up counts in 2 component galaxy model.
   History : Began: 14 August 1994. Last edit: 16 August 1994.
   Author  : P.J.C.Hodder (hodder@geop.ubc.ca)
   Usage   : egm | add2egm bright faint
   Comments: 1. A bit of a hack really...
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define ALL 0
#define DSK 1
#define SPH 2
#define TOT 3

#define USAGE fprintf(stderr,"Usage: add2egm [-d|-s|-t] br ft < egm_file \n")

void main(int argc, char **argv)
{
  int    a = 0, p = ALL;
  char   line[1024];
  double br, ft;
  double m, d, s, t;
  double dsk = 0.0, sph = 0.0, tot = 0.0;

  /** parse command line **/
  if (argc > 1) {
    if (!strcmp(argv[1],"-d")) { 
      p = DSK; argc--; a = 1;
    } else if (!strcmp(argv[1],"-s")) { 
      p = SPH; argc--; a = 1;
    } else if (!strcmp(argv[1],"-t")) { 
      p = TOT; argc--; a = 1;
    } 
  }

  /* check args */
  if (argc < 3 || argc > 4) { USAGE; exit(1); }

  br = atof(argv[a+1]);
  ft = atof(argv[a+2]);

  if (br > ft) { USAGE; exit(1); }

  /* read past header */
  while (fgets(line,1024,stdin)) {
    if (line[0] != '#') break;
  }
  
  /* last line read was the first one we're interested in */
  sscanf(line,"%*lf %lf %*lf %lf %*lf %lf %*lf %lf %*lf", &m, &d, &s, &t);

  if (m >= br && m <= ft) { dsk += d; sph += s; tot += t; }

  /* now read the rest of the block */
  while (fgets(line,1024,stdin)) {
    if (line[0] == '#') break;

    sscanf(line,"%*lf %lf %*lf %lf %*lf %lf %*lf %lf %*lf", &m, &d, &s, &t);

    if (m >= br && m <= ft) { dsk += d; sph += s; tot += t; } 
  }

  /* print out results */
  switch (p) {
  case ALL :
    printf("[%5.2f - %5.2f]:  DSK = %g   SPH = %g   TOT = %g\n", 
	   br, ft, dsk, sph, tot);
    break;
  case DSK :
    printf("%g\n", dsk);
    break;
  case SPH :
    printf("%g\n", sph);
    break;
  case TOT :
    printf("%g\n", tot);
    break;
  }

  exit(0);
}
/*---------------------------------------------------------------------------*/
