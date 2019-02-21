/*
  Function : read_lum.c
  Purpose  : MU space. Bahcall - Soneira Galaxy Model.
             Read files containing luminosity function data.
  History  : Began: 31 October 1991. Last edit: 28 April 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. File format for this function is:
		   mag[1]    count[1]
		   mag[2]    count[2]
		   ...
		   mag[N]    count[N]
	     2. Function now looks in CWD (.) for the file, then in the
	        library.
*/

#include "mubsm.h"

void read_lum(int mode, Model *ml, int *npt, REAL **pn, REAL **pm)
{
  FILE *inp;
  char file1[MAXFCH];
  char file2[MAXFCH*2];
  char line[MAXFCH];
  int  i;
  int  n;                                   /* number of allocations        */

  /** set up filename **/
  switch (mode) {
  case DSK :
    strcpy(file1,ml->dlffn);
    break;
  case THK :
    strcpy(file1,ml->tlffn);
    break;
  default :
    strcpy(file1,ml->slffn);
  }

  /** find file **/
  if ((inp = fopen(file1,"r")) == NULL) {
    strcpy(file2,ml->libry);
    strcat(file2,file1);
    if ((inp = fopen(file2,"r")) == NULL) {
      quit_bsm(ERR_OPEN,file1,"read_lum()");
    }
  }

  /** read file **/
  /** allocate basic amount of memory **/
  ALLOC(*pn,MBLOCK,"*pn","read_lum()");
  ALLOC(*pm,MBLOCK,"*pm","read_lum()");

  i = 0; n = 1;

  /** read file until end **/
  while (fgets(line,MAXFCH,inp)) {
    if (i+1 == n*MBLOCK) {
      n++;
      REALLOC(*pn,n*MBLOCK,"*pn","read_lum()");
      REALLOC(*pm,n*MBLOCK,"*pm","read_lum()");
    }
    if (line[0] != '#') {
      sscanf(line,"%lf %lf",*pm+i,*pn+i);
      i++;
    }
  }
  
  /** now trim array sizes **/
  *npt = i;
  REALLOC(*pn,i,"*pn","read_lum()");
  REALLOC(*pm,i,"*pm","read_lum()");
  
  fclose(inp);
	
  return;
}
/*---------------------------------------------------------------------------*/
