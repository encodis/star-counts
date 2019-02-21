/*
  Function : calc_sph.c
  Purpose  : Bahcall - Soneira Galaxy Model. 
             Calculate spheroid density distribution.
  History  : Began: 10 June 1991. Last edit: 30 June 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca).
  Comments : 
*/

#include "bsm.h"

#define bd 7.66924944
#define c1 4.6132E-2/2.0
#define c2 PI/(8.0*bd)

void calc_sph(BOOL zed, Param *pm, Lumfn *lf, Model *ml, Color *cl, Numbr *nm)
{
  REAL m_abs;                           /* abs. mag. of current step        */
  REAL m_app;                           /* app. mag. of current step        */
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
  int  num_r;                           /* no. of points along l.o.s.       */
  REAL rmax;                            /* max. distance to integrate to    */
  REAL r;                               /* distance of current step         */

  REAL x, s;                            /* used to calc. logarithmic step   */
  REAL dr;                              /* thickness of volume element      */
  REAL den_r0;                          /* density in solar neighbourhood   */
  REAL den;                             /* density at vol. element          */
  
  REAL sinb, cosb, cosl, cosbl;         /* useful values                    */
  REAL rcf, re, rj, rec, rc;            /* various parameters for sphd      */

  int  j, k;                            /* loop variables                   */

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

  /** increment for LOGARITHMIC distance integration intervals **/
  s = 1.05;
  x = s - 1.0;

  /** initial distance in pc **/
  r = 1.0;
  
  /** maximum distance for integration in pc **/
  rmax = pm->r_max_s;
  num_r = log10(rmax) / log10(s);

  /** integrate along (l,b) direction **/
  for (tot=0.0, j=0; j<num_r; j++) {
    r *= s;
      dr = r * x;
    
    /** calculate total absorption along l.o.s. at this distance **/
    absmag = obscure(pm->amode, ml->b2, r, pm->a) + pm->abs;
    
    /** distance of volume element from centre of Galaxy **/
    vol = r * r * farea * dr * pm->dm_abs;
    
    /** calculate density of spheroid **/
    
    /** r^1/4 density law **/
    rec = r*rcf;
    rc = sqrt(pm->r0*pm->r0 + rec*rec - 2.0*pm->r0*r*cosbl);
    rj = pow(rc/re,0.25);      
    den = c1*exp(-bd*rj)/(rj*rj*rj)*sqrt(c2/rj);
    
    /** scale density to local known spheroid star density **/
    den = (den / den_r0) * norm;

    /** step through luminosity function **/
    for (znm = 0.0, k=0; k<lf->nl; k++) {
      m_abs = pm->m_brd + k*pm->dm_abs;
	  if (m_abs < pm->m_brs) continue;
      
      m_app = m_abs + 5.0*log10(r/10.0) + absmag;
      if (m_app > pm->ma_dim || m_app < pm->ma_brt) continue;
      
      dnt = vol * den * lf->s[k];
      
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
      
      col_dist(SPH, m_abs, m_app, dnms, dng, 
	       cl->sms[mind], cl->sg[mind], pm, nm);

      /** apparent magnitude bin **/
      mind = (int) floor((m_app-(pm->ma_brt - pm->dm_app/2.0))/pm->dm_app);
      if (mind >=0 && mind <= nm->nn) nm->num[SPH][mind] += dnt;
    }
    
    /** accumulate grand total **/
    tot += znm;
    
    /** possibly update Z distribution **/
    if (zed == TRUE) {
      nm->zsn[j] += znm;
      nm->zsr[j] = r;
    }

    /** if trivial contribution then stop **/
    if (znm < pm->c_fac*tot) break;
  }
  
  return;
}
/*---------------------------------------------------------------------------*/
