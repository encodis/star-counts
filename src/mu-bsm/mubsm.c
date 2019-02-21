/*  
  Function : bacson.c
  Purpose  : MU space. Bahcall - Soneira Galaxy Model. 
             Main program.
  History  : Rewrite in C of the original Fortran code by Bahcall & Soneira.
             Began: 23 May 1991. Last edit: 28 April 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. Must be compiled using ANSI C compatible compiler (e.g. gcc).
             2. Program does no plotting. All output is in the form of ASCII
                tables. 
             3. Currently automatically uses DISK and SPHEROID components with 
	        an option to include the THICK DISK. Ideally should be able to 
		input arbitrary number and type of components.
	     4. No band transformations are performed in this code. The user
	        must supply (or ask the author (nicely!) to supply LF and CMD 
		files in other filters).
*/

#include "mubsm.h"

void main(int argc, char **argv)
{
  Param pm;
  Model ml;
  Lumfn lf;
  Color cl;
  Numbr nm;
  Optar op;

  /** initialize default parameters **/
  init_def(&pm, &ml, &op);

  /** parse command line and read parameter file **/
  pars_com(argc, argv, &pm, &ml, &op);

  /** set up the luminosity function **/
  init_lum(op.thick, &pm, &ml, &lf);

  /** initialize color routine **/
  init_col(op.thick, &pm, &ml, &cl);

  /** initialize numbr structure **/
  init_num(&pm, &ml, &nm);

  /** initialize fms array **/
  init_fms(&pm, &ml, &nm);

  /** calculate disk component **/
  calc_dsk(&pm, &lf, &ml, &cl, &nm);

  /** calculate thick disk component **/
  if (op.thick == TRUE) calc_thk(&pm, &lf, &ml, &cl, &nm);

  /** calculate spheroid component **/
  calc_sph(&pm, &lf, &ml, &cl, &nm);

  /** calculate color distribution **/
  calc_col(op.thick, &pm, &cl, &nm);

  /** calculate final number distribution **/
  calc_num(op.thick, &pm, &nm);

  /** write out results **/
  writ_res(&op, &pm, &lf, &ml, &cl, &nm);

  /** quit **/
  quit_bsm(ERR_NONE, NULL_STR, NULL_STR);
}
/*---------------------------------------------------------------------------*/
