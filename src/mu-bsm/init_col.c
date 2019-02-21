/* 
  Function : init_col.c
  Purpose  : MU space. Bahcall - Soneira Galaxy Model. 
             Initialize and compute color distribution.
  History  : Began: 18 June 1991. Last edit: 3 August 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. Function is given the address of the color structure cl
                set up in bacson.c. Then it can write to those elements.
	     2. Uses modifications of the Numerical Recipes routines spline() 
	        and splint() for cubic spline interpolation.
*/

#include "mubsm.h"

void init_col(BOOL thick, Param *pm, Model *ml, Color *cl)
{
  int  j;
  REAL m;
  REAL cd, ce, c0, cc;

  int  dms_npt;                      /* pointers to c-m arrays               */
  REAL *dms_mag, *dms_col, *dms_d2;  /* _mag and _col assigned in read_cmd() */
  int  dgb_npt;
  REAL *dgb_mag, *dgb_col, *dgb_d2;
  int  tms_npt;                    
  REAL *tms_mag, *tms_col, *tms_d2;
  int  tgb_npt;
  REAL *tgb_mag, *tgb_col, *tgb_d2;
  int  sms_npt;                    
  REAL *sms_mag, *sms_col, *sms_d2;
  int  sgb_npt;
  REAL *sgb_mag, *sgb_col, *sgb_d2;

  REAL yp1, ypN;

  /** initialize color distn arrays **/
  cl->nc = (int) ((pm->m_dim - pm->m_brd)/pm->dm_abs) + 1;
  ALLOC(cl->dms,cl->nc,"cl->dms","init_col()");
  ALLOC(cl->dg,cl->nc,"cl->dg","init_col()");
  ALLOC(cl->sms,cl->nc,"cl->dms","init_col()");
  ALLOC(cl->sg,cl->nc,"cl->sg","init_col()");

  /** read files containing colour/magnitude tables **/
  read_dat(ml->dmsfn, ml->libry, &dms_npt, &dms_mag, &dms_col);
  read_dat(ml->dgbfn, ml->libry, &dgb_npt, &dgb_mag, &dgb_col);
  read_dat(ml->smsfn, ml->libry, &sms_npt, &sms_mag, &sms_col);
  read_dat(ml->sgbfn, ml->libry, &sgb_npt, &sgb_mag, &sgb_col);

  /** allocate space for _d2 arrays **/
  ALLOC(dms_d2,dms_npt,"dms_d2","init_col()");
  ALLOC(dgb_d2,dgb_npt,"dgb_d2","init_col()");
  ALLOC(sms_d2,sms_npt,"sms_d2","init_col()");
  ALLOC(sgb_d2,sgb_npt,"sgb_d2","init_col()");

  /** Calculate spline coefficients **/
  /** Use yp1, ypN > 0.99 x 10^(30) so that spline sets the boundary
      conditions for a natural spline (2nd derivative = 0) **/
  yp1 = 1.0e30;
  ypN = 1.0e30;

  spline(dms_mag, dms_col, dms_npt, yp1, ypN, dms_d2);
  spline(dgb_mag, dgb_col, dgb_npt, yp1, ypN, dgb_d2);
  spline(sms_mag, sms_col, sms_npt, yp1, ypN, sms_d2);
  spline(sgb_mag, sgb_col, sgb_npt, yp1, ypN, sgb_d2);

  /** Including thick disk ? **/
  if (thick == TRUE) {
    ALLOC(cl->tms,cl->nc,"cl->tms","init_col()");
    ALLOC(cl->tg,cl->nc,"cl->tg","init_col()");
    read_dat(ml->tmsfn, ml->libry, &tms_npt, &tms_mag, &tms_col);
    read_dat(ml->tgbfn, ml->libry, &tgb_npt, &tgb_mag, &tgb_col);
    ALLOC(tms_d2,tms_npt,"tms_d2","init_col()");
    ALLOC(tgb_d2,tgb_npt,"tgb_d2","init_col()");
    spline(tms_mag, tms_col, tms_npt, yp1, ypN, tms_d2);
    spline(tgb_mag, tgb_col, tgb_npt, yp1, ypN, tgb_d2);
  }

  /** Fill in MS and Giant colour arrays **/
  for (j=0; j<(cl->nc); j++) {
    m = pm->m_brd + j*pm->dm_abs;

    cl->dms[j] = splint(dms_mag, dms_col, dms_d2, dms_npt, m);
    cl->dg[j] = splint(dgb_mag, dgb_col, dgb_d2, dgb_npt, m);

    if (m > dgb_mag[dgb_npt-1]) {
      cl->dg[j] = splint(dms_mag, dms_col, dms_d2, dms_npt, m);
    }

    if (thick == TRUE) {
      cl->tms[j] = splint(tms_mag, tms_col, tms_d2, tms_npt, m);
      cl->tg[j] = splint(tgb_mag, tgb_col, tgb_d2, tgb_npt, m);
	  
      if (m > tgb_mag[tgb_npt-1]) {
	cl->tg[j] = splint(tms_mag, tms_col, tms_d2, tms_npt, m);
      }
    }

    cl->sms[j] = splint(sms_mag, sms_col, sms_d2, sms_npt, m);
    cl->sg[j] = splint(sgb_mag, sgb_col, sgb_d2, sgb_npt, m); 
    
    if (m > sgb_mag[sgb_npt-1]){
      cl->sg[j] = splint(sms_mag, sms_col, sms_d2, sms_npt, m);
    }
  }

  /** Initialize Gaussian convolution function **/

  /* Go to 4 sigma each side of 0, ng must be odd for symmetry */
  cd = pm->s_col;                           /* specify colour dispersion  */
  ce = pm->d_col;

  cl->ng = (int) ((2.0*4.0*cd)/ce);
  if (2*(cl->ng/2) == cl->ng) cl->ng++;

  c0 = (cl->ng/2)*ce;

  ALLOC(cl->gcf,cl->ng,"cl->gcf","init_col()");

  for (j=0; j<(cl->ng); j++) {
    cc = j*ce;
    cl->gcf[j] = exp(-((cc-c0)*(cc-c0))/(2.0*cd*cd))*ce/(cd*sqrt(2.0*PI));
  }

  return;
}
/*---------------------------------------------------------------------------*/
