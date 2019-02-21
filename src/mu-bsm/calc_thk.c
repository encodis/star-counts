/*
  Function : calc_thk.c
  Purpose  : MU space. Bahcall - Soneira Galaxy Model. 
             Calculate thick disk density distribution.
  History  : Began: 10 June 1991. Last edit: 4 August 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca).
  Comments : 1. Obscuration model needs parameterising.
             2. Scale height for m-s stars needs to be a function.
*/

#include "mubsm.h"

void calc_thk(Param *pm, Lumfn *lf, Model *ml, Color *cl, Numbr *nm)
{
  REAL sinb, cosb, cosbl, cosl, cos2b;  /* trigonometric identities         */
  REAL mu;                              /* current m-M                      */
  REAL m_abs;                           /* abs. mag. of current step        */
  int  mind;                            /* abs. mag index                   */
  REAL absmag;                          /* absorption in magnitudes         */
  REAL vol;                             /* volume of current volume element */
  REAL tmp;                             /* tmp variable for speed           */
  REAL tot;                             /* total counts over l.o.s. and LF  */
  REAL znm;                             /* total counts over LF             */
  REAL farea;                           /* field area in steradians         */
  REAL norm;                            /* density normalization            */
  REAL dnms;                            /* counts from vol. element (m-s)   */
  REAL dng;                             /* counts from vol. element (giant) */
  REAL dnt;                             /* counts from vol. element (total) */
  REAL fms;                             /* frac. of stars on m-s            */
  REAL fg;                              /* frac. of stars on giant branch   */
  REAL r;                               /* distance of current step         */

  REAL z;                               /* height above plane               */
  REAL x;                               /* distance from Galactic Centre    */
  REAL sh;                              /* scale height for ms stars        */
  REAL sh_a;                            /* scale height slope               */
  REAL sh_b;                            /* scale height intercept           */

  int  j, k;                            /* loop variables                   */
  REAL r1, r2, dr;

  /** compute some useful quantities **/
  sinb  = sin(fabs(ml->b2)*PI/180.0);
  cosb  = cos(ml->b2*PI/180.0);
  cosl  = cos(ml->l2*PI/180.0);
  cosbl = cosb*cosl;
  cos2b = cosb*cosb;
  farea = ml->omega * SQD2ST;
  norm  = pm->dn[THK]/pm->dn[DSK];

  /** thick disk scale height slope/intercept **/
  /** if heights are the same use a constant scale height **/
  if (ml->tsh_f_h == ml->tsh_b_h) {
    sh_a = 0.000;
    sh_b = ml->tsh_f_h;
  } else {
    sh_a = (ml->tsh_f_h - ml->tsh_b_h) / (ml->tsh_f_m - ml->tsh_b_m);
    sh_b = ml->tsh_b_h - (sh_a * ml->tsh_b_m);
  }

  for (tot=0.0, j=0; j<nm->nn; j++) {
    mu = pm->mu_brt + j*pm->del_mu;
    
    m_abs = pm->mag - mu;
    
    r = solve4r(pm, ml, mu); 

    r1 = solve4r(pm, ml, mu+(pm->del_mu/2.0));
    r2 = solve4r(pm, ml, mu-(pm->del_mu/2.0));
    dr = r1 - r2;
    
    /** calculate total absorption along l.o.s. at this distance **/
    /*  absmag = obscure(pm->amode, ml->b2, r, pm->a) + pm->abs;  */
    
    z = r*sinb;
    x = sqrt(pm->r0*pm->r0 + r*r*cos2b - 2.0*r*pm->r0*cosbl);
    vol = r * r * farea * dr;
    tmp = vol*exp(-(x-pm->r0)/pm->psl_t);
    
    /** specify scale heights for main sequence stars **/
    sh = sh_a * m_abs + sh_b;
    if (sh < ml->tsh_b_h) sh = ml->tsh_b_h;
    if (sh > ml->tsh_f_h) sh = ml->tsh_f_h;
    
    mind = (int) ((m_abs - pm->m_brd)/pm->dm_abs) + 1;   

    fms = nm->fms[mind];
    fg  = 1.0 - fms;

    /** contribution by this vol. element to counts **/
    dng  = tmp*lf->d[mind]*fg*exp(-z/pm->gsh_t) * norm;
    dnms = tmp*lf->d[mind]*fms*exp(-z/sh) * norm;
    dnt  = dng + dnms;
    
    /** total contribution for this (distance) step **/
    znm += dnt;
    
    /** Fill in colour distribution **/
    mind = (int) ((m_abs - pm->m_brd)/pm->dm_abs) + 1;
    
    col_dist(THK, m_abs, dnms, dng, cl->tms[mind], cl->tg[mind], pm, nm);
    
    /** apparent magnitude bin **/
    mind = (int) floor((mu-(pm->mu_brt - pm->del_mu/2.0))/pm->del_mu);
    if (mind >=0 && mind <= nm->nn) nm->num[THK][mind] += dnt;
  }
  
  /** accumulate grand total **/
  tot += znm;

  return;
}
/*---------------------------------------------------------------------------*/
