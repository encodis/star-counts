/*
  Function : calc_num.c
  Purpose  : MU space. Bahcall - Soneira Galaxy Model.
             Compute final number distribution.
  History  : Began: 25 November 1991. Last edit: 3 June 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. The array nm->num[] is used in calc_disk() and calc_sphd() to
                store the counts  per magnitude bin. It is divided by the bin
		size to get stars per unit magnitude at that magnitude (which
		equals the mean magnitude of the bin).
*/

#include "mubsm.h"
#define ZERO 1.0e-6

void calc_num(BOOL thick, Param *pm, Numbr *nm)
{
  int  j;
  REAL tmpsum0 = 0.00;
  REAL tmpsum1 = 0.00;
  REAL tmpsum2 = 0.00;
  REAL tmpsum3 = 0.00;

  /** compute totals for disk, spheroid and total **/
  for (j=0; j<(nm->nn); j++) {
    nm->num[TOT][j] += nm->num[DSK][j] + nm->num[SPH][j];
    if (thick == TRUE) nm->num[TOT][j] += nm->num[THK][j];

    tmpsum0 += nm->num[DSK][j];
    tmpsum1 += nm->num[SPH][j];
    tmpsum2 += nm->num[TOT][j];
    if (thick == TRUE) tmpsum3 += nm->num[THK][j];
    
    nm->sum[DSK][j] = tmpsum0;
    nm->sum[SPH][j] = tmpsum1;
    nm->sum[TOT][j] = tmpsum2;
    if (thick == TRUE) nm->sum[THK][j] = tmpsum3;
  }

  /** check for rescaling **/
  if (pm->dm_bin > 0.0) {
    tmpsum0 = (pm->dm_bin / pm->del_mu);
    for (j=0; j<(nm->nn); j++) {
      /** scale to output bin size. reuse nm->num array **/
      nm->num[DSK][j] *= tmpsum0;
      nm->num[SPH][j] *= tmpsum0;
      nm->num[TOT][j] *= tmpsum0;
      if (thick == TRUE) nm->num[THK][j] *= tmpsum0;
    }
  }

  /** set stupidly low numbers to ZERO for clarity **/
  for (j=0; j<(nm->nn); j++) {
    nm->num[DSK][j] = (nm->num[DSK][j] > ZERO) ? nm->num[DSK][j] : 0.0;
    nm->num[SPH][j] = (nm->num[SPH][j] > ZERO) ? nm->num[SPH][j] : 0.0;
    nm->num[TOT][j] = (nm->num[TOT][j] > ZERO) ? nm->num[TOT][j] : 0.0;

    if (thick == TRUE)
      nm->num[THK][j] = (nm->num[THK][j] > ZERO) ? nm->num[THK][j] : 0.0;
  }

  return;
}
/*---------------------------------------------------------------------------*/
