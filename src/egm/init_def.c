/*
  Function : init_def.c
  Purpose  : External Galaxy Model.
             Initialize default parameters. 
  History  : Began: 6 October 1992. Last edit: 4 May 1995.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. These default values  themselves could  be  in a default  file.
                However this is good  enough for now. This  does mean  that the
		code should run even if the "parameter" file is empty  - you'll
		just get a "standard" answer.
*/

#include "egm.h"

void init_def(Param *pm, Model *ml, Optar *op)
{
  /** Initialize parameter structure **/
  pm->ma_brt = 16.0;
  pm->ma_dim = 26.0;
  pm->dm_app = 0.5;
  pm->dm_abs = 0.05;
  pm->m_dim  = 16.5;
  pm->m_bri  = -6.0;
  pm->mbc    = 16.0;
  pm->mfc    = 26.0;
  pm->dm_bin = 0.00;
  pm->c_fac  = 1.0E-6;
  pm->s_col  = 0.10;
  pm->d_col  = 0.005;
  pm->i_col  = 0.20;
  pm->max_col = 3.0;
  pm->min_col = 0.0;
  pm->dn[DSK] = 0.0;            /* these values are set by  */
  pm->dn[THK] = 0.0;            /* the calc_nor() function  */
  pm->dn[SPH] = 0.0;            /* & are used in calc_xxx() */
  pm->amode   = SA;
  pm->a[0]    = 100.0;
  pm->a[1]    = 0.15;
  pm->a[2]    = 0.165;
  pm->a[3]    = 1.192;
  pm->abs     = 0.000;
  pm->dabs    = 1.000;
  pm->es      = 0.8;
  pm->rek     = 2670.0;
  pm->rac     = 0.0;
  pm->psl_d   = 5500.0;
  pm->psl_t   = 5500.0;
  pm->gsh_d   = 250.0;
  pm->gsh_t   = 1300.0;  
  pm->dr_d    = 25.0;
  pm->dr_t    = 25.0;
  pm->dr_s    = 1000.0;
  pm->r_min   = 0.0;
  pm->r_max_d = 362500.0;
  pm->r_max_t = 362500.0;
  pm->r_max_s = 362500.0;

  /** Initialize model structure **/
  strcpy(ml->libry,EGMLIB);
  strcpy(ml->ofile,NULL_STR);
  ml->x0 = 23.74;
  ml->y0 = 23.74;
  ml->omega = 0.001;
  ml->inc = 77.5;
  ml->dist = 725000.0;
  strcpy(ml->den,NULL_STR);
  strcpy(ml->mag,"V");
  strcpy(ml->col,"B-V");

  /** Initialize colour magnitude data files **/
  strcpy(ml->dmsfn,"ms.vbv");
  strcpy(ml->dgbfn,"dskm67.vbv");
  strcpy(ml->tgbfn,"dskm67.vbv");
  strcpy(ml->sgbfn,"m13.vbv");

  /** Initialize luminosity function data files **/
  strcpy(ml->dlffn,"wielen.vlf");
  strcpy(ml->tlffn,"wielen.vlf");
  strcpy(ml->slffn,"dacosta.vlf");

  /** Initialize fraction on main-sequence data file **/
  strcpy(ml->fmsfn,"analytic.vfm");

  /** Initialize optional argument flags **/
  op->v        = FALSE;
  op->thick    = FALSE;
  op->far_disk = FALSE;
  op->far_thik = FALSE;
  op->far_sphd = FALSE;
  op->doms     = FALSE;

  return;
}
/*---------------------------------------------------------------------------*/
