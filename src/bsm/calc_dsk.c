/*
  Function : calc_dsk.c
  Purpose  : Bahcall - Soneira Galaxy Model. 
             Calculate disk density distribution.
  History  : Began: 10 June 1991. Last edit: 30 June 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca).
  Comments : 1. Scale height for m-s stars needs to be a function.
*/

#include "bsm.h"

void calc_dsk(BOOL zed, Param *pm, Lumfn *lf, Model *ml, Color *cl, Numbr *nm)
{
  REAL sinb, cosb, cosbl, cosl, cos2b;  /* trigonometric identities         */
  REAL m_abs;                           /* abs. mag. of current step        */
  REAL m_app;                           /* app. mag. of current step        */
  int  mind;                            /* abs. mag index                   */
  REAL absmag;                          /* absorption in magnitudes         */
  REAL vol;                             /* volume of current volume element */
  REAL tmp;                             /* tmp variable for speed           */
  REAL tot;                             /* total counts over l.o.s. and LF  */
  REAL znm;                             /* total counts over LF             */
  REAL farea;                           /* field area in steradians         */
  REAL dnms;                            /* counts from vol. element (m-s)   */
  REAL dng;                             /* counts from vol. element (giant) */
  REAL dnt;                             /* counts from vol. element (total) */
  REAL fms;                             /* frac. of stars on m-s            */
  REAL fg;                              /* frac. of stars on giant branch   */
  int  num_r;                           /* no. of points along l.o.s.       */
  REAL rmax;                            /* max. distance to integrate to    */
  REAL r;                               /* distance of current step         */

  REAL z;                               /* height above plane               */
  REAL x;                               /* distance from Galactic Centre    */
  REAL sh;                              /* scale height for ms stars        */
  REAL sh_a;                            /* scale height slope               */
  REAL sh_b;                            /* scale height intercept           */

  int  j, k;                            /* loop variables                   */

  /** compute some useful quantities **/
  sinb  = sin(fabs(ml->b2)*PI/180.0);
  cosb  = cos(ml->b2*PI/180.0);
  cosl  = cos(ml->l2*PI/180.0);
  cosbl = cosb*cosl;
  cos2b = cosb*cosb;
  farea = ml->omega * SQD2ST;

  /** disk scale height slope/intercept **/
  /** if heights are the same use a constant scale height **/
  if (ml->dsh_f_h == ml->dsh_b_h) {
    sh_a = 0.000;
    sh_b = ml->dsh_f_h;
  } else {
    sh_a = (ml->dsh_f_h - ml->dsh_b_h) / (ml->dsh_f_m - ml->dsh_b_m);
    sh_b = ml->dsh_b_h - (sh_a * ml->dsh_b_m);
  }

  /** now integrate along line of sight **/
  rmax = (ml->b2 == 0.0) ? pm->r_max_d : pm->r0/sinb;

  num_r = (int) rmax/pm->dr;

  for (tot=0.0, j=0; j<num_r; j++) {
    r = j*pm->dr;
    if (r < pm->r_min) continue;
    
    /** calculate total absorption along l.o.s. at this distance **/
    absmag = obscure(pm->amode, ml->b2, r, pm->a) + pm->abs;
    
    z = r*sinb;
    x = sqrt(pm->r0*pm->r0 + r*r*cos2b - 2.0*r*pm->r0*cosbl);
    vol = r * r * farea * pm->dr * pm->dm_abs;
    tmp = vol*exp(-(x-pm->r0)/pm->psl_d);

    /** step through luminosity function **/
    for (znm = 0.0, k=0; k<lf->nl; k++) {
      m_abs = pm->m_brd + k*pm->dm_abs;

      /** calculate apparent magnitude **/
      m_app = m_abs + 5.0*log10(r/10.0) + absmag;
      if (m_app > pm->ma_dim || m_app < pm->ma_brt) continue;
      
      /** specify scale heights for main sequence stars **/
      sh = sh_a * m_abs + sh_b;
      if (sh < ml->dsh_b_h) sh = ml->dsh_b_h;
      if (sh > ml->dsh_f_h) sh = ml->dsh_f_h;
      
      fms = nm->fms[k];
      fg  = 1.0 - fms;
      
      /** contribution by this vol. element to counts **/
      dng  = tmp*lf->d[k]*fg*exp(-z/pm->gsh_d);
      dnms = tmp*lf->d[k]*fms*exp(-z/sh);
      dnt  = dng + dnms;

      /** total contribution for this (distance) step **/
      znm += dnt;

      /** fill in colour distribution **/
      mind = (int) ((m_abs - pm->m_brd)/pm->dm_abs) + 1;

      col_dist(DSK, m_abs, m_app, dnms, dng, 
	       cl->dms[mind], cl->dg[mind], pm, nm);
	  
      /** apparent magnitude bin **/
      mind = (int) floor((m_app-(pm->ma_brt - pm->dm_app/2.0))/pm->dm_app);
      if (mind >=0 && mind <= nm->nn) nm->num[DSK][mind] += dnt;
    }
      
    /** accumulate grand total **/
    tot += znm;

    /** possibly update Z distribution **/
    if (zed == TRUE) {
      nm->zdn[j] += znm;
      nm->zdr[j] = r;
    }

    /** if trivial conribution then stop **/
    if (znm < pm->c_fac*tot) break;
  }

  return;
}
/*---------------------------------------------------------------------------*/
