/*
  Function : calc_spd.c
  Purpose  : External Galaxy Model.
             Calculate spheroid density distribution.
  History  : Began: 6 October 1992. Last edit: 16 May 1995.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca).
  Comments : 1. See also comments in calc_dsk.c.
             2. Fraction of stars on m-s NOT included here. Therefore the
	        call to col_dist() has dnms = 0.0 and cms = 0.0.
	     3. Scaling by pm.dn now done by calc_nor().
*/

#include "egm.h"

void calc_spd(int DIR, Param *pm, Lumfn *lf, Model *ml, Color *cl,
	      Optar *op, Numbr *nm)
{
  double m_abs;                           /* abs. mag. of current step       */
  double m_app;                           /* app. mag. of current step       */
  int    mind;                            /* abs. mag index                  */
  double absmag = 0.0;                    /* absorption in magnitudes        */
  double vol;                             /* volume of current volume element*/
  double tot;                             /* total counts over l.o.s. and LF */
  double znm;                             /* total counts over LF            */
  double farea;                           /* field area in steradians        */
  double dng;                             /* counts from vol. element (giant)*/
  double dnt;                             /* counts from vol. element (total)*/
  int    num_r;                           /* no. of points along l.o.s.      */
  double rmax;                            /* max. distance to integrate to   */
  double r;                               /* distance of element from plane  */
  double d;                               /* distance of element to observer */
  double x, s;                            /* used to calc. logarithmic step  */
  double dr;                              /* thickness of volume element     */
  double den_r0;                          /* density in solar neighbourhood  */
  double den;                             /* density at vol. element         */
  double rcf, re, rj, rec, rc;            /* used in density calc.           */
  double sinb, cosb, cosl, cosbl;         /* some useful quantities          */
  int    j, k;                            /* loop variables                  */

  /** compute field size **/
  farea = ml->omega * SQD2ST;

  /** compute some useful quantities **/
  sinb  = sin(pm->b2);
  cosb  = cos(pm->b2);
  cosl  = cos(pm->l2);
  cosbl = cosb*cosl;
  rcf = sqrt(cosb*cosb + sinb*sinb/(pm->es*pm->es));
  re  = pm->rek/sqrt(pm->es);
  
  /** calculate local value of density **/
  rj = pow(pm->r0/re,0.25);
  den_r0 = C1*exp(-BD*rj)*sqrt(C2/rj)/(rj*rj*rj);

  /** maximum distance for integration in pc **/
  rmax = pm->r_max_s;

  /** Uncomment for LOGARITHMIC distance integration intervals
      s = 1.05; x = s - 1.0;
      num_r = log10(rmax) / log10(s);
      r = (pm->r_min == 0.0) ? 1.0 : pm->r_min;
  **/
  
  dr    = pm->dr_s;
  num_r = (int) (rmax/dr);
  
  /** integrate along (l,b) direction **/
  for (tot=0.0, j=0; j<num_r; j++) {
    
    /** Uncomment for LOGARITHMIC distance integration intervals
        r *= s; dr = r * x;
    **/

    if (DIR == FAR && j == 0) continue;

    r = j*dr;
    d = ml->dist + pm->rpk + (DIR * r);

    /** calculate total absorption along l.o.s. at this distance **/
    if (pm->r0 < pm->rac) {
      absmag = obscure(pm->amode, pm->b2, r, pm->a);
    }

    /** distance of volume element from centre of Galaxy **/
    vol = d * d * farea * dr;

    /** calculate density of spheroid **/
    rec = r*rcf; 
    
    rc = sqrt(pm->r0*pm->r0 + rec*rec - 2.0*pm->r0*r*cosbl); 
    rj = pow(rc/re,0.25);      
    
    den = C1*exp(-BD*rj)*sqrt(C2/rj)/(rj*rj*rj) * pm->dn[SPH] / den_r0;

    /** step through luminosity function **/
    for (znm = 0.0, k=0; k<lf->nl; k++) {
      m_abs = pm->m_bri + k*pm->dm_abs;
      if (m_abs < pm->m_bri) continue;

      m_app = m_abs + 5.0*log10(d/10.0) + absmag + pm->abs;

      if (DIR == FAR && pm->r0 < pm->rac) m_app += pm->dabs;

      if ((m_app > pm->ma_dim) || (m_app < pm->ma_brt)) continue;

      dnt = vol * den * lf->s[k] * pm->dm_abs;
	  
      /** total contibution to this distance step **/
      znm += dnt;
      dng  = dnt;
	  
      /** fill in colour distribution **/
      mind = (int) ((m_abs - pm->m_bri)/pm->dm_abs) + 1;
      
      col_dist(SPH, m_abs, m_app, 0.0, 0.0, dng, cl->sg[mind], pm, nm);

      /** apparent magnitude bin **/
      mind = (int) floor((m_app-(pm->ma_brt - pm->dm_app/2.0))/pm->dm_app);
      if (mind >= 0 && mind <= nm->nn) nm->num[SPH][mind] += dng;
    }

    /* printf(" %10.3f %10.3f %10.7f\n ", r, d, znm);  */

    /** accumulate grand total **/
    tot += znm;

    /** if trivial contribution then stop **/
    if (znm < pm->c_fac*tot) break;
  }

  return;
}
/*---------------------------------------------------------------------------*/
