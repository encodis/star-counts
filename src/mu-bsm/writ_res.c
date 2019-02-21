/*
  Function : writ_res.c
  Purpose  : MU space. Bahcall - Soneira Galaxy Model.
             Write number and color distributions to standard output.
  History  : Began: 25 November 1991. Last edit: 26 May 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. The array nm.num[][] contains the number of stars per unit
                magnitude, at the mean magnitude of the bin.  write_dist()
		must calculate and print the correct magnitudes during for
		the output.
*/

#include "mubsm.h"

void writ_res(Optar *op, Param *pm, Lumfn *lf, Model *ml, Color *cl, Numbr *nm)
{
  FILE *out;

  /** Open file **/
  if (strlen(ml->ofile) != 0) {
    if ((out = fopen(ml->ofile,"w")) == NULL) {
      quit_bsm(ERR_OPEN,ml->ofile,"writ_res()");
    }
  } else {
    out = stdout;
  }

  /** Write header information **/
  writ_hed(op, pm, ml, nm, out);

  /** Write out individual distributions **/
  writ_num(op->thick, pm, ml, nm, out);
  writ_col(op->thick, pm, ml, nm, out);

  if (op->v == TRUE) writ_vrb(op->thick, pm, ml, lf, cl, nm, out);

  return;
} 
/*---------------------------------------------------------------------------*/
