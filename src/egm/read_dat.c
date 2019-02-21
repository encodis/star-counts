/*
  Function : read_dat.c
  Purpose  : External Galaxy Model.
             Read files in two column format.
  History  : Began: 28 June 1994. Last edit: 1 July 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. Function looks in CWD (.) for the file, then in the library.
             2. Reads two column data, ignores comments (lines beginning
	        with a #).
*/

#include "egm.h"

void read_dat(char *file, char *libry, int *npt, double **x, double **y)
{
  FILE *inp;
  char xfile[MAXFCH*2];                     /* extended fn with libry path  */
  char line[MAXFCH];
  int  i;
  int  n;                                   /* number of allocations        */

  /** find file **/
  if ((inp = fopen(file,"r")) == NULL) {
    strcpy(xfile,libry);
    strcat(xfile,file);
    if ((inp = fopen(xfile,"r")) == NULL) {
      quit_egm(ERR_OPEN,file,"read_dat()");
    }
  }

  /** allocate basic amount of memory **/
  ALLOC(*x,MBLOCK,"*x","read_dat()");
  ALLOC(*y,MBLOCK,"*y","read_dat()");

  i=0; n=1;
  
  /** read file until end **/
  while (fgets(line,MAXFCH,inp)) {
    if (i+1 == n*MBLOCK) {
      n++;
      REALLOC(*x,n*MBLOCK,"*x","read_dat()");
      REALLOC(*y,n*MBLOCK,"*y","read_dat()");
    }
    if (line[0] != '#') {
      sscanf(line,"%lf %lf",*x+i,*y+i);
      i++;
    }
  }
  
  /** now trim array sizes **/
  *npt = i;
  REALLOC(*x,i,"*x","read_dat()");
  REALLOC(*y,i,"*y","read_dat()");
  
  fclose(inp);
  
  return;
}
/*---------------------------------------------------------------------------*/
