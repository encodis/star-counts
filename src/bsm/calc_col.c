/*
  Function : calc_col.c
  Purpose  : Bahcall - Soneira Galactic Model. 
             Compute colour distribution.
  History  : Began: 18 June 1991. Last edit: 28 April 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. If thick disk is being included then the TOT arrays will
                be correct. The calls to col_dist() by calc_dsk(), calc_thk()
		and calc_sph() will take care of them.
	     2. To save time, only convolve & average THK if being used. The
	        scaling does not matter because the array THK will be 
		initialized to 0.0.
	     3. Scaling now done in i_col bin sizes.
*/

#include "bsm.h"

void calc_col(BOOL thick, Param *pm, Color *cl, Numbr *nm)
{
  int  i,j, k;
  int br;                                      /* ratio of bin sizes        */
  int nx;
  REAL *x;                                     /* temp. array for rebinning */

  /** Convolve with Gaussian error distribution **/
  convlv(nm->col[DSK], nm->nc, cl->gcf, cl->ng);
  convlv(nm->col[SPH], nm->nc, cl->gcf, cl->ng);
  convlv(nm->col[TOT], nm->nc, cl->gcf, cl->ng);

  /** Compute various means **/
  nm->av[DSK] = (nm->tc[DSK] == 0.0) ? 0.0 : nm->cb[DSK]/nm->tc[DSK];
  nm->av[SPH] = (nm->tc[SPH] == 0.0) ? 0.0 : nm->cb[SPH]/nm->tc[SPH];
  nm->av[TOT] = (nm->tc[TOT] == 0.0) ? 0.0 : nm->cb[TOT]/nm->tc[TOT];
  
  nm->gb[DSK] = (nm->tc[DSK] == 0.0) ? 0.0 : nm->gb[DSK]/nm->tc[DSK];
  nm->gb[SPH] = (nm->tc[SPH] == 0.0) ? 0.0 : nm->gb[SPH]/nm->tc[SPH];
  nm->gb[TOT] = (nm->tc[TOT] == 0.0) ? 0.0 : nm->gb[TOT]/nm->tc[TOT];
  
  nm->fd = (nm->tc[TOT] == 0.0) ? 0.0 : nm->tc[DSK]/nm->tc[TOT];
  nm->fs = (nm->tc[TOT] == 0.0) ? 0.0 : nm->tc[SPH]/nm->tc[TOT];

  /** Include thick disk ? (if yes, then total will still be correct) **/
  if (thick == TRUE) {
    convlv(nm->col[THK], nm->nc, cl->gcf, cl->ng);
    nm->av[THK] = (nm->tc[THK] == 0.0) ? 0.0 : nm->cb[THK]/nm->tc[THK];
    nm->gb[THK] = (nm->tc[THK] == 0.0) ? 0.0 : nm->gb[THK]/nm->tc[THK];
    nm->ft = (nm->tc[TOT] == 0.0) ? 0.0 : nm->tc[THK]/nm->tc[TOT];
  }

  /** Re-bin colour dist. to colour bin interval **/
  br = (int) (pm->i_col / pm->d_col);
  nx = (int) ((pm->max_col - pm->min_col) / pm->i_col);

  ALLOC(x,nx,"x","calc_col()");           /* temp. array */

  /** use first nx elements of nm->col for new array **/
  nm->nc = nx;

  for (i=0; i<NUM_CMP; i++) {
    for (j=0; j<nx; j++) {
      x[j] = 0.0;
      for (k=j*br; k<((j+1)*br); k++) {
	x[j] += nm->col[i][k];
      }
    }      
    for (j=0; j<(nm->nc); j++) { nm->col[i][j] = x[j]; }
  }

  DEALLOC(x);

  return;
}
/*---------------------------------------------------------------------------*/
