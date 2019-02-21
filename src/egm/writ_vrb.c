/*
  Function : writ_vrb.c
  Purpose  : External Galaxy Model.
             Write out the additional arrays. Change format according to
	     number of components.
  History  : Began: 6 October 1992. Last edit: 14 March 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. This function will output the following arrays:
                DLF  [TLF]  SLF
		DGC  [TGC]  SGC  [MSC]
*/

#include "egm.h"

void writ_vrb(BOOL thick, BOOL doms, Param *pm, Model *ml, Lumfn *lf,
	      Color *cl, Numbr *nm, FILE *out)
{
  double *mag;
  int    i;

  /** Create temporary array for magnitudes **/
  ALLOC(mag,lf->nl,"mag","write_res()");
  for (i=0; i<lf->nl; i++) mag[i] = pm->m_bri + i*pm->dm_abs;

  /** Include thick disk ? **/
  if (thick == TRUE) {
    fprintf(out,"#\n");
    fprintf(out,"# %s  DLF   TLF   SLF\n",ml->mag);
    for (i=0; i<lf->nl; i++) {
      fprintf(out,"%5.2f %9.3e %9.3e %9.3e\n",
	      mag[i], lf->d[i], lf->t[i], lf->s[i]);
    }
    
    if (doms == TRUE) {
      fprintf(out,"#\n");
      fprintf(out,"# %s  DGC   TGC   SGC   MSC\n",ml->mag);
      for (i=0; i<lf->nl; i++) {
	fprintf(out,"%5.2f %9.3e %9.3e %9.3e %9.3e\n",
		mag[i], cl->dg[i], cl->tg[i], cl->sg[i], cl->ms[i]);
      }
    } else {
      fprintf(out,"#\n");
      fprintf(out,"# %s  DGC   TGC   SGC\n",ml->mag);
      for (i=0; i<lf->nl; i++) {
	fprintf(out,"%5.2f %9.3e %9.3e %9.3e\n",
		mag[i], cl->dg[i], cl->tg[i], cl->sg[i]);
      }
    }
  } else {
    fprintf(out,"#\n");
    fprintf(out,"# %s  DLF   SLF\n",ml->mag);
    for (i=0; i<lf->nl; i++) {
      fprintf(out,"%5.2f %9.3e %9.3e\n",
	      mag[i], lf->d[i], lf->s[i]);
    }
    
    if (doms == TRUE) {
      fprintf(out,"#\n");
      fprintf(out,"# %s  DGC   SGC   MSC\n",ml->mag);
      for (i=0; i<lf->nl; i++) {
	fprintf(out,"%5.2f %9.3e %9.3e %9.3e\n",
		mag[i], cl->dg[i], cl->sg[i], cl->ms[i]);
      }
    } else {
      fprintf(out,"#\n");
      fprintf(out,"# %s  DGC   SGC\n",ml->mag);
      for (i=0; i<lf->nl; i++) {
	fprintf(out,"%5.2f %9.3e %9.3e\n",
		mag[i], cl->dg[i], cl->sg[i]);
      }
    }
  }

  return;
}
/*---------------------------------------------------------------------------*/
