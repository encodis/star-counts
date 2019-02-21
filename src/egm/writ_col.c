/*
  Function : writ_col.c
  Purpose  : External Galxy Model.
             Write out the colour distribution. Change format according to
	     number of components.
  History  : Began: 6 October 1992. Last edit: 7 February 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments :
*/

#include "egm.h"

void writ_col(BOOL thick, Param *pm, Model *ml, Numbr *nm, FILE *out)
{
  double c1, c2, c12;
  int i;

  /** Write out color distribution **/
  fprintf(out,"#\n");
  fprintf(out,"# COL:\n");

  /** If thick disk used, use four cols. else use three **/
  if (thick == TRUE) {
    fprintf(out,"#          %s               Nd        Nt        Ns"
	    "        NT\n", 
	    ml->col);
    
    for (i=0; i<(nm->nc); i++) {
      c2  = (i+1)*pm->i_col + pm->min_col;
      c1  = c2 - pm->i_col;
      c12 = (c1+c2)/2.0;
      
      fprintf(out,"%7.4f %7.4f %7.4f %9.3f %9.3f %9.3f %9.3f\n", 
	      c1, c12, c2, nm->col[DSK][i], nm->col[THK][i], nm->col[SPH][i],
	      nm->col[TOT][i]);
    }
  } else {
    fprintf(out,"#          %s               Nd        Ns        NT\n", 
	    ml->col);

    for (i=0; i<(nm->nc); i++) {
      c2  = (i+1)*pm->i_col + pm->min_col;
      c1  = c2 - pm->i_col;
      c12 = (c1+c2)/2.0;
      
      fprintf(out,"%7.4f %7.4f %7.4f %9.3f %9.3f %9.3f\n",
	      c1, c12, c2, nm->col[DSK][i], nm->col[SPH][i], nm->col[TOT][i]);
    }
  }
  
  return;
}
/*---------------------------------------------------------------------------*/
