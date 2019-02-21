/*
  Function : writ_num.c
  Purpose  : MU space. Bahcall - Soneira Galaxy Model.
             Write out the number distribution. Change format according to
	     number of components.
  History  : Began: 25 August 1992. Last edit: 15 June 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments :
*/

#include "mubsm.h"

void writ_num(BOOL thick, Param *pm, Model *ml, Numbr *nm, FILE *out)
{
  REAL m1, m2, m12;
  int  i;

  /** Write out number distribution **/
  fprintf(out,"#\n");
  fprintf(out,"# NUM:  %s\n",ml->mag);

  /** if thick disk print disk & thick disk, spheroid & total underneath **/

  if (thick == TRUE) {
    /** disk and thick disk first **/
    fprintf(out,"# u1    u     u2    Ad(u)     Nd(<u2)    At(u)    Nt(<u2)\n");
    
    for (i=0; i<(nm->nn); i++) {
      /** find limits for mu **/
      m12  = pm->mu_brt + i*pm->del_mu;
      m1  = m12 - (pm->del_mu/2.0);
      m2  = m12 + (pm->del_mu/2.0);
      
      fprintf(out,"%5.2f %5.2f %5.2f %9.3e %9.3e %9.3e %9.3e\n", 
	      m1, m12, m2, nm->num[DSK][i], nm->sum[DSK][i],
	      nm->num[THK][i], nm->sum[THK][i]);
    }
    
    /** now spheroid and total **/
    fprintf(out,"# u1    u     u2    As(u)    Ns(<u2)    AT(u)    NT(<u2)\n");
    
    for (i=0; i<(nm->nn); i++) {
      /** find mag. limits for stars unit magnitude **/
      m12  = pm->mu_brt + i*pm->del_mu;
      m1  = m12 - (pm->del_mu/2.0);
      m2  = m12 + (pm->del_mu/2.0);
      
      fprintf(out,"%5.2f %5.2f %5.2f %9.3e %9.3e %9.3e %9.3e\n", 
	      m1, m12, m2, nm->num[SPH][i], nm->sum[SPH][i],
	      nm->num[TOT][i], nm->sum[TOT][i]);
    }
  } else {
    fprintf(out,"# u1    u     u2    Ad(u)    Nd(<u2)    As(u)    Ns(<u2)    AT(u)    NT(<u2)\n");
    
    for (i=0; i<(nm->nn); i++) {
      /** find mag. limits for stars unit magnitude **/
      m12  = pm->mu_brt + i*pm->del_mu;
      m1  = m12 - (pm->del_mu/2.0);
      m2  = m12 + (pm->del_mu/2.0);
      
      fprintf(out,"%5.2f %5.2f %5.2f %9.3e %9.3e %9.3e %9.3e %9.3e %9.3e\n", 
	      m1, m12, m2, nm->num[DSK][i], nm->sum[DSK][i],
	      nm->num[SPH][i], nm->sum[SPH][i],
	      nm->num[TOT][i], nm->sum[TOT][i]);
    }
    
  }
  
  return;
}
/*---------------------------------------------------------------------------*/
