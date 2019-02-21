/*  
  Function : extgal.c
  Purpose  : External Galaxy Model.
             Main program.
  History  : Began: 6 October 1992. Last edit: 4 May 1995.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. Must be compiled using ANSI C compatible compiler (e.g. gcc).
             2. Program does no  plotting. All output is in the form of ASCII
                tables. Write some SM macros to complement this program.
             3. Currently  automatically  uses  DISK and  SPHEROID components
	        with an option to  include the THICK DISK.  Ideally should be
		able to input arbitrary number and type of components.
*/

#include "egm.h"

void main(int argc, char *argv[])
{
  Param pm;
  Model ml;
  Lumfn lf;
  Color cl;
  Numbr nm;
  Optar op;

  /** initialize default parameters **/
  init_def(&pm, &ml, &op);

  /** parse command line **/
  scan_com(argc, argv, &pm, &ml, &op);

  /** set up the luminosity function **/
  init_lf(op.thick, &pm, &ml, &lf);

  /** initialize color routine **/
  init_col(op.thick, op.doms, &pm, &ml, &cl);

  /** initialize numbr structure **/
  init_num(op.doms, &pm, &ml, &nm);

  /** calculate projection parameters **/
  calc_prj(NEAR, &pm, &ml);

  /** calculate normalization **/
  calc_nor(op.thick, &pm, &ml, &lf);

  /** calculate disk component **/
  calc_dsk(NEAR, &pm, &lf, &ml, &cl, &op, &nm);

  /** calculate thick disk component **/
  if (op.thick == TRUE) calc_thk(NEAR, &pm, &lf, &ml, &cl, &op, &nm);

  /** calculate spheroid component **/
  calc_spd(NEAR, &pm, &lf, &ml, &cl, &op, &nm);

  /** if integrating far side do it again **/
  if (op.far_disk || op.far_thik || op.far_sphd) calc_prj(FAR, &pm, &ml);

  if (op.far_disk) calc_dsk(FAR, &pm, &lf, &ml, &cl, &op, &nm);
  if (op.far_sphd) calc_spd(FAR, &pm, &lf, &ml, &cl, &op, &nm);
  if (op.far_thik && op.thick) calc_thk(FAR, &pm, &lf, &ml, &cl, &op, &nm);

  /** calculate color distribution **/
  calc_col(op.thick, &pm, &cl, &nm);

  /** calculate final number distribution **/
  calc_num(op.thick, &nm, &pm);

  /** write out results **/
  writ_res(&op, &pm, &lf, &ml, &cl, &nm);

  /** quit **/
  quit_egm(ERR_NONE, NULL_STR, NULL_STR);

}
/*---------------------------------------------------------------------------*/
