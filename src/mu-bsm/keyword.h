/*
  Function : keyword.h
  Purpose  : MU space. Bahcall - Soneira Galaxy Model.
             Defines integer values for keywords in a parameter file.
  History  : Began: 26 June 1991. Last edit: 4 August 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. Each keyword that can appear in the parameter file is assigned
                a (somewhat arbitrary) integer number. An array is set up  in
		find_idx() whose elements are the allowed  keywords. The array 
		is ordered in the same sequence as the numbers are assigned in 
		this file. In read_par() each line of the parameter file is 
		read and passed to parsetok(). This calls find_idx() which 
		returns the number associated with that keyword. A switch
		statement then assigns values to the parameter structure.
	     2. Recommended procedure for adding keywords:
	       a) May have to alter the definitions of one of the structures
	          (in mubsm.h).
	       b) Add keyword to the end of this list.
	       c) Extend array declaration.
	       d) Add "case the_new_keyword:" to read_par().
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
  DEL_COL,
  DEL_MU,
  DGC_FILE,
  DLF_FILE,
  DMS_FILE,
  DN,
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
  MAG,
  MAG_BIN,
  MAG_NAME,
  MAX_COL,
  MBC,
  MFC,
  MIN_COL,
  MTO,
  MU_BRT,
  MU_DIM,
  OMEGA,
  PSL_D,
  PSL_T,
  R_0,
  R_EK,
  SGC_FILE,
  SLF_FILE,
  SMS_FILE,
  TSH_B_H,
  TSH_B_M,
  TSH_F_H,
  TSH_F_M,
  TGC_FILE,
  TLF_FILE,
  TMS_FILE,
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
  "DEL_COL",
  "DEL_MU",
  "DGC_FILE",
  "DLF_FILE",
  "DMS_FILE",
  "DN",
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
  "MAG",
  "MAG_BIN",
  "MAG_NAME",
  "MAX_COL",
  "MBC",
  "MFC",
  "MIN_COL",
  "MTO",
  "MU_BRT",
  "MU_DIM",
  "OMEGA",
  "PSL_D",
  "PSL_T",
  "R_0",
  "R_EK",
  "SGC_FILE",
  "SLF_FILE",
  "SMS_FILE",
  "TSH_B_H",
  "TSH_B_M",
  "TSH_F_H",
  "TSH_F_M",
  "TGC_FILE",
  "TLF_FILE",
  "TMS_FILE"
};
/*---------------------------------------------------------------------------*/
