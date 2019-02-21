/*
  Function : init_def.c
  Purpose  : MU space. Bahcall - Soneira Galaxy Model. 
             Initialize default parameters. 
  History  : Began: 24 June 1991. Last edit: 3 August 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. These default values themselves could be in a default file.
                However this is good enough for now. This does mean that the
		code should run even if the "parameter" file is empty - you'll
		just get a "standard" answer.
*/

#include "mubsm.h"

void init_def(Param *pm, Model *ml, Optar *op)
{
  /** Initialize parameter structure **/
  pm->mag    = 20.0;
  pm->mu_brt = 0.0;
  pm->mu_dim = 25.0;
  pm->del_mu = 1.0;
  pm->dm_abs = 0.05;
  pm->m_dim  = 16.5;
  pm->m_brd  = -6.0;
  pm->m_brs  = -3.0;
  pm->mbc    =  0.0;
  pm->mfc    = 20.0;
  pm->dm_bin = 0.0;
  pm->c_fac  = 1.0E-6;
  pm->s_col  = 0.10;
  pm->d_col  = 0.005;
  pm->i_col  = 0.20;
  pm->max_col = 3.0;
  pm->min_col = 0.0;
  pm->dn[DSK] = 500.0;
  pm->dn[THK] = 10.0;
  pm->dn[SPH] = 1.0;
  pm->r0      = 8000.0;
  pm->amode   = SA;
  pm->a[0]    = 100.0;
  pm->a[1]    = 0.0;
  pm->a[2]    = 0.165;
  pm->a[3]    = 1.192;
  pm->abs     = 0.0;
  pm->es      = 0.8;
  pm->rek     = 2670.0;
  pm->psl_d   = 3500.0;
  pm->psl_t   = 3500.0;
  pm->gsh_d   = 250.0;
  pm->gsh_t   = 1300.0;

  /** Initialize model structure **/
  strcpy(ml->libry,BSMLIB);
  strcpy(ml->ofile,NULL_STR);
  ml->l2 =  0.0;
  ml->b2 = 90.0;
  ml->omega = 1.0;
  strcpy(ml->mag,"V");
  strcpy(ml->col,"B-V");
  ml->dsh_f_h = 325.0;
  ml->dsh_f_m = 5.1;
  ml->dsh_b_h = 90.0;
  ml->dsh_b_m = 2.3;
  ml->tsh_f_h = 1300.0;
  ml->tsh_f_m = 5.1;
  ml->tsh_b_h = 1300.0;
  ml->tsh_b_m = 2.3;

  /** Initialize colour magnitude data files **/
  strcpy(ml->dmsfn,"ms.vbv");
  strcpy(ml->tmsfn,"ms.vbv");
  strcpy(ml->smsfn,"ms.vbv");
  strcpy(ml->dgbfn,"dskm67.vbv");
  strcpy(ml->tgbfn,"dskm67.vbv");
  strcpy(ml->sgbfn,"m13.vbv");

  /** Initialize luminosity function data files **/
  strcpy(ml->dlffn,"wielen.vlf");
  strcpy(ml->tlffn,"wielen.vlf");
  strcpy(ml->slffn,"dacosta.vlf");

  /** Initialize FMS function data files **/
  strcpy(ml->fmsfn,"analytic.vfm");

  /** Initialize optional argument flags **/
  op->v     = FALSE;
  op->thick = FALSE;

  return;
}
/*---------------------------------------------------------------------------*/
