/*
  Function : read_cmd.c
  Purpose  : MU space. Bahcall - Soneira Galaxy Model.
             Read files containing colour/magnitude data.
  History  : Began: 22 October 1991. Last edit: 28 April 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. Data files for the main sequence and disk giants do not
                contain entries for the "mturn" and "bshift" variables.
	        "mode" is used to flag this.
	     2. File format for MS mode is:
		   mag[1]    colour[1]
		   mag[2]    colour[2]
		   ...
		   mag[N] colour[N]
	     3. File format for DG and SG modes is:
	           mturn     bshift
		   mag[1]    colour[1]
		   mag[2]    colour[2]
		   ...
		   mag[N]    colour[N]
	     4. Function now looks in CWD (.) for the file, then in the
	        library.
*/

#include "mubsm.h"

void read_cmd(int mode, Model *ml, int *npt, REAL **pm, REAL **pc)
{
  FILE *inp;
  REAL pt, pb;
  char file1[MAXFCH];
  char file2[MAXFCH*2];
  int  i;
  int  n;                                   /* number of allocations        */

  /** set up filename **/
  switch (mode) {
  case MS :
    strcpy(file1,ml->msdfn);
    break;
  case DG :
    strcpy(file1,ml->dgbfn);
    break;
  case TG :
    strcpy(file1,ml->tgbfn);
    break;
  case SG :
    strcpy(file1,ml->sgbfn);
    break;
  }

  /** find file **/
  if ((inp = fopen(file1,"r")) == NULL) {
    strcpy(file2,ml->libry);
    strcat(file2,file1);
    if ((inp = fopen(file2,"r")) == NULL) {
      quit_bsm(ERR_OPEN,file1,"read_cmd()");
    }
  }
	  
  /** read file **/
  switch (mode) {
  case DG :
    fscanf(inp,"%lf %lf",&pt,&pb);
    ml->dg_mturn  = pt;
    ml->dg_bshift = pb;
    break;
  case TG :
    fscanf(inp,"%lf %lf",&pt,&pb);
    ml->tg_mturn  = pt;
    ml->tg_bshift = pb;
    break;
  case SG :
    fscanf(inp,"%lf %lf",&pt,&pb);
    ml->sg_mturn  = pt;
    ml->sg_bshift = pb;
  }
  
  /** allocate basic amount of memory **/
  ALLOC(*pc,MBLOCK,"*pc","read_cmd()");
  ALLOC(*pm,MBLOCK,"*pm","read_cmd()");

  i = 0; n = 1;
  
  /** read file until end **/
  while (1) {
    if (i+1 == n*MBLOCK) {
      n++;
      REALLOC(*pc,n*MBLOCK,"*pc","read_cmd()");
      REALLOC(*pm,n*MBLOCK,"*pm","read_cmd()");
    }
    if (fscanf(inp,"%lf %lf",*pm+i,*pc+i) == EOF) break;
    i++;
  }
  
  /** now trim array sizes **/
  *npt = i;
  REALLOC(*pc,i,"*pc","read_cmd()");
  REALLOC(*pm,i,"*pm","read_cmd()");
  
  fclose(inp);
  
  return;
}
/*---------------------------------------------------------------------------*/
