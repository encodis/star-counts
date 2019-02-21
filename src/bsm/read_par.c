/*
  Function : read_par.c
  Purpose  : Bahcall - Soneira Galaxy Model. 
             Read model parameter file and fill in appropriate elements of 
	     the parameter structure.
  History  : Began: 10 June 1991. Last edit: 30 June 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca).
  Comments : 1. Front end for parsetok().
             2. Ignores comments (#).
*/

#include "bsm.h"

void read_par(BOOL thick, Param *pm, Model *ml)
{
  FILE *inp;
  char line[MAXFCH];

  if ((inp = fopen(ml->pfile,"r")) != NULL) {
    while (fgets(line,MAXFCH,inp)) {
      if (line[0] == '#') continue;
      parsetok(thick, line, pm, ml);
    }
    fclose(inp);
    return;
  } else {
    quit_bsm(ERR_OPEN,ml->pfile,"read_par()");
  }
}
/*---------------------------------------------------------------------------*/
