/*
   Function : readdata.c
   Purpose  : Read two-column data from file or stdin.
   History  : Began: 27 February 1994. Last edit: 18 May 1994.
   Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
   Comments : 1. Reads two columns of data from file. Returns number of lines
                 read.
	      2. Reads from stdin if file is NULL.
	      3. Comment lines in input begin with "#".
*/

#include "gmutil.h"
#define LENGTH 129
#define MBLOCK 20

int readdata(char *file, double **x, double **y)
{
  FILE *inp;
  int  i,j;
  char line[LENGTH];

  if (strlen(file) != 0) {
    inp = fopen(file,"r");
  } else {
    inp = stdin;
  }

  if (inp != NULL) {
    /** allocate basic amount of memory **/
    Alloc(*x, MBLOCK); Alloc(*y, MBLOCK);
    i = 0; j = 1;

    /** read file until end **/
    while (fgets(line,LENGTH,inp)) {
      if (i+1 == j*MBLOCK) {
	j++;
	ReAlloc(*x, j*MBLOCK); ReAlloc(*y, j*MBLOCK);
      }
      if (line[0] != '#') {
	sscanf(line,"%lf %lf",*x+i,*y+i);
	i++;
      }
    }
    
    /** now trim array sizes **/
    ReAlloc(*x, i); ReAlloc(*y, i);
    fclose(inp);
  } else {
    EROPN; exit(1);
  } 

  return i;
}
/*---------------------------------------------------------------------------*/
