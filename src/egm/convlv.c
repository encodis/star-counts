/* 
  Function : convlv.c
  Purpose  : External Galaxy Model.
             Convolve two arrays together. Place the result in the first
	     array. Use zero padding.
  History  : Began: External Galaxy Model.
  Author   : Original: P. Hickson (hickson@geop.ubc.ca) as al_vcnv().
             Modified: P.J.C.Hodder (hodder@geop.ubc.ca).
  Comments : 1. Original code from P. Hickson (via B. Gibson). Modified by
                P.J.C.H. to fit with the egm code protocol.
	     2. Function now creates a zero padded array  z[] to use in the 
	        convolution in order to prevent "edge effects".  This array 
		is (nx + 2*nc) elements long - the central nx elements  are
		copies of the appropriate element of x[].
*/

#include "egm.h"

void convlv(double *x, int nx, double *c, int nc)
{
  register int	i,j,k;
  int		cen;
  double        *y;                  /* storage array                        */
  double        *z;                  /* zero padded array                    */
  int           nz;

  /** Zero pad the original array (x) **/
  nz = (nx + (2 * nc));
  ALLOC(z,nz,"z","convlv()");
  for (i=0;  i<nc;      i++) z[i] = 0.00;
  for (i=nc; i<(nx+nc); i++) z[i] = x[(i-nc)];
  for (i=(nx+nc); i<nz; i++) z[i] = 0.00;

  /** Temporary storage array **/
  ALLOC(y,nz,"y","convlv()");
  cen = nc/2;

  /** Convolve using c[] and z[] **/
  for (i = cen; i < nz-cen; i++) {
    y[i] = 0; k = i-cen;
    for (j = 0; j < nc;) y[i] += z[k++]*c[j++];
  }

  for (i = cen; i < nz-cen; i++) z[i] = y[i];

  /** Restore x[] **/
  for (i=0; i<nx; i++) x[i] = z[(i+nc)];

  /** Free memory and return **/
  DEALLOC(y);
  DEALLOC(z);
  
  return;
}
/*---------------------------------------------------------------------------*/

