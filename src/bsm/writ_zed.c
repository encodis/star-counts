/*
  Function : writ_zed.c
  Purpose  : Bahcall - Soneira Galaxy Model.
             Write out  vertical density distribution.  Change format  if
	     using thick disk.
  History  : Began: 25 August 1992. Last edit: 28 April 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. Prints out vertical density distribution in format:
                ZDR  ZDN  [ZTR]  [ZTN]  ZSR  ZSN
	     2. Must find largest  array of ZDR, ZTR and  ZSR. The output
	        is a  bit  awkward because the  arrays  are of  different
		sizes, and you can't know "a priori" which will be larger
		(when writing this function).
*/

#include "bsm.h"

void writ_zed(BOOL thick, Numbr *nm, FILE *out)
{
  REAL r1, r2, r3;
  REAL n1, n2, n3;
  int i, rmax;

  /** If using thick disk use three columns else use two **/
  fprintf(out,"#\n");
  
  if(thick == TRUE) {
    rmax = (nm->nzd > nm->nzt) ? nm->nzd : nm->nzt;
    rmax = (rmax > nm->nzs) ? rmax : nm->nzs;
    fprintf(out,"#    ZDR        ZDN        ZTR        ZTN        ZSR        ZSN\n");
  } else {
    rmax = (nm->nzd > nm->nzs) ? nm->nzd : nm->nzs;
    fprintf(out,"#    ZDR        ZDN        ZSR        ZSN\n");
  }

  for (i=0; i<rmax; i++) {
    r1 = (i<nm->nzd) ? nm->zdr[i] : 0.0;
    n1 = (i<nm->nzd) ? nm->zdn[i] : 0.0;      
    fprintf(out,"%10.3f %10.3f ", r1, n1);
    
    if (thick == TRUE) {
      r2 = (i<nm->nzt) ? nm->ztr[i] : 0.0;
      n2 = (i<nm->nzt) ? nm->ztn[i] : 0.0;
      fprintf(out,"%10.3f %10.3f ", r2, n2);
    }
    
    r3 = (i<nm->nzs) ? nm->zsr[i] : 0.0;
    n3 = (i<nm->nzs) ? nm->zsn[i] : 0.0;
    fprintf(out,"%10.3f %10.3f \n", r3, n3);
  }
  
  return;
}
/*---------------------------------------------------------------------------*/
