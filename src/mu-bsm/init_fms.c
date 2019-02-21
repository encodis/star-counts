/*
  Function : init_fms.c
  Purpose  : MU space. Bahcall - Soneira Galaxy Model.
             Initialise array with fraction of stars on main sequence.
  History  : Began: 24 March 1992. Last edit: 3 August 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. This function, and the modifications that accompanied it,
                removes the dependance of the fraction of stars on any hard 
		coded analytical form.
*/

#include "mubsm.h"

void init_fms(Param *pm, Model *ml, Numbr *nm)
{
  int  i;
  REAL mag;

  int  fms_npt;
  REAL *fms_mag, *fms_num, *fms_d2;

  REAL yp1, ypN;                   /* 1st derivatives at end points          */

  /** set array size **/
  nm->nf = (int) ((pm->m_dim - pm->m_brd)/pm->dm_abs) + 1;
  ALLOC(nm->fms,nm->nf,"nm->fms","init_fms()");

  /** read fms data **/
  read_dat(ml->fmsfn, ml->libry, &fms_npt, &fms_mag, &fms_num);

  /** allocate space for 2nd derivative **/
  ALLOC(fms_d2,fms_npt,"fms_d2","init_fms()");

  /** Calculate spline coefficients **/
  /** Use yp1, ypN > 0.99 x 10^(3) so that spline sets the boundary
      conditions for a natural spline (2nd derivative = 0) **/
  yp1 = 1.0e30;
  ypN = 1.0e30;

  spline(fms_mag, fms_num, fms_npt, yp1, ypN, fms_d2);

  /** Compute fms in steps of dm_abs **/
  for (i=0; i<(nm->nf); i++) {
    mag = pm->m_brd + i*pm->dm_abs;
    nm->fms[i] = splint(fms_mag, fms_num, fms_d2, fms_npt, mag);
    if (nm->fms[i] > 1.0) nm->fms[i] = 1.0;
  }

  return;
}
/*---------------------------------------------------------------------------*/
