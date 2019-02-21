/*
  Function : read_par.c
  Purpose  : External Galaxy Model.
             Read model parameter file and fill in  appropriate elements of 
	     the parameter structure.
  History  : Began: 6 October 1992. Last edit: 2 March 1995.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca).
  Comments : 1. The thick disc flag can be set in the parameter file. It is
	        also used  in this function to  set DN correctly. Therefore
		the  "THICK"  statement must be  included in  the parameter
		file BEFORE the  "DN" statement if it is  to work properly.
		The command line switch "-t" will override this, of course.
*/

#include "egm.h"
#include "keyword.h"

void read_par(BOOL thick, Param *pm, Model *ml, Optar *op)
{
  FILE *inp;
  char line[MAXFCH];

  /** read parameter file **/
  if ((inp = fopen(ml->pfile,"r")) != NULL) {
    while (fgets(line,MAXFCH,inp)) {
      if (line[0] == '#') continue;
      parsetok(thick, line, pm, ml, op); 
    }
    fclose(inp);
    return;
  } else {
    quit_egm(ERR_OPEN,ml->pfile,"read_par()");
  }
}
/*---------------------------------------------------------------------------*/
