/*
  Function : calc_num.c
  Purpose  : External Galaxy Model.
             Compute final number distribution.
  History  : Began: 6 October 1992. Last edit: 21 January 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. The array  nm->num[] is used in  calc_dsk() and  calc_spd() to
                store the  counts per  magnitude  bin.  If dm_bin == 0 then no
		scaling is done; else divide by bin size (dm_app) to get stars
		per unit  magnitude, then multiply  by scaling factor (dm_bin)
		to get number per (dm_bin_size).
*/

#include "egm.h"

void calc_num(BOOL thick, Numbr *nm, Param *pm)
{
  int  j;
  double tmpsum0 = 0.00;
  double tmpsum1 = 0.00;
  double tmpsum2 = 0.00;
  double tmpsum3 = 0.00;

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
    tmpsum0 = (pm->dm_bin / pm->dm_app);
    for (j=0; j<(nm->nn); j++) {
      /** scale to output bin size. reuse nm->num array **/
      nm->num[DSK][j] *= tmpsum0;
      nm->num[SPH][j] *= tmpsum0;
      nm->num[TOT][j] *= tmpsum0;
      if (thick == TRUE) nm->num[THK][j] *= tmpsum0;
    }
  }
  
  return;
}
/*---------------------------------------------------------------------------*/
