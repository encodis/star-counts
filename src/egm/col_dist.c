/*
  Function : col_dist.c
  Purpose  : External Galaxy Model.
             Routine to convert absolute magnitudes to colours.
  History  : Began: 6 October 1992. Last edit: 7 February 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. There are many areas of improvement for this routine. It
	        may not be necessary  to pass whole  structures to  this
		function.
*/

#include "egm.h"

void col_dist(int id, double m_abs, double m_app, double nms, double cms,
	      double ngb, double cgb, Param *pm, Numbr *nm)
{
  int  ims, igb;

  /** check if app. mags. are outside requested range **/
  if ((m_app < pm->mbc) || (m_app > pm->mfc)) return;

  /** get index into colour arrays **/
  ims  = (int) ( (cms - pm->min_col) / pm->d_col);
  igb  = (int) ( (cgb - pm->min_col) / pm->d_col);

  /** check index and accumulate totals **/
  if (ims >= 0 && ims <= nm->nc) {
    nm->col[id][ims] += nms; nm->col[TOT][ims] += nms;

    /** compute colour means **/
    nm->cb[id] += nms*cms; nm->cb[TOT] += nms*cms;
    nm->tc[id] += nms; nm->tc[TOT] += nms;
  }
  
  if (igb >= 0 && igb <= nm->nc) {
    nm->col[id][igb] += ngb; nm->col[TOT][igb] += ngb;
    
    /** compute colour means **/
    nm->cb[id] += ngb*cgb; nm->cb[TOT] += ngb*cgb;
    nm->tc[id] += ngb; nm->tc[TOT] += ngb;
    
    /** compute fraction on giant branch **/
    nm->gb[id] += ngb; nm->gb[TOT] += ngb;
  }
  
  return;
}
/*---------------------------------------------------------------------------*/
