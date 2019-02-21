/*
  Function : read_par.c
  Purpose  : MU space. Bahcall - Soneira Galaxy Model. 
             Read model parameter file and fill in appropriate elements of 
	     the parameter structure.
  History  : Began: 10 June 1991. Last edit: 28 April 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca).
  Comments : 1. Using an idea by GD:-
                #define (or use enum) eg. APP_LIM  0
		Use an array of keywords, search the array for the keyword
		and get the index - then use the index in a switch.
*/

#include "mubsm.h"

void read_par(BOOL thick, Param *pm, Model *ml)
{
  int index;
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
