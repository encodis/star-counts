/*
  Function : keyword.h
  Purpose  : Bahcall - Soneira Galaxy Model.
             Defines integer values for keywords in a parameter file.
  History  : Began: 26 June 1991. Last edit: 30 June 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. Each keyword that can appear in the parameter file is assigned
                an integer number in thr enum{} below. The keyword array is set
		up whose elements are the allowed keywords. The array must be
		ordered in the same sequence as the numbers are assigned.
		this file. In read_par() each line of the parameter file is 
		read and passed to parsetok(). This calls find_idx() which 
		returns the number associated with that keyword. A switch
		statement then assigns values to the parameter structure.
	     2. Recommended procedure for adding keywords:
	        a) Add keyword to the end of this list.
	        b) Extend array declaration, keeping same order.
	        c) Add "case the_new_keyword:" to read_par().
	        d) May have to alter the definitions of one of the structures
		   in bsm.h and change the code in the appropriate function.
	        e) Contact author and get him to do it when the above fails!!!
*/

enum keywords {
  NOT_A_WORD = -1,     /* not a keyword */
  A_0,
  A_1,
  A_2,
  A_3,
  ABS,
  AMODE,
  B2,
  COL_BIN,
  COL_ERR,
  COL_NAME, 
  CON_FAC,
  DEL_ABS,
  DEL_APP,
  DEL_COL,
  DGC_FILE,
  DLF_FILE,
  DMS_FILE,
  DN,
  DR,
  DSH_B_H,
  DSH_B_M,
  DSH_F_H,
  DSH_F_M,
  E_SPHER,
  FMS_FILE,
  GSH_D,
  GSH_T,
  L2,
  LIBRARY,
  M_BRD,
  M_BRS,
  M_DIM,
  MA_BRT,
  MA_DIM,
  MAG_BIN,
  MAG_NAME,
  MAX_COL,
  MBC,
  MFC,
  MIN_COL,
  MTO,
  OMEGA,
  PSL_D,
  PSL_T,
  R_0,
  R_EK,
  R_MAX_D,
  R_MAX_S,
  R_MAX_T,
  R_MIN,
  SGC_FILE,
  SLF_FILE,
  SMS_FILE,
  TGC_FILE,
  TLF_FILE,
  TMS_FILE,
  TSH_B_H,
  TSH_B_M,
  TSH_F_H,
  TSH_F_M,
  NUM_KEYWORDS    /* number of keywords */
};

static char *keyword[NUM_KEYWORDS] = {
  "A_0",
  "A_1",
  "A_2",
  "A_3",
  "ABS",
  "AMODE",
  "B2",
  "COL_BIN",
  "COL_ERR",
  "COL_NAME",
  "CON_FAC",
  "DEL_ABS",
  "DEL_APP",
  "DEL_COL",
  "DGC_FILE",
  "DLF_FILE",
  "DMS_FILE",
  "DN",
  "DR",
  "DSH_B_H",
  "DSH_B_M",
  "DSH_F_H",
  "DSH_F_M",
  "E_SPHER",
  "FMS_FILE",
  "GSH_D",
  "GSH_T",
  "L2",
  "LIBRARY",
  "M_BRD",
  "M_BRS",
  "M_DIM",
  "MA_BRT",
  "MA_DIM",
  "MAG_BIN",
  "MAG_NAME",
  "MAX_COL",
  "MBC",
  "MFC",
  "MIN_COL",
  "MTO",
  "OMEGA",
  "PSL_D",
  "PSL_T",
  "R_0",
  "R_EK",
  "R_MAX_D",
  "R_MAX_S",
  "R_MAX_T",
  "R_MIN",
  "SGC_FILE",
  "SLF_FILE",
  "SMS_FILE",
  "TGC_FILE",
  "TLF_FILE",
  "TMS_FILE",
  "TSH_B_H",
  "TSH_B_M",
  "TSH_F_H",
  "TSH_F_M"
};
/*---------------------------------------------------------------------------*/
