/*
  Function : calc_nor.c
  Purpose  : External Galaxy Model.
             Calculate density normalizations.
  History  : Began: 17 June 1993. Last edit: 6 August 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca).
  Comments : 1. init_def() sets the default density string to be NULL. 
	        calc_nor() checks for this, and if true sets the default string
		depending on whether or not the thick disk option is set.
	     2. If the normalisation radius is set to -1 in the input string 
	        then the density is normalized to r0. If it is -2 then the
		normalization radius is rho0.
*/

#include "egm.h"

void calc_nor(BOOL thick, Param *pm, Model *ml, Lumfn *lf)
{
  double rj, d_r0, d_rn;
  double rc, rn, cosbl;

  /** check for default values **/
  if (!strcmp(ml->den,NULL_STR)) {
    if (thick) {
      strcpy(ml->den,DEFDEN3);
    } else {
      strcpy(ml->den,DEFDEN2);
    }
  }
  
  /** parse den. norm. string **/
  ml->dnr[DSK] = atof(strtok(ml->den,SEPCHARS1));
  ml->dnr[THK] = (thick) ? atof(strtok(NULL,SEPCHARS1)) : 0.0;
  ml->dnr[SPH] = atof(strtok(NULL,SEPCHARS1));

  /** check for negative values (= use r0 or rho0) **/
  if (ml->dnr[DSK] == -1) ml->dnr[DSK] = pm->r0;
  if (ml->dnr[THK] == -1) ml->dnr[THK] = pm->r0;
  if (ml->dnr[SPH] == -1) ml->dnr[SPH] = pm->r0;

  if (ml->dnr[DSK] == -2) ml->dnr[DSK] = ml->rho0;
  if (ml->dnr[THK] == -2) ml->dnr[THK] = ml->rho0;
  if (ml->dnr[SPH] == -2) ml->dnr[SPH] = ml->rho0;

  /** calculate rel. norms **/
  /* disk */
  pm->dn[DSK] = exp(-(pm->r0 - ml->dnr[DSK])/pm->psl_d);

  /* thick disk */
  if (thick) pm->dn[THK] = exp(-(pm->r0 - ml->dnr[THK])/pm->psl_t);

  /* spheroid */
  rj = pow(pm->r0/(pm->rek/sqrt(pm->es)),0.25);
  d_r0 = C1*exp(-BD*rj)*sqrt(C2/rj)/(rj*rj*rj);

  rj = pow(ml->dnr[SPH]/(pm->rek/sqrt(pm->es)),0.25);
  d_rn = C1*exp(-BD*rj)*sqrt(C2/rj)/(rj*rj*rj);

  pm->dn[SPH] = d_r0 / d_rn;

  return;
}
/*---------------------------------------------------------------------------*/
