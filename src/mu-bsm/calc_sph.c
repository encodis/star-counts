/*
  Function : calc_sph.c
  Purpose  : MU space. Bahcall - Soneira Galaxy Model. 
             Calculate spheroid density distribution.
  History  : Began: 10 June 1991. Last edit: 4 August 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca).
  Comments : See also comments in disk.c.
*/

#include "mubsm.h"

#define bd 7.66924944
#define c1 4.6132E-2/2.0
#define c2 PI/(8.0*bd)

void calc_sph(Param *pm, Lumfn *lf, Model *ml, Color *cl, Numbr *nm)
{
  REAL m_abs;                           /* abs. mag. of current step        */
  REAL mu;                              /* current m-M                      */
  int  mind;                            /* abs. mag index                   */
  REAL absmag;                          /* absorption in magnitudes         */
  REAL vol;                             /* volume of current volume element */
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

  REAL x, s;                            /* used to calc. logarithmic step   */
  REAL den_r0;                          /* density in solar neighbourhood   */
  REAL den;                             /* density at vol. element          */
  
  REAL sinb, cosb, cosl, cosbl;         /* useful values                    */
  REAL rcf, re, rj, rec, rc;            /* various parameters for sphd      */

  int  j, k;                            /* loop variables                   */
  REAL r1, r2, dr;

  /** compute field size **/
  farea = ml->omega * SQD2ST;
  norm = pm->dn[SPH]/pm->dn[DSK];

  /** compute some useful quantities **/
  sinb  = sin(fabs(ml->b2)*PI/180.0);
  cosb  = cos(ml->b2*PI/180.0);
  cosl  = cos(ml->l2*PI/180.0);
  cosbl = cosb*cosl;
  rcf = sqrt(cosb*cosb + sinb*sinb/pm->es/pm->es);
  re  = pm->rek/sqrt(pm->es);
  
  /** calculate density at r0 **/
  rj = pow(pm->r0/re,0.25);
  den_r0 = c1*exp(-bd*rj)/(rj*rj*rj)*sqrt(c2/rj);

  /** integrate along (l,b) direction **/
  for (tot=0.0, j=0; j<nm->nn; j++) {
    mu = pm->mu_brt + j*pm->del_mu;
    
    m_abs = pm->mag - mu;
    r = solve4r(pm, ml, mu); 
    
    r1 = solve4r(pm, ml, mu+(pm->del_mu/2.0));
    r2 = solve4r(pm, ml, mu-(pm->del_mu/2.0));
    dr = r1 - r2;
        
    /** calculate total absorption along l.o.s. at this distance **/
    /*  absmag = obscure(pm->amode, ml->b2, r, pm->a) + pm->abs;  */
    
    /** distance of volume element from centre of Galaxy **/
    vol = r * r * farea * dr;

    /** calculate density of spheroid **/
    
    /** r^1/4 density law **/
    rec = r*rcf;
    rc = sqrt(pm->r0*pm->r0 + rec*rec - 2.0*pm->r0*r*cosbl);
    rj = pow(rc/re,0.25);      
    den = c1*exp(-bd*rj)/(rj*rj*rj)*sqrt(c2/rj);
    
    /** scale density to local known spheroid star density **/
    den = (den / den_r0) * norm;
 
    /** how do we get lf[k]? m_abs is calculated. either work out the index
      (like mind = ...) or do a direct spline fit **/

    mind = (int) ((m_abs - pm->m_brd)/pm->dm_abs) + 1;
 
    dnt = vol * den * lf->s[mind];

    /** total contibution to this distance step **/
    znm += dnt;
      
    /** main sequence and giant fractions **/
    fms = 1.0;
    if (m_abs < pm->mturn) fms = 0.0;
    fg = 1.0 - fms;
    dng  = dnt * fg;
    dnms = dnt * fms;
    
    /** fill in colour distribution **/
    mind = (int) ((m_abs - pm->m_brd)/pm->dm_abs) +1 ;
    
    col_dist(SPH, m_abs, dnms, dng, 
	     cl->sms[mind], cl->sg[mind], pm, nm);
    
    /** apparent magnitude bin **/
    mind = (int) floor((mu-(pm->mu_brt - pm->del_mu/2.0))/pm->del_mu);
    if (mind >=0 && mind <= nm->nn) nm->num[SPH][mind] += dnt;
  }
    
  /** accumulate grand total **/
  tot += znm;
    
  return;
}
/*---------------------------------------------------------------------------*/
