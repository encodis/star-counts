/*
  Function : quit_bsm.c
  Purpose  : Bahcall - Soneira Galaxy Model. 
             Report errors and exit with appropriate error code.
  History  : Began: 28 May 1992. Last edit: 29 June 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. Takes as arguments an error code (integer) and two strings.
                The strings may  be used for messages and for function  and
		and file names. Recommended use is string1 for messages and
		string2 for the function in which the error occurred or the
		filename in which the open/read error happened.
*/

#include "bsm.h"

int quit_bsm(int ecode, char *string1, char *string2)
{
  char e[4096];

  if (ecode <= ERR_USE2) {
    strcpy(e,NULL_STR);
  } else {
    strcpy(e,"\n*** BSM: ");
  }

  switch (ecode) {
  case ERR_USE1 :
    strcat(e,"Usage: bsm [parameter_file] [options] [> output_file]\n\n");
    strcat(e,"Options:\n");
    strcat(e,"    -a   $     absorption mode (None, Cosec or Sandage)\n");
    strcat(e,"    -A   #     fixed absorption value\n");
    strcat(e,"    -b   #     galactic latitude\n");
    strcat(e,"    -ce  #     colour error\n");
    strcat(e,"    -dm  #     apparent magnitude interval\n");
    strcat(e,"    -dM  #     absolute magnitude interval\n");
    strcat(e,"    -dn  #:#:# density normalization (disk:thick:spd)\n");
    strcat(e,"    -h         print this help message\n");
    strcat(e,"    -H         print keyword list\n");
    strcat(e,"    -l   #     galactic longitude\n");
    strcat(e,"    -L   $     path to LF and CMD library\n");     
    strcat(e,"    -mb  #     brightest apparent magnitude\n");
    strcat(e,"    -mf  #     faintest apparent magnitude\n");
    strcat(e,"    -Md  #     brightest absolute magnitude (disk)\n");
    strcat(e,"    -Mf  #     faintest absolute magnitude\n");
    strcat(e,"    -Ms  #     brightest absolute magnitude (sphd)\n");
    strcat(e,"    -Mt  #     absolute magnitude of turn off\n");
    strcat(e,"    -o   $     file for output\n");
    strcat(e,"    -P   $     additional parameters in .pm format\n");
    strcat(e,"    -s   #     field size in square degrees\n");
    strcat(e,"    -t         include thick disk\n");
    strcat(e,"    -v         verbose mode\n");
    strcat(e,"    -z         print radial distribution\n\n");
    strcat(e," where # = number (real), $ = string/file name/path");
    break;

  case ERR_USE2 :
    strcat(e,"Usage: bsm [parameter_file] [options] [> output_file]\n\n");
    strcat(e,"Keywords:\n");
    strcat(e,"A_0      = #     absorption scale height\n");
    strcat(e,"A_1      = #     cosecant law absorption coefficient\n");
    strcat(e,"A_2      = #     Sandage absorption coefficient\n");
    strcat(e,"A_3      = #     Sandage absorption offset\n");
    strcat(e,"ABS      = #     fixed value of absorption\n");
    strcat(e,"AMODE    = $     absorption mode (None, Sandage, Cosec)\n");
    strcat(e,"B2       = #     galactic latitude\n");
    strcat(e,"COL_BIN  = #     colour bin size\n");
    strcat(e,"COL_ERR  = #     colour error\n");
    strcat(e,"COL_NAME = $     colour name\n");
    strcat(e,"CON_FAC  = #     convergence factor \n");
    strcat(e,"DEL_ABS  = #     absolute magnitude interval\n");
    strcat(e,"DEL_APP  = #     apparent magnitude interval\n");
    strcat(e,"DEL_COL  = #     colour interval for calculations\n");
    strcat(e,"DGC_FILE = $     disk giant branch CMD\n");
    strcat(e,"DLF_FILE = $     disk LF file\n");
    strcat(e,"DMS_FILE = $     disk M-S CMD file\n");
    strcat(e,"DN       = #:#:# density normalization (disk:thick:spd)\n");
    strcat(e,"DR       = #     distance step in parsecs\n");
    strcat(e,"DSH_B_H  = #     disk scale height for stars > DSH_B_M\n");
    strcat(e,"DSH_B_M  = #     disk scale height mag. limit (bright)\n");
    strcat(e,"DSH_F_H  = #     disk scale height for stars < DSH_F_M\n");
    strcat(e,"DSH_F_M  = #     disk scale height mag. limit (faint)\n");
    strcat(e,"E_SPHER  = #     ellipticity of spheroid\n");
    strcat(e,"FMS_FILE = $     fraction of stars on MS\n");
    strcat(e,"GSH_D    = #     scale height of disk giants\n");
    strcat(e,"GSH_T    = #     scale height of thick disk giants\n");
    strcat(e,"L2       = #     galactic longitude\n");
    strcat(e,"LIBRARY  = $     path to library files\n");
    strcat(e,"M_BRD    = #     brightest absolute magnitude for disk LF\n");
    strcat(e,"M_BRS    = #     brightest absolute magnitude for sphd LF\n");
    strcat(e,"M_DIM    = #     dimmest absolute magnitude in LF\n");
    strcat(e,"MA_BRT   = #     brightest apparent magnitude in model\n");
    strcat(e,"MA_DIM   = #     dimmest apparent magnitude in model\n");
    strcat(e,"MAG_BIN  = #     output bin size\n");
    strcat(e,"MAG_NAME = $     filter name\n");
    strcat(e,"MAX_COL  = #     maximum colour in colour distribution.\n");
    strcat(e,"MBC      = #     brightest mag. to use in colour distn.\n");
    strcat(e,"MFC      = #     faintest  mag. to use in colour distn.\n");
    strcat(e,"MIN_COL  = #     minimum colour in colour distribution.\n");
    strcat(e,"MTO      = #     absolute magnitude of turn off\n");
    strcat(e,"OMEGA    = #     field size in square degrees\n");
    strcat(e,"PSL_D    = #     scale length of disk\n");
    strcat(e,"PSL_T    = #     scale length of thick disk\n");
    strcat(e,"R_0      = #     distance to galactic centre in parsecs\n");
    strcat(e,"R_EK     = #     effective radius of spheroid\n");
    strcat(e,"R_MAX_D  = #     maximum distance for disk integration\n");
    strcat(e,"R_MAX_S  = #     maximum distance for thick disk integration\n");
    strcat(e,"R_MAX_T  = #     maximum distance for spheroid integration\n");
    strcat(e,"R_MIN    = #     minimum distance for all integrations\n");
    strcat(e,"SGC_FILE = $     spheroid giant branch CMD\n");
    strcat(e,"SLF_FILE = $     spheroid LF file\n");
    strcat(e,"SMS_FILE = $     spheroid M-S CMD file\n");
    strcat(e,"TGC_FILE = $     thick disk giant branch CMD\n");
    strcat(e,"TLF_FILE = $     thick disk LF file\n");
    strcat(e,"TMS_FILE = $     thick disk M-S CMD file\n");
    strcat(e,"TSH_B_H  = #     thick disk scale ht. for stars > TSH_B_M\n");
    strcat(e,"TSH_B_M  = #     thick disk scale ht. mag. limit (bright)\n");
    strcat(e,"TSH_F_H  = #     thick disk scale ht. for stars < TSH_F_M\n");
    strcat(e,"TSH_F_M  = #     thick disk scale ht. mag. limit (faint)\n\n");
    strcat(e," where # = number, $ = string/file name/path");
    break;
   
  case ERR_CARG :
    strcat(e,"Invalid argument '");
    strcat(e,string1);
    strcat(e,"' on command line. Use bsm -h for help");
    break;
    
  case ERR_PARM :
    strcat(e,"Invalid parameter '");
    strcat(e,string1);
    strcat(e,"' in ");
    strcat(e,string2);
    break;
    
  case ERR_OPEN :
    strcat(e,"Cannot open file '");
    strcat(e,string1);
    strcat(e,"' in ");
    strcat(e,string2);
    break;
    
  case ERR_READ :
    strcat(e,"Problem reading '");
    strcat(e,string1);
    strcat(e,"' in ");
    strcat(e,string2);
    break;
    
  case ERR_MALC :
    strcat(e,"Cannot allocate memory for '");
    strcat(e,string1);
    strcat(e,"' in ");
    strcat(e,string2);
    break;
    
  case ERR_MATH :
    strcat(e,"Math error in ");
    strcat(e,string2);
    strcat(e,": ");
    strcat(e,string1);
    break;
  }
  
  if (ecode != ERR_NONE) fprintf(stderr,"%s.\n",e);
  
  exit(ecode);
}
/*---------------------------------------------------------------------------*/
