/*
  Function : col_dist.c
  Purpose  : Bahcall - Soneira Galaxy Model. 
             Routine to convert absolute magnitudes to colours.
  History  : Began: 19 June 1991. Last edit: 28 April 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. There are many areas of improvement for this routine. It
	        may not be necessary  to pass whole  structures to  this
		function.
*/

#include "bsm.h"

void col_dist(int id, REAL m_abs, REAL m_app, REAL nms, REAL ng, 
	      REAL cms, REAL cg, Param *pm, Numbr *nm)
{
  int  ims, ig;

  /** check if app. mags. are outside requested range **/
  nms = (m_app < pm->mbc || m_app > pm->mfc) ? 0.0 : nms;
  ng  = (m_app < pm->mbc || m_app > pm->mfc) ? 0.0 : ng;

  /** get index into colour arrays **/
  ims = (int) (cms / pm->d_col);
  ig  = (int) (cg  / pm->d_col);

  /** check index **/
  ims = (ims < 0) ? 0 : ims;
  ims = (ims > nm->nc) ? nm->nc : ims;
  ig = (ig < 0) ? 0 : ig;
  ig = (ig > nm->nc) ? nm->nc : ig;

  /** accumulate components and totals in colour arrays **/
  nm->col[id][ims]  += nms;
  nm->col[TOT][ims] += nms;

  nm->col[id][ig]  += ng;
  nm->col[TOT][ig] += ng;

  /** compute colour means **/
  nm->cb[id]  += nms*cms + ng*cg;
  nm->cb[TOT] += nms*cms + ng*cg;

  nm->tc[id]  += nms + ng;
  nm->tc[TOT] += nms + ng;

  /** compute fraction on giant branch **/
  nm->gb[id]  += ng;
  nm->gb[TOT] += ng;

  return;
}
/*---------------------------------------------------------------------------*/
