/*
  Function : keyword.h
  Purpose  : External Galaxy Model.
             Defines integer values for keywords in a parameter file.
  History  : Began: 6 October 1992. Last edit: 4 May 1995.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. Each keyword that can appear in the parameter file is assigned
                a (somewhat arbitrary) integer number using enum.  The keyword
		array of strings is then set up whose elements are in the same
		order as the keywords. (The strings do not have to be the same
		as the  enum  variable  name, but it helps!)  In the  function 
		read_par() each line of the parameter file is scanned and  the
		first word is passed to  find_idx()  which  returns the number
		associated with  that keyword. A switch statement then assigns
		values to the parameter structure.
	     2. Recommended procedure for adding keywords:
	       a) Change the appropriate structure(s) in egm.h.
	       b) Add keyword to the end of the enum list (but put it before
	          before NUM_KEYWORDS).
	       c) Add keyword string to array (keeping same order as above).
	       d) Add "case THE_NEW_KEYWORD:" to read_par().
	     3. read_par() includes this file and "includes" the keyword array
	       of strings. But it doesn't use it - only the enum list.
*/

enum keywords {
  NOT_A_WORD = -1,   /** not a keyword **/
  A_0,
  A_1,
  A_2,
  A_3,
  ABS,
  AMODE,
  COL_BIN,
  COL_ERR,
  COL_NAME,
  CON_FAC,
  DEL_ABS,
  DEL_APP,
  DEL_COL,
  DGC_FILE,
  DISTANCE,
  DLF_FILE,
  DNR,
  DR_D,
  DR_S,
  DR_T,
  DSK_ABS,
  E_SPHER,
  FAR_DISK,
  FAR_SIDE,
  FAR_SPHD,
  FAR_THIK,
  FMS_FILE,
  GSH_D,
  GSH_T,
  INC,
  LIBRARY,
  M_BRI,
  M_DIM,
  MA_BRT,
  MA_DIM,
  MAG_BIN,
  MAG_NAME,
  MAX_COL,
  MBC,
  MFC,
  MIN_COL,
  MS_FILE,
  OMEGA,
  PSL_D,
  PSL_T,
  R_AC,
  R_EK,
  R_MAX_D,
  R_MAX_S,
  R_MAX_T,
  R_MIN,
  SGC_FILE,
  SLF_FILE,
  TGC_FILE,
  THICK,
  TLF_FILE,
  USE_MS,
  VERBOSE,
  X0,
  Y0,
  NUM_KEYWORDS  /** number of keywords **/
};

static char *keyword[NUM_KEYWORDS] = {
  "A_0",
  "A_1",
  "A_2",
  "A_3",
  "ABS",
  "AMODE",
  "COL_BIN",
  "COL_ERR",
  "COL_NAME",
  "CON_FAC",
  "DEL_ABS",
  "DEL_APP",
  "DEL_COL",
  "DGC_FILE",
  "DISTANCE",
  "DLF_FILE",
  "DNR",
  "DR_D",
  "DR_S",
  "DR_T",
  "DSK_ABS",
  "E_SPHER",
  "FAR_DISK",
  "FAR_SIDE",
  "FAR_SPHD",
  "FAR_THIK",
  "FMS_FILE",
  "GSH_D",
  "GSH_T",
  "INC",
  "LIBRARY",
  "M_BRI",
  "M_DIM",
  "MA_BRT",
  "MA_DIM",
  "MAG_BIN",
  "MAG_NAME",
  "MAX_COL",
  "MBC",
  "MFC",
  "MIN_COL",
  "MS_FILE",
  "OMEGA",
  "PSL_D",
  "PSL_T",
  "R_AC",
  "R_EK",
  "R_MAX_D",
  "R_MAX_S",
  "R_MAX_T",
  "R_MIN",
  "SGC_FILE",
  "SLF_FILE",
  "TGC_FILE",
  "THICK",
  "TLF_FILE",
  "USE_MS",
  "VERBOSE",
  "X0",
  "Y0"
};

/*---------------------------------------------------------------------------*/
