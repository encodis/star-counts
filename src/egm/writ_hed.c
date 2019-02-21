/*
  Function : writ_hed.c
  Purpose  : External Galaxy Model.
             Write header for output. Change format if thick disk is
	     being used.
  History  : Began: 6 October 1992. Last edit: 4 May 1995.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. Output goes to stdout unless the -o switch is used.
*/

#include "egm.h"

void writ_hed(Optar *op, Param *pm, Lumfn *lf, Model *ml, Numbr *nm, FILE *out)
{
  int  numcp;
  char amode[MAXSCH];
  char farsd[MAXSCH];

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
  
  /** integrate far side? **/
  if (op->thick) {
    if (op->far_disk && op->far_thik && op->far_sphd) {
      strcpy(farsd,"ALL");
    } else {
      strcpy(farsd,"");
      if (op->far_disk) strcat(farsd,"D ");
      if (op->far_thik) strcat(farsd,"T ");
      if (op->far_sphd) strcat(farsd,"S ");
    }  
  } else {
    if (op->far_disk && op->far_sphd) {
      strcpy(farsd,"ALL");
    } else {
      strcpy(farsd,"");
      if (op->far_disk) strcat(farsd,"D ");
      if (op->far_sphd) strcat(farsd,"S ");
    }
  }
  if (strlen(farsd) == 0) strcpy(farsd,"NONE");

  /** Write header **/
  fprintf(out,"# EXTERNAL GALAXY MODEL: %-32s    Components: %d \n",
	  ml->pfile, numcp);
  fprintf(out,"#    x0 = %10.3f    y0 = %10.3f     A = %10.5f   far = %10s\n", 
	  ml->x0, ml->y0, ml->omega, farsd);
  fprintf(out,"#     D = %10.3f     i = %10.3f    r0 = %10.3f   rpk = %10.3f\n",
	 ml->dist, ml->inc, pm->r0, pm->rpk);
  fprintf(out,"# mabrt = %10.3f madim = %10.3f    dm = %10.3f  Mbin = %10.3f\n",
	  pm->ma_brt, pm->ma_dim, pm->dm_app, pm->dm_bin);
  fprintf(out,"#  Mbri = %10.3f  Mdim = %10.3f    dM = %10.3f  rho0 = %10.3f\n",
	  pm->m_bri, pm->m_dim, pm->dm_abs, ml->rho0);
  fprintf(out,"#  Cerr = %10.3f  Cint = %10.3f  Cbin = %10.3f\n",
	  pm->s_col, pm->d_col, pm->i_col);
  fprintf(out,"#  maxC = %10.3f  minC = %10.3f   mbc = %10.3f   mfc = %10.3f\n",
	  pm->max_col, pm->min_col, pm->mbc, pm->mfc);
  fprintf(out,"# amode = %10s   abs = %10.3f  dska = %10.3f\n",
	  amode, pm->abs, pm->dabs);
  fprintf(out,"#    a0 = %10.3f    a1 = %10.3f    a2 = %10.3f    a3 = %10.3f\n",
	  pm->a[0], pm->a[1], pm->a[2], pm->a[3]);
  
  /** Disk parameters **/ 
  fprintf(out,"#\n");
  fprintf(out,"# DSK:\n");
  fprintf(out,"#  dn_d = %10.3f  rn_d = %10.3f psl_d = %10.3f gsh_d = %10.3f\n",
	  pm->dn[DSK], ml->dnr[DSK], pm->psl_d, pm->gsh_d);
  fprintf(out,"#  dr_d = %10.3f  rmin = %10.3f rmaxd = %10.3f\n",
	  pm->dr_d, pm->r_min, pm->r_max_d);
  fprintf(out,"# dsklf = %-26s    dgcmd = %-24s\n",
	  ml->dlffn, ml->dgbfn);
  if (op->doms == TRUE) {
    fprintf(out,"# dmsfn = %-26s    fmsfn = %-24s\n",
	    ml->dmsfn, ml->fmsfn);
  } else {
    fprintf(out,"# dmsfn = %-26s    fmsfn = %-24s\n",
	    "NONE", "NONE");
  }

  if (op->thick == TRUE)  {
    /** Thick disk parameters **/
    fprintf(out,"#\n");
    fprintf(out,"# THK:\n");
    fprintf(out,"#  dn_t = %10.3f  rn_t = %10.3f psl_t = %10.3f gsh_t = %10.3f\n",
	    pm->dn[THK], ml->dnr[THK], pm->psl_t, pm->gsh_t);
    fprintf(out,"#  dr_t = %10.3f  rmin = %10.3f rmaxt = %10.3f\n",
	    pm->dr_t, pm->r_min, pm->r_max_t);
    fprintf(out,"# thklf = %-26s    tgbfn = %-24s\n",
	    ml->tlffn, ml->tgbfn);
  }
  
  /** Spheroid parameters **/
  fprintf(out,"#\n");
  fprintf(out,"# SPH:\n");
  fprintf(out,"#  dn_s = %10.3f  rn_s = %10.3f   rek = %10.3f    es = %10.3f\n",
	  pm->dn[SPH], ml->dnr[SPH], pm->rek, pm->es);
  fprintf(out,"#  dr_s = %10.3f  rmin = %10.3f rmaxs = %10.3f   rac = %10.3f\n",
	  pm->dr_s, pm->r_min, pm->r_max_s, pm->rac);
  fprintf(out,"# sphlf = %-26s    sgbfn = %-24s\n",
	  ml->slffn, ml->sgbfn);
  
  if (op->thick == TRUE) {
    /** Colour information **/
    fprintf(out,"#\n");
    fprintf(out,"#                      DSK             THK             SPH             TOT\n");
    fprintf(out,"# Stars in COL   = %10.3f      %10.3f      %10.3f      %10.3f\n", 
	    nm->tc[DSK], nm->tc[THK], nm->tc[SPH], nm->tc[TOT]);
      fprintf(out,"# Mean Colours   = %10.3f      %10.3f      %10.3f      %10.3f\n",
	      nm->av[DSK], nm->av[THK], nm->av[SPH], nm->av[TOT]);
    fprintf(out,"# Star Fraction  = %10.3f      %10.3f      %10.3f\n",
	    nm->fd, nm->ft, nm->fs);
    fprintf(out,"# Giant Fraction = %10.3f      %10.3f      %10.3f      %10.3f\n",
	    nm->gb[DSK], nm->gb[THK], nm->gb[SPH], nm->gb[TOT]);
  } else { 
    /** Colour information **/
    fprintf(out,"#\n");
    fprintf(out,"#                     DSK           SPH           TOT\n");
    fprintf(out,"# Stars in COL   = %10.3f      %10.3f      %10.3f\n", 
	    nm->tc[DSK], nm->tc[SPH], nm->tc[TOT]);
    fprintf(out,"# Mean Colours   = %10.3f      %10.3f      %10.3f\n",
	    nm->av[DSK], nm->av[SPH], nm->av[TOT]);
    fprintf(out,"# Star Fraction  = %10.3f      %10.3f\n",
	    nm->fd, nm->fs);
    fprintf(out,"# Giant Fraction = %10.3f      %10.3f      %10.3f\n",
	    nm->gb[DSK], nm->gb[SPH], nm->gb[TOT]);
  }
  
  return;
}
/*---------------------------------------------------------------------------*/
