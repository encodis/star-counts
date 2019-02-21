/*
  Function : writ_hed.c
  Purpose  : Bahcall - Soneira Galaxy Model.
             Write header for output. Change format if thick disk is
	     being used.
  History  : Began: 25 August 1992. Last edit: 29 June 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 
*/

#include "bsm.h"

void writ_hed(Optar *op, Param *pm, Model *ml, Numbr *nm, FILE *out)
{
  int  numcp;
  char amode[MAXSCH];
  char pfile[MAXFCH];

  /** parameter file **/
  if (strlen(ml->pfile) == 0) {
    strcpy(pfile,"none");
  } else {
    strcpy(pfile,ml->pfile);
  }
  
  /** number of components **/
  numcp = (op->thick == TRUE) ? 3 : 2;
  
  /** get absorption mode **/
  switch (pm->amode) {
  case NA :
    strcpy(amode,"None");
    break;
  case CS :
    strcpy(amode,"Cosec");
    break;
  case SA :
    strcpy(amode,"Sandage");
    break;
  }
  
  /** Write header **/
  fprintf(out,"# B & S GALAXY MODEL: %-36s    Components: %d \n", 
	  pfile, numcp);
  fprintf(out,"#     l = %9.3f     b = %9.3f     A = %9.5f\n", 
	  ml->l2, ml->b2, ml->omega);
  fprintf(out,"# mabrt = %9.3f madim = %9.3f    dm = %9.3f  Mbin = %9.3f\n",
	  pm->ma_brt, pm->ma_dim, pm->dm_app, pm->dm_bin);
  fprintf(out,"#  Mbrd = %9.3f  Mbrs = %9.3f  Mdim = %9.3f    dM = %9.3f\n",
	  pm->m_brd, pm->m_brs, pm->m_dim, pm->dm_abs);
  fprintf(out,"#  Cerr = %9.3f  Cint = %9.3f  Cbin = %9.3f\n",
	  pm->s_col, pm->d_col, pm->i_col);
  fprintf(out,"#  maxC = %9.3f  minC = %9.3f   mbc = %9.3f   mfc = %9.3f\n",
	  pm->max_col, pm->min_col, pm->mbc, pm->mfc);
  fprintf(out,"#    dr = %9.3f    r0 = %9.3f   abs = %9.3f amode = %9s\n",
	  pm->dr, pm->r0, pm->abs, amode);
  fprintf(out,"#    a0 = %9.3f    a1 = %9.3f    a2 = %9.3f    a3 = %9.3f\n",
	  pm->a[0], pm->a[1], pm->a[2], pm->a[3]);
  fprintf(out,"# fmsfn = %-24s\n",
	  ml->fmsfn);

  /** Disk parameters **/ 
  fprintf(out,"#\n# DSK:\n");
  fprintf(out,"# den_d = %9.3f psl_d = %9.3f gsh_d = %9.3f\n",
	  pm->dn[DSK], pm->psl_d, pm->gsh_d);
  fprintf(out,"# dshfm = %9.3f dshfh = %9.3f dshbm = %9.3f dshbh = %9.3f\n",
	  ml->dsh_f_m, ml->dsh_f_h, ml->dsh_b_m, ml->dsh_b_h);
  fprintf(out,"# dsklf = %-15s dmcmd = %-15s dgcmd = %-15s\n",
	  ml->dlffn, ml->dmsfn, ml->dgbfn);

  /** Thick disk parameters **/
  if (op->thick == TRUE) {
    fprintf(out,"#\n# THK:\n");
    fprintf(out,"# den_t = %9.3f psl_t = %9.3f gsh_t = %9.3f\n",
	    pm->dn[THK], pm->psl_t, pm->gsh_t);
    fprintf(out,"# tshfm = %9.3f tshfh = %9.3f tshbm = %9.3f tshbh = %9.3f\n",
	    ml->tsh_f_m, ml->tsh_f_h, ml->tsh_b_m, ml->tsh_b_h);
    fprintf(out,"# thklf = %-15s tmcmd = %-15s tgcmd = %-15s\n",
	    ml->tlffn, ml->tmsfn, ml->tgbfn);
  }

  /** Spheroid parameter **/
  fprintf(out,"#\n# SPH:\n");
  fprintf(out,"# den_s = %9.3f   rek = %9.3f    es = %9.3f     mto = %9.3f\n",
	  pm->dn[SPH], pm->rek, pm->es, pm->mturn);
  fprintf(out,"# sphlf = %-15s smcmd = %-15s sgcmd = %-15s\n",
	  ml->slffn, ml->smsfn, ml->sgbfn);
     
  /** Colour information **/
  if (op->thick == TRUE) {
    fprintf(out,"#\n");
    fprintf(out,"#                     DSK           THK           SPH           TOT\n");
    fprintf(out,"# Stars in COL   = %8.3f      %8.3f      %8.3f      %8.3f\n", 
	    nm->tc[DSK], nm->tc[THK], nm->tc[SPH], nm->tc[TOT]);
    fprintf(out,"# Mean Colours   = %8.3f      %8.3f      %8.3f      %8.3f\n",
	    nm->av[DSK], nm->av[THK], nm->av[SPH], nm->av[TOT]);
    fprintf(out,"# Star Fraction  = %8.3f      %8.3f      %8.3f\n",
	    nm->fd, nm->ft, nm->fs);
    fprintf(out,"# Giant Fraction = %8.3f      %8.3f      %8.3f      %8.3f\n",
	    nm->gb[DSK], nm->gb[THK], nm->gb[SPH], nm->gb[TOT]);
  } else {
    fprintf(out,"#\n");
    fprintf(out,"#                     DSK           SPH           TOT\n");
    fprintf(out,"# Stars in COL   = %8.3f      %8.3f      %8.3f\n", 
	    nm->tc[DSK], nm->tc[SPH], nm->tc[TOT]);
    fprintf(out,"# Mean Colours   = %8.3f      %8.3f      %8.3f\n",
	    nm->av[DSK], nm->av[SPH], nm->av[TOT]);
    fprintf(out,"# Star Fraction  = %8.3f      %8.3f\n",
	    nm->fd, nm->fs);
    fprintf(out,"# Giant Fraction = %8.3f      %8.3f      %8.3f\n",
	    nm->gb[DSK], nm->gb[SPH], nm->gb[TOT]);
  }
  
  return;
}
/*---------------------------------------------------------------------------*/
