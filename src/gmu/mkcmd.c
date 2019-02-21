/*
  Program  : mkcmd
  Purpose  : Galaxy Model Utility.
             Make new (composite) CMDs from old ones.
  History  : Began: 26 June 1994. Last edit: 26 April 1995.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. Output goes to stdout.
	     2. Other parameters (and their order) are mandatory.
	     3. CMD data must be monotonic increasing but spline fitting
	        is not done here.
	     4. mkcmd 1.0 file == apply blue shift of 1.0 to file
	        mkcmd -2.0 1.0 file1 file2 == make gb cmd using file1 as the
		MS CMD and file2 as the original GB CMD.
*/

#include "gmutil.h"
#define USAGE fprintf(stderr,"Usage: mkcmd ce cmd | mto [ce] mscmd gbcmd\n")

void main(int argc, char **argv)
{
  double *ms_mag, *ms_col, *ms_d2, *gb_mag, *gb_col, *gb_d2;
  double mt, ce;
  double m, col, mb, mf, dm;
  int    i, nms, ngb;
  char   msfile[81], gbfile[81];

  /** check num args **/
  if (argc < 3 || argc > 5) { USAGE; exit(1); }

  /** make a CMD **/
  if (argc == 3) {
    ce = atof(argv[1]);
    strcpy(msfile,argv[2]);
    nms = readdata(msfile, &ms_mag, &ms_col);
    /** production note **/
    printf("#"); for (i=0; i<argc; i++) printf("%s ",argv[i]); printf("\n");
    for (i=0; i<nms; i++) printf("%f %f\n", ms_mag[i], ms_col[i] + ce);
  } else {
    mt = atof(argv[1]);
    if (argc == 4) {
      ce = 0.0;
      strcpy(msfile,argv[2]);
      strcpy(gbfile,argv[3]);
    } else {
      ce = atof(argv[2]);
      strcpy(msfile,argv[3]);
      strcpy(gbfile,argv[4]);
    }

    nms = readdata(msfile, &ms_mag, &ms_col);
    Alloc(ms_d2, nms); 
    spline(ms_mag, ms_col, nms, 1.0e30, 1.0e30, ms_d2);

    ngb = readdata(gbfile, &gb_mag, &gb_col);
    Alloc(gb_d2, ngb); 
    spline(gb_mag, gb_col, ngb, 1.0e30, 1.0e30, gb_d2);

    mb = (ms_mag[0] < gb_mag[0]) ? ms_mag[0] : gb_mag[0];
    mf = (ms_mag[nms-1] > gb_mag[ngb-1]) ? ms_mag[nms-1] : gb_mag[ngb-1];
    dm = ms_mag[1] - ms_mag[0];
    
    /** production note **/
    printf("#"); for (i=0; i<argc; i++) printf("%s ",argv[i]); printf("\n");
    
    for (m=mb; m<=mf; m+=dm) {
      col = splint(gb_mag, gb_col, gb_d2, ngb, m);
      if (m > mt) {
	col = splint(ms_mag, ms_col, ms_d2, nms, m) + ce;
      }
      printf("%f %f\n", m, col);
    }
  } 

  exit(0);
}
/*---------------------------------------------------------------------------*/
