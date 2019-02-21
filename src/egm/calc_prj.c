/*  
  Function : calc_prj.c
  Purpose  : External Galaxy Model.
             Calculate projection parameters.
  History  : Began: 17 October 1992. Last edit: 7 July 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. Formula defined for y0 > 0.0 as the  "far" side of the galaxy.
             2. Each case and quadrant is calculated seperately -  this is not
	        an elegant solution but it does work (hopefully). The quadrant
		will determine wether, for example, ml.l2 is 90d. or 270d.
	     3. Integrating  the far  side always occurs  after doing the near
	        side. All parameters stay the same except for l (even b if you
		think about it). Thus don't rerun this function to get the new
		parameters - set l2 = 180 + l2.
	     4. x0 and y0 as  given on  command line or  parameter file are in
	        arcminutes. These are ml.x0 and ml.y0. In this function x0 and
		y0 are the distances in parsecs.
*/

#include "egm.h"

void calc_prj(int DIR, Param *pm, Model *ml)
{
  double phi;              /* angle between x-axis & rho0 - in plane of sky  */
  double theta;            /* angle between x-axis & r0 - in plane of galaxy */
  double x0;               /* coordinates of field along major & minor axes  */
  double y0;               /*  in the plane of the sky  (in pc)              */
  double i;                /* angle between plane of sky and galaxy          */
  double sec2i;

  i = (PI/180.0)*ml->inc;
  sec2i = 1.0/(cos(i)*cos(i));
  x0 = ml->dist * tan(ml->x0 * DEG2RAD/60.0);
  y0 = ml->dist * tan(ml->y0 * DEG2RAD/60.0);

  if (x0 == 0.00 && y0 == 0.00) {
    phi   = 0.00;
    theta = 0.00;
    ml->rho0 = 0.00;
    pm->l2 = PI;
    pm->r0 = 0.00;
  } else if (x0 == 0.00 && y0 != 0.00) {                     /* along y-axis */
    phi = M_PI2;
    theta = M_PI2;
    ml->rho0 = fabs(y0);
    pm->r0 = fabs(y0) / cos(i);
    
    if (y0 > 0.00) { pm->l2 = (DIR == NEAR) ? 0.0 : PI; }
    if (y0 < 0.00) { pm->l2 = (DIR == NEAR) ? PI : 0.0; }
  } else if (y0 == 0.00 && x0 != 0.00) {                    /* along x-axis */ 
    phi = 0.0;
    theta = 0.0;
    ml->rho0 = fabs(x0);
    pm->r0 = fabs(x0);

    if (x0 > 0.00) { pm->l2 = M_PI2; }
    if (x0 < 0.00) { pm->l2 = M_PI2; }
  } else {
    phi = atan(fabs(y0/x0));
    theta = atan(tan(phi)/cos(i));
    ml->rho0 = sqrt(x0*x0 + y0*y0);
    pm->r0 = ml->rho0 * sqrt(cos(phi)*cos(phi) + sec2i*sin(phi)*sin(phi));

    if (x0 > 0.00 && y0 > 0.00) {
      pm->l2 = (DIR == NEAR) ? M_PI2 - theta : M_PI2 + theta ;
    } else if (x0 > 0.00 && y0 < 0.00) {
      pm->l2 = (DIR == NEAR) ? M_PI2 + theta : M_PI2 - theta ;
    } else if (x0 < 0.00 && y0 > 0.00) {
      pm->l2 = (DIR == NEAR) ? M_PI2 - theta : M_PI2 + theta ;
    } else if (x0 < 0.00 && y0 < 0.00) {
      pm->l2 = (DIR == NEAR) ? M_PI2 + theta : M_PI2 - theta ;
    }
  }

  /** b=90-i in ALL cases! **/
  pm->b2 = M_PI2 - i;

  /** find rpk correction - only do it once or it's wrong **/
  if (DIR == NEAR) pm->rpk = pm->r0 * cos(pm->b2) * cos(pm->l2);

  return;
}
/*---------------------------------------------------------------------------*/
