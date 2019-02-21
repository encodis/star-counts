/*
  Function : writ_num.c
  Purpose  : External Galaxy Model.
             Write out the number distribution. Change format according to
	     number of components.
  History  : Began: 6 October 1992. Last edit: 7 February 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments :
*/

#include "egm.h"

void writ_num(BOOL thick, Param *pm, Model *ml, Numbr *nm, FILE *out)
{
  double m1, m2, m12;
  int    i;

  /** Write out number distribution **/
  fprintf(out,"#\n");
  fprintf(out,"# NUM:\n");

  /** If thick disk print disk and thick disk,
      spheroid and total underneath **/

  if (thick == TRUE) {
    /** disk and thick disk first **/
    fprintf(out, "# %s1    %s     %s2"
	    "    Ad(%s)    Nd(<%s2)    At(%s)    Nt(<%s2)\n",
	    ml->mag, ml->mag, ml->mag, ml->mag, ml->mag, ml->mag, ml->mag);
    
    for (i=0; i<(nm->nn); i++) {
      /** find mag. limits for stars unit magnitude **/
      m12 = pm->ma_brt + i*pm->dm_app;
      m1  = m12 - (pm->dm_app/2.0);
      m2  = m12 + (pm->dm_app/2.0);
      
      fprintf(out,"%5.2f %5.2f %5.2f %9.3e %9.3e %9.3e %9.3e\n", 
	      m1, m12, m2, nm->num[DSK][i], nm->sum[DSK][i], nm->num[THK][i],
	      nm->sum[THK][i]);
    }
    
    /** now spheroid and total **/
    fprintf(out, "# %s1    %s     %s2"
	    "    As(%s)    Ns(<%s2)    AT(%s)    NT(<%s2)\n",
	    ml->mag, ml->mag, ml->mag, ml->mag, ml->mag, ml->mag, ml->mag);

    for (i=0; i<(nm->nn); i++) {
      /** find mag. limits for stars unit magnitude **/
      m12 = pm->ma_brt + i*pm->dm_app;
      m1  = m12 - (pm->dm_app/2.0);
      m2  = m12 + (pm->dm_app/2.0);
      
      fprintf(out,"%5.2f %5.2f %5.2f %9.3e %9.3e %9.3e %9.3e\n", 
	      m1, m12, m2, nm->num[SPH][i], nm->sum[SPH][i], nm->num[TOT][i],
	      nm->sum[TOT][i]);
    }
  } else {
    fprintf(out, "# %s1    %s     %s2    Ad(%s)    Nd(<%s2)"
	    "    As(%s)    Ns(<%s2)    AT(%s)    NT(<%s2)\n",
	    ml->mag, ml->mag, ml->mag, ml->mag, ml->mag, 
	    ml->mag, ml->mag, ml->mag, ml->mag);

    for (i=0; i<(nm->nn); i++) {
      /** find mag. limits for stars unit magnitude **/
      m12 = pm->ma_brt + i*pm->dm_app;
      m1  = m12 - (pm->dm_app/2.0);
      m2  = m12 + (pm->dm_app/2.0);
      
      fprintf(out,"%5.2f %5.2f %5.2f %9.3e %9.3e %9.3e %9.3e %9.3e %9.3e\n", 
	      m1, m12, m2, nm->num[DSK][i], nm->sum[DSK][i], nm->num[SPH][i],
	      nm->sum[SPH][i], nm->num[TOT][i], nm->sum[TOT][i]);
    }  
  }
  
  return;
}
/*---------------------------------------------------------------------------*/
