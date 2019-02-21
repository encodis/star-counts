/*
  Function : writ_res.c
  Purpose  : External Galaxy Model.
             Write number and color distributions to standard output.
  History  : Began: 6 October 1992. Last edit: 17 May 1993.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. The array nm.num[][] contains the number of stars per unit
                magnitude, at the mean magnitude of  the bin.  write_res()
		must calculate and print the correct magnitudes during for
		the output.
	     2. Output goes to stdout unless the -o option is used.
*/

#include "egm.h"

void writ_res(Optar *op, Param *pm, Lumfn *lf, Model *ml, Color *cl, Numbr *nm)
{
  FILE *out;

  /** Open file **/
  if (strlen(ml->ofile) != 0) {
    if ((out = fopen(ml->ofile,"w")) == NULL) {
      quit_egm(ERR_OPEN,ml->ofile,"writ_res()");
    }
  } else {
    out = stdout;
  }

  /** Write header information **/
  writ_hed(op, pm, lf, ml, nm, out);

  /** Write out individual distributions **/
  writ_num(op->thick, pm, ml, nm, out);
  writ_col(op->thick, pm, ml, nm, out);

  if (op->v == TRUE) writ_vrb(op->thick, op->doms, pm, ml, lf, cl, nm, out);

  return;
} 
/*---------------------------------------------------------------------------*/
