/* 
   Function : init_lum.c
   Purpose  : MU space. Bahcall - Soneira Galaxy Model. 
              Initialize and compute disk and spheroid luminosity function.
   History  : Began: 30 May 1991. Last edit: 4 August 1994.
   Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
   Comments : 3. The analytic form gives N(M_v) - which is not very easy to
                 interpolate on due to the large gradients. So the LF files
		 contain information in the form:  M_v  log(N(M_v)). This 
		 means that init_lumfn() now takes the antilog, once all the
		 spline fitting and interpolation has been done.
*/

#include "mubsm.h"

void init_lum(BOOL thick, Param *pm, Model *ml, Lumfn *lf)
{
  int  dlf_npt;                     /* pointers to lf arrays                 */
  REAL *dlf_num, *dlf_mag, *dlf_d2; /* _num and _mag allocated in read_lum() */
  int  tlf_npt;
  REAL *tlf_num, *tlf_mag, *tlf_d2;
  int  slf_npt;
  REAL *slf_num, *slf_mag, *slf_d2;

  REAL mlf;
  REAL yp1, ypN;                   /* 1st derivatives at end points */

  int  i;                          /* temporary loop variable */

  /** Allocate memory for the LF structure **/
  lf->nl = ((pm->m_dim - pm->m_brd)/pm->dm_abs) + 1;
  ALLOC(lf->d,lf->nl,"lf->d","init_lum()");
  ALLOC(lf->s,lf->nl,"lf->s","init_lum()");

  /** read files containing luminosity function data **/
  read_dat(ml->dlffn, ml->libry, &dlf_npt, &dlf_mag, &dlf_num);
  read_dat(ml->slffn, ml->libry, &slf_npt, &slf_mag, &slf_num);

  /** allocate space for _d2 arrays **/
  ALLOC(dlf_d2,dlf_npt,"dlf_d2","init_lum()");
  ALLOC(slf_d2,slf_npt,"slf_d2","init_lum()");

  /** Calculate spline coefficients **/
  /** Use yp1, ypN > 0.99 x 10^(30) so that spline sets the boundary
      conditions for a natural spline (2nd derivative = 0) **/
  yp1 = 1.0e30;
  ypN = 1.0e30;

  spline(dlf_mag, dlf_num, dlf_npt, yp1, ypN, dlf_d2);
  spline(slf_mag, slf_num, slf_npt, yp1, ypN, slf_d2);

  /** Including thick disk ? **/
  if (thick == TRUE) {
    ALLOC(lf->t,lf->nl,"lf->t","init_lum()");
    read_dat(ml->tlffn, ml->libry, &tlf_npt, &tlf_mag, &tlf_num);
    ALLOC(tlf_d2,tlf_npt,"tlf_d2","init_lum()");
    spline(tlf_mag, tlf_num, tlf_npt, yp1, ypN, tlf_d2);
  }

  /** Compute L.F. in steps of dm_abs **/
  for (i=0; i<(lf->nl); i++) {
    mlf = pm->m_brd + (i*pm->dm_abs);

    /** must clamp dim L.F. to constant value = LF(mc) **/
    lf->d[i] = splint(dlf_mag, dlf_num, dlf_d2, dlf_npt, mlf);
    lf->d[i] = pow(10.0,lf->d[i]);
    
    if (thick == TRUE) {
      lf->t[i] = splint(tlf_mag, tlf_num, tlf_d2, tlf_npt, mlf);
      lf->t[i] = pow(10.0,lf->t[i]);
    }

    lf->s[i] = splint(slf_mag, slf_num, slf_d2, slf_npt, mlf);
    lf->s[i] = pow(10.0,lf->s[i]);
  }
  
  return;
}
/*---------------------------------------------------------------------------*/
