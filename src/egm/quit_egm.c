/*
  Function : quit_egm.c
  Purpose  : External Galaxy Model.
             Report errors and exit with appropriate error code.
  History  : Began: 6 October 1992. Last edit: 4 May 1995.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. Takes as arguments an error code (integer) and two strings.
                The strings may  be used for messages and for function  and
		and file names. Recommended use is string1 for messages and
		string2 for the function in which the error occurred or the
		filename in which the open/read error happened.
*/

#include "egm.h"

int quit_egm(int ecode, char *string1, char *string2)
{
  char e[4096];

  if (ecode <= ERR_USE2) {
    strcpy(e,NULL_STR);
  } else {
    strcpy(e,"\n*** EGM: ");
  }

  switch (ecode) {
  case ERR_USE1 :
    strcat(e,"Usage: egm [parameter_file] [options] [> output_file]\n\n");
    strcat(e,"Options:\n");
    strcat(e,"    -a   $     absorption mode (None, Cosec or Sandage)\n");
    strcat(e,"    -A   #     fixed absorption value\n");
    strcat(e,"    -bm  #     magnitude bin size for output\n");
    strcat(e,"    -cb  #     brightest magnitude for colour distn.\n");
    strcat(e,"    -ce  #     colour error\n");
    strcat(e,"    -cf  #     faintest magnitude for colour distn.\n");
    strcat(e,"    -cl  #     min colour in colour distn.\n");
    strcat(e,"    -cu  #     max colour in colour distn.\n");
    strcat(e,"    -dm  #     apparent magnitude interval\n");
    strcat(e,"    -dM  #     absolute magnitude interval\n");
    strcat(e,"    -dn  #:#:# density normalization radii (disk:thick:spd)\n");
    strcat(e,"    -D   #     distance to galaxy in parsecs\n");
    strcat(e,"    -es  #     eccentricity of spheroid\n");
    strcat(e,"    -f   #     field size in square degrees\n");
    strcat(e,"    -F         integrate far side of all components\n");
    strcat(e,"    -FD        integrate far side of disk \n");
    strcat(e,"    -FS        integrate far side of spheroid\n");
    strcat(e,"    -FT        integrate far side of thick disk\n");
    strcat(e,"    -h         print this help message\n");
    strcat(e,"    -H         print keyword list\n");
    strcat(e,"    -i   #     inclination\n");
    strcat(e,"    -L   $     path to LF and CMD library\n");     
    strcat(e,"    -mb  #     brightest apparent magnitude\n");
    strcat(e,"    -mf  #     faintest apparent magnitude\n");
    strcat(e,"    -Mb  #     brightest absolute magnitude\n");
    strcat(e,"    -Mf  #     faintest absolute magnitude\n");
    strcat(e,"    -MS        include disk main-sequence\n");
    strcat(e,"    -o   $     file for output\n");
    strcat(e,"    -P   $     additional parameters in .pm format\n");
    strcat(e,"    -re  #     effective radius of spheroid\n");
    strcat(e,"    -sl  #     scale length of disk\n");
    strcat(e,"    -sh  #     scale height of disk\n");
    strcat(e,"    -T         include thick disk\n");
    strcat(e,"    -V         verbose mode\n");
    strcat(e,"    -x   #     position along major axis\n");
    strcat(e,"    -y   #     position along minor axis\n\n");
    strcat(e," where # = number (real), $ = string/file name/path");
    break;

  case ERR_USE2 :
    strcat(e,"Usage: egm [parameter_file] [options] [> output_file]\n\n");
    strcat(e,"Keywords:\n");
    strcat(e,"A_0      = #     absorption scale height\n");
    strcat(e,"A_1      = #     cosecant law absorption coefficient\n");
    strcat(e,"A_2      = #     Sandage absorption coefficient\n");
    strcat(e,"A_3      = #     Sandage absorption offset\n");
    strcat(e,"ABS      = #     fixed value of absorption\n");
    strcat(e,"AMODE    = $     absorption mode (None, Sandage, Cosec)\n");
    strcat(e,"COL_BIN  = #     colour bin size\n");
    strcat(e,"COL_ERR  = #     colour error\n");
    strcat(e,"COL_NAME = $     colour name\n");
    strcat(e,"CON_FAC  = #     convergence factor \n");
    strcat(e,"DEL_ABS  = #     absolute magnitude interval\n");
    strcat(e,"DEL_APP  = #     apparent magnitude interval\n");
    strcat(e,"DEL_COL  = #     colour interval for calculations\n");
    strcat(e,"DGC_FILE = $     disk giant branch CMD\n");
    strcat(e,"DISTANCE = #     distance to galaxy in parsecs\n");
    strcat(e,"DLF_FILE = $     disk LF file\n");
    strcat(e,"DNR      = #:#:# density normalization radii (dsk:thk:spd)\n");
    strcat(e,"DR_D     = #     distance step for disk in parsecs\n");
    strcat(e,"DR_S     = #     distance step for spheroid in parsecs\n");
    strcat(e,"DR_T     = #     distance step for thick disk in parsecs\n");
    strcat(e,"DSK_ABS  = #     absorption through disk\n");
    strcat(e,"E_SPHER  = #     ellipticity of spheroid\n");
    strcat(e,"FAR_DISK = $     integrate far side of disk (Y/N)\n");
    strcat(e,"FAR_SIDE = $     integrate far side of all (Y/N)\n");
    strcat(e,"FAR_SPHD = $     integrate far side of spheroid (Y/N)\n");
    strcat(e,"FAR_THIK = $     integrate far side of thick disk (Y/N)\n");
    strcat(e,"FMS_FILE = $     fraction of stars on MS\n");
    strcat(e,"GSH_D    = #     scale height of disk giants\n");
    strcat(e,"GSH_T    = #     scale height of thick disk giants\n");
    strcat(e,"INC      = #     inclination of the disk, in degrees\n");
    strcat(e,"LIBRARY  = $     path to library files\n");
    strcat(e,"M_BRI    = #     brightest absolute magnitude in LF\n");
    strcat(e,"M_DIM    = #     dimmest absolute magnitude in LF\n");
    strcat(e,"MA_BRT   = #     brightest apparent magnitude in model\n");
    strcat(e,"MA_DIM   = #     dimmest apparent magnitude in model\n");
    strcat(e,"MAG_BIN  = #     output bin size\n");
    strcat(e,"MAG_NAME = $     filter name\n");
    strcat(e,"MAX_COL  = #     maximum colour in colour distribution.\n");
    strcat(e,"MBC      = #     brightest mag. to use in colour distn.\n");
    strcat(e,"MFC      = #     faintest  mag. to use in colour distn.\n");
    strcat(e,"MIN_COL  = #     minimum colour in colour distribution.\n");
    strcat(e,"MS_FILE  = #     main--sequence file for disk\n");
    strcat(e,"OMEGA    = #     field size in square degrees\n");
    strcat(e,"PSL_D    = #     scale length of disk\n");
    strcat(e,"PSL_T    = #     scale length of thick disk\n");
    strcat(e,"R_AC     = #     cutoff radius for spheroid absorption\n");
    strcat(e,"R_EK     = #     effective radius of spheroid\n");
    strcat(e,"R_MAX_D  = #     maximum distance for disk integration\n");
    strcat(e,"R_MAX_S  = #     maximum distance for thick disk integration\n");
    strcat(e,"R_MAX_T  = #     maximum distance for spheroid integration\n");
    strcat(e,"R_MIN    = #     minimum distance for all integrations\n");
    strcat(e,"SGC_FILE = $     spheroid giant branch CMD\n");
    strcat(e,"SLF_FILE = $     spheroid LF file\n");
    strcat(e,"TGC_FILE = $     thick disk giant branch CMD\n");
    strcat(e,"THICK    = $     include thick disk (Y/N)\n");
    strcat(e,"TLF_FILE = $     thick disk LF file\n");
    strcat(e,"USE_MS   = $     include disk M-S (Y/N)\n");
    strcat(e,"VERBOSE  = $     verbose output (Y/N)\n");
    strcat(e,"X0       = #     position along minor axis (arcmin)\n");
    strcat(e,"Y0       = #     position along major axis (arcmin)\n\n");
    strcat(e," where # = number, $ = string/file name/path");
    break;
    
  case ERR_CARG :
    strcat(e,"Invalid argument '"); 
    strcat(e,string1); 
    strcat(e,"' on command line");
    break;
    
  case ERR_PARM :
    strcat(e,"Invalid parameter '");
    strcat(e,string1); strcat(e,"' in "); strcat(e,string2);
    break;
    
  case ERR_OPEN :
    strcat(e,"Cannot open file '");
    strcat(e,string1); strcat(e,"' in "); strcat(e,string2);
    break;
    
  case ERR_READ :
    strcat(e,"Problem reading '");
    strcat(e,string1); strcat(e,"' in "); strcat(e,string2);
    break;
    
  case ERR_MALC :
    strcat(e,"Cannot allocate memory for '");
    strcat(e,string1); strcat(e,"' in "); strcat(e,string2);
    break;
    
  case ERR_MATH :
    strcat(e,"Math error in ");
    strcat(e,string2); strcat(e,string1);
    break;
  }
  
  if (ecode != ERR_NONE) fprintf(stderr,"%s.\n",e);
  
  exit(ecode);
}
/*---------------------------------------------------------------------------*/
