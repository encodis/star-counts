/*
  Function : calc_dsk.c
  Purpose  : External Galaxy Model.
             Calculate disk density distribution.
  History  : Began: 6 October 1992. Last edit: 7 July 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca).
  Comments : 1. Uses DIR flag (+/- 1) for direction of integration:
	        r = D - s for the near side, r = D + s for the far side.
	     2. Scaling by pm.dn now done in calc_nor().
*/

#include "egm.h"

void calc_dsk(int DIR, Param *pm, Lumfn *lf, Model *ml, Color *cl,
	      Optar *op, Numbr *nm)
{
  double sinb, cosb, cosbl, cosl, cos2b;  /* trigonometric identities        */
  double m_abs;                           /* abs. mag. of current step       */
  double m_app;                           /* app. mag. of current step       */
  int    mind;                            /* abs. mag index                  */
  double absmag;                          /* absorption in magnitudes        */
  double vol;                             /* volume of current volume element*/
  double tmp;                             /* tmp variable for speed          */
  double tot;                             /* total counts over l.o.s. and LF */
  double znm;                             /* total counts over LF            */
  double farea;                           /* field area in steradians        */
  double dnms;                            /* counts from vol. element (m-s)  */
  double dng;                             /* counts from vol. element (giant)*/
  double dnt;                             /* counts from vol. element (total)*/
  double fms;                             /* fraction on m-s                 */
  double fg;                              /* fraction on g-b                 */
  int    num_r;                           /* no. of points along l.o.s.      */
  double rmax;                            /* max. distance to integrate to   */
  double r;                               /* distance of element from plane  */
  double d;                               /* distance of element to observer */
  double z;                               /* height above plane              */
  double x;                               /* distance from galaxy centre     */
  int    j, k;                            /* loop variables                  */
  double mag;                             /* dummy variable                  */

  /** compute some useful quantities **/
  sinb  = sin(pm->b2);
  cosb  = cos(pm->b2);
  cosl  = cos(pm->l2);
  cosbl = cosb*cosl;
  cos2b = cosb*cosb;
  farea = ml->omega * SQD2ST;

  /** now integrate along line of sight **/
  rmax = pm->r_max_d;
  num_r = (int) rmax/pm->dr_d;

  for (tot=0.0, j=0; j<num_r; j++) {
    r = j*pm->dr_d;
    if (r < pm->r_min) continue;
    
    d = ml->dist + pm->rpk + (DIR * r);

    /** calculate total absorption along l.o.s. at this distance **/
    absmag = obscure(pm->amode, pm->b2, r, pm->a) + pm->abs;

    z = r*sinb;
    x = sqrt(pm->r0*pm->r0 + r*r*cos2b - 2.0*r*pm->r0*cosbl);
    vol = d * d * farea * pm->dr_d * pm->dm_abs;
    tmp = vol*exp(-(x - pm->r0)/pm->psl_d)*exp(-z/pm->gsh_d) * pm->dn[DSK];

    /** step through luminosity function **/
    for (znm = 0.0, k=0; k<lf->nl; k++) {
      m_abs = pm->m_bri + (k * pm->dm_abs);

      /** calculate apparent magnitude **/
      m_app = m_abs + 5.0*log10(d/10.0) + absmag;
      if (DIR == FAR) m_app += pm->dabs;
      if ((m_app > pm->ma_dim) || (m_app < pm->ma_brt)) continue;
      
      /** fraction on m-s & g-b **/
      if (op->doms == TRUE) {
	fms = nm->fms[k];
	fg  = 1.0 - fms;
      } else {
	fms = 0.0;
	fg  = 1.0;
      }

      /** contribution by this vol. element to counts **/
      dnms = tmp*lf->d[k]*fms;
      dng = tmp*lf->d[k]*fg;
      dnt = dnms + dng;

      /** total contribution for this (distance) step **/
      znm += dnt;

      /** Fill in colour distribution **/
      mind = (int) ((m_abs - pm->m_bri)/pm->dm_abs) + 1;
      
      if (op->doms == TRUE) {
	col_dist(DSK, m_abs, m_app, dnms, cl->ms[mind], dng, cl->dg[mind], 
		 pm, nm);
      } else {
	col_dist(DSK, m_abs, m_app, 0.0, 0.0, dng, cl->dg[mind], pm, nm);
      }

      /** apparent magnitude bin **/
      mind = (int) floor((m_app-(pm->ma_brt - pm->dm_app/2.0))/pm->dm_app);
      if (mind >= 0 && mind <= nm->nn) nm->num[DSK][mind] += dnms + dng;
    }
      
    /** accumulate grand total **/
    tot += znm;

    /** if trivial conribution then stop **/
    if (znm < pm->c_fac*tot) break;
  }

  return;
}
/*---------------------------------------------------------------------------*/
