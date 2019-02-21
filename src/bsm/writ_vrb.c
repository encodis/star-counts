/*
  Function : writ_vrb.c
  Purpose  : Bahcall - Soneira Galaxy Model.
             Write out the additional arrays. Change format according to
	     number of components.
  History  : Began: 25 August 1992. Last edit: 30 June 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. This function will output the following arrays:
                DLF  [TLF]  SLF   FMS
		DMS   DGC  [TMS] [TGC]  SMS  SGC
*/

#include "bsm.h"

void writ_vrb(BOOL thick, Param *pm, Model *ml, Lumfn *lf, Color *cl, 
	      Numbr *nm, FILE *out)
{
  REAL *mag;
  int  i;

  /** Create temporary array for magnitudes **/
  ALLOC(mag,lf->nl,"mag","write_dist()");
  for (i=0; i<lf->nl; i++) mag[i] = pm->m_brd + i*pm->dm_abs;

  /** Include thick disk ? **/
  if (thick == TRUE) {
    fprintf(out,"#\n");
    fprintf(out,"# %s  DLF   TLF   SLF   FMS\n",ml->mag);
    for (i=0; i<lf->nl; i++) {
      fprintf(out,"%5.2f %9.3e %9.3e %9.3e %9.3e\n",
	      mag[i], lf->d[i], lf->t[i], lf->s[i], nm->fms[i]);
    }
    
    fprintf(out,"#\n");
    fprintf(out,"# %s  DMS   DGC   TMS   TGC   SMS   SGC\n",ml->mag);
    for (i=0; i<lf->nl; i++) {
      fprintf(out,"%5.2f %9.3e %9.3e %9.3e %9.3e %9.3e %9.3e\n",
	      mag[i], cl->dms[i], cl->dg[i], cl->tms[i], cl->tg[i], 
	      cl->sms[i],cl->sg[i]);
    }
  } else {
    fprintf(out,"#\n");
    fprintf(out,"# %s  DLF   SLF   FMS\n",ml->mag);
    for (i=0; i<lf->nl; i++) {
      fprintf(out,"%5.2f %9.3e %9.3e %9.3e\n",
	      mag[i], lf->d[i], lf->s[i], nm->fms[i]);
    }

    fprintf(out,"#\n");
    fprintf(out,"# %s  DMS   DGC   SMS   SGC\n",ml->mag);
    for (i=0; i<lf->nl; i++) {
      fprintf(out,"%5.2f %9.3e %9.3e %9.3e %9.3e\n",
	      mag[i], cl->dms[i], cl->dg[i], cl->sms[i], cl->sg[i]);
    }
  }
  
  return;
}
/*---------------------------------------------------------------------------*/
