/* 
  Function : init_num.c
  Purpose  : External Galaxy Model.
             Initialize number count arrays.
  History  : Began: 6 October 1992. Last edit: 7 February 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. num, sum and col are 2-dimensional  arrays, and as such
	        are allocated as arrays of pointers containing pointers 
		to floats.
	     2. fms is an array containing the fraction of stars on the
	        main sequence.
	     3. The thick disk component is automatically allocated and
	        initialized wether or not  it is specified. This may be
		a waste of memory but is easier to do. If thick disk is
		not being used then it will contribute 0.0 counts.
*/

#include "egm.h"

void init_num(BOOL doms, Param *pm, Model *ml, Numbr *nm)
{
  int    i, j;
  double m, rmax;

  /** number of points **/
  nm->nn  = (int) (pm->ma_dim - pm->ma_brt)/pm->dm_app + 1;

  /** num and sum are arrays of pointers **/
  ALLOC2(nm->num,NUM_CMP,"nm->num","init_num()");
  ALLOC2(nm->sum,NUM_CMP,"nm->sum","init_num()");

  for (i=0; i<NUM_CMP; i++) {
    ALLOC(nm->num[i],nm->nn,"nm->num[i]","init_num()");
    ALLOC(nm->sum[i],nm->nn,"nm->sum[i]","init_num()");
  }

  /** initialization of arrays **/
  for (i=0; i<NUM_CMP; i++) {
    for (j=0; j<(nm->nn); j++) {
      nm->num[i][j] = 0.0;
      nm->sum[i][j] = 0.0;
    }
  }

  /** colour distribution **/
  nm->nc  = (int) ((pm->max_col - pm->min_col) / pm->d_col) + 1;
  ALLOC2(nm->col,NUM_CMP,"nm->col","init_num()");

  for (i=0; i<NUM_CMP; i++) {
    ALLOC(nm->col[i],nm->nc,"nm->col[i]","init_num()");
  }

  /** initialization of colour distribution array **/
  for (i=0; i<NUM_CMP; i++) {
    for (j=0; j<(nm->nc); j++) {
      nm->col[i][j] = 0.0;
    }
  }

  /** accumulators **/
  ALLOC(nm->tc,NUM_CMP,"nm->tc","init_num()");
  ALLOC(nm->gb,NUM_CMP,"nm->gb","init_num()");
  ALLOC(nm->cb,NUM_CMP,"nm->cb","init_num()");
  ALLOC(nm->av,NUM_CMP,"nm->av","init_num()");

  /** initialization of accumulators**/
  for (j=0; j<NUM_CMP; j++) {
    nm->tc[j] = 0.0;
    nm->cb[j] = 0.0;
    nm->gb[j] = 0.0;
    nm->av[j] = 0.0;
    for (i=0; i<(nm->nc); i++) nm->col[j][i] = 0.0;
  }

  /** initialize "Star Fraction" **/
  nm->fd = 0.0;
  nm->ft = 0.0;
  nm->fs = 0.0;

  /** initialize FMS array **/
  if (doms) init_fms(pm, ml, nm);

  return;
}
/*---------------------------------------------------------------------------*/
