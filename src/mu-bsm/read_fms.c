/*
  Function : read_fms.c
  Purpose  : MU space. Bahcall - Soneira Galaxy Model.
             Read file containing fms data.
  History  : Began: 24 March 1992. Last edit: 28 April 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. File format is:
                   mag[1]      fraction[1]
                   mag[2]      fraction[2]
		   ...
                   mag[N]      fraction[N]
*/

#include "mubsm.h"

void read_fms(Model *ml, int *npt, REAL **pm, REAL **pf)
{
  FILE *inp;
  char file1[MAXFCH];
  char file2[MAXFCH*2];
  int  i;
  int  n;                                   /* number of allocations        */

  /** set up filename **/
  strcpy(file1,ml->fmsfn);

  /** find file **/
  if ((inp = fopen(file1,"r")) == NULL) {
    strcpy(file2,ml->libry);
    strcat(file2,file1);
    if ((inp = fopen(file2,"r")) == NULL) {
      quit_bsm(ERR_OPEN,file1,"read_fms()");
    }
  }

  /** read file **/
  /** allocate basic amount of memory **/
  ALLOC(*pm,MBLOCK,"*pm","read_fms()");
  ALLOC(*pf,MBLOCK,"*pf","read_fms()");

  i = 0; n = 1;

  /** read file until end **/
  while (1) {
    if (i+1 == n*MBLOCK) {
      n++;
      REALLOC(*pm,n*MBLOCK,"*pm","read_fms()");
      REALLOC(*pf,n*MBLOCK,"*pf","read_fms()");
    }
    if (fscanf(inp,"%lf %lf",*pm+i,*pf+i) == EOF) break;
    i++;
  }

  /** now trim array sizes **/
  *npt = i;
  REALLOC(*pm,i,"*pm","read_fms()");
  REALLOC(*pf,i,"*pf","read_fms()");

  fclose(inp);
  
  return;
}
/*---------------------------------------------------------------------------*/
