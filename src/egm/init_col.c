/* 
  Function : init_col.c
  Purpose  : External Galaxy Model.
             Initialize and compute color distribution.
  History  : Began: 6 October 1992. Last edit: 3 March 1995.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. Function is given the address of the color structure cl
                set up in extgal.c. Then it can write to those elements.
*/

#include "egm.h"

void init_col(BOOL thick, BOOL doms, Param *pm, Model *ml, Color *cl)
{
  int    j;
  double m;
  double cd, ce, c0, cc;
  double yp1, ypN;

  /** pointers to c-m arrays **/
  /** _mag and _col are assigned in read_cmtab() **/

  int     ms_npt;                   
  double *ms_mag, *ms_col, *ms_d2; 
  int     dg_npt;                   
  double *dg_mag, *dg_col, *dg_d2; 
  int     tg_npt;                   
  double *tg_mag, *tg_col, *tg_d2; 
  int     sg_npt;
  double  *sg_mag, *sg_col, *sg_d2;

  /** initialize color distn arrays **/
  cl->nc = (int) ((pm->m_dim - pm->m_bri)/pm->dm_abs) + 1;
  ALLOC(cl->dg,cl->nc,"cl->dg","init_col()");
  ALLOC(cl->sg,cl->nc,"cl->sg","init_col()");

  /** read files containing colour/magnitude tables **/
  read_dat(ml->dgbfn, ml->libry, &dg_npt, &dg_mag, &dg_col);
  read_dat(ml->sgbfn, ml->libry, &sg_npt, &sg_mag, &sg_col);

  /** allocate space for _d2 arrays **/
  ALLOC(dg_d2,dg_npt,"dg_d2","init_col()");
  ALLOC(sg_d2,sg_npt,"sg_d2","init_col()");

  /** Calculate spline coefficients **/
  /** Use yp1, ypN > 0.99 x 10^(30) so that spline sets the boundary
      conditions for a natural spline (2nd derivative = 0) **/
  yp1 = 1.0e30; ypN = 1.0e30;

  spline(dg_mag, dg_col, dg_npt, yp1, ypN, dg_d2);
  spline(sg_mag, sg_col, sg_npt, yp1, ypN, sg_d2);

  /** Including M-S ? **/
  if (doms == TRUE) {
    ALLOC(cl->ms,cl->nc,"cl->ms","init_col()");
    read_dat(ml->dmsfn, ml->libry, &ms_npt, &ms_mag, &ms_col);
    ALLOC(ms_d2,ms_npt,"ms_d2","init_col()");
    spline(ms_mag, ms_col, ms_npt, yp1, ypN, ms_d2);
  }

  /** Including thick disk ? **/
  if (thick == TRUE) {
    ALLOC(cl->tg,cl->nc,"cl->tg","init_col()");
    read_dat(ml->tgbfn, ml->libry, &tg_npt, &tg_mag, &tg_col);
    ALLOC(tg_d2,tg_npt,"tg_d2","init_col()");
    spline(tg_mag, tg_col, tg_npt, yp1, ypN, tg_d2);
  }

  /** Fill in colour arrays **/
  for (j=0; j<(cl->nc); j++) {
    m = pm->m_bri + j*pm->dm_abs;
    
    if (doms == TRUE) cl->ms[j] = splint(ms_mag, ms_col, ms_d2, ms_npt, m);    
    cl->dg[j] = splint(dg_mag, dg_col, dg_d2, dg_npt, m);
    if (thick == TRUE) cl->tg[j] = splint(tg_mag, tg_col, tg_d2, tg_npt, m);
    cl->sg[j] = splint(sg_mag, sg_col, sg_d2, sg_npt, m); 
  }

  return;
}
/*---------------------------------------------------------------------------*/
