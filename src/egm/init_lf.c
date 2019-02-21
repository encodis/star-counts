/* 
   Function : init_lf.c
   Purpose  : External Galaxy Model.
              Initialize and compute disk and spheroid luminosity function.
   History  : Began: 6 October 1992. Last edit: 1 July 1994.
   Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
   Comments : 1. Should rewrite for arbitrary number and type of components.
                 (Use a structure  of arrays +  dynamic  memory allocation).
	      2. Must implement linear interpolation/extrapolation for end
	         points. For now just set limits accordingly.
*/

#include "egm.h"

void init_lf(BOOL thick, Param *pm, Model *ml, Lumfn *lf)
{
  /** _num and _mag are allocated in read_lftab() **/
  /** pointers to disk lf arrays **/
  int     dlf_npt;
  double *dlf_num, *dlf_mag, *dlf_d2;

  /** pointers to thick disk lf arrays **/
  int     tlf_npt;
  double *tlf_num, *tlf_mag, *tlf_d2;

  /** pointers to spheroid lf arrays **/
  int     slf_npt;
  double *slf_num, *slf_mag, *slf_d2;
  double  mlf;

  double  yp1, ypN;                   /* 1st derivatives at end points */
  int     i;                          /* temporary loop variable */

  /** Allocate memory for the LF structure **/
  lf->nl = ((pm->m_dim - pm->m_bri)/pm->dm_abs) + 1;
  ALLOC(lf->d,lf->nl,"lf->d","init_lf()");
  ALLOC(lf->s,lf->nl,"lf->s","init_lf()");

  /** read files containing luminosity function data **/
  read_dat(ml->dlffn, ml->libry, &dlf_npt, &dlf_mag, &dlf_num);
  read_dat(ml->slffn, ml->libry, &slf_npt, &slf_mag, &slf_num);

  /** allocate space for _d2 arrays **/
  ALLOC(dlf_d2,dlf_npt,"dlf_d2","init_lf()");
  ALLOC(slf_d2,slf_npt,"slf_d2","init_lf()");

  /** Calculate spline coefficients **/
  /** Use yp1, ypN > 0.99 x 10^(30) so that spline sets the boundary
      conditions for a natural spline (2nd derivative = 0) **/
  yp1 = 1.0e30;
  ypN = 1.0e30;

  spline(dlf_mag, dlf_num, dlf_npt, yp1, ypN, dlf_d2);
  spline(slf_mag, slf_num, slf_npt, yp1, ypN, slf_d2);

  /** Including thick disk ? **/
  if (thick == TRUE) {
    ALLOC(lf->t,lf->nl,"lf->t","init_lf()");
    read_dat(ml->tlffn, ml->libry, &tlf_npt, &tlf_num, &tlf_mag);
    ALLOC(tlf_d2,tlf_npt,"tlf_d2","init_lf()");
    spline(tlf_mag, tlf_num, tlf_npt, yp1, ypN, tlf_d2);
  }

  /** Compute L.F. in steps of dm_abs **/

  for (i=0; i<(lf->nl); i++) {
    mlf = pm->m_bri + (i*pm->dm_abs);

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
