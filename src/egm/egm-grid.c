/*
   Program : egm-grid
   Function: External Galaxy Model.
             Run models over 2-D parameter grid.
   History : Began: 16 August 1994. Last edit: 18 August 1994.
   Author  : P.J.C.Hodder (hodder@geop.ubc.ca)
   Usage   : egm-grid pref pfile p1 min1 max1 del1 p2 min2 max2 del2
   Comments: 1. A bit of a hack really...especially with the command line
                parsing!
             2. Each file is named: pref_val1_val2
	     3. p1, p2 should be, for example, "-x" and "-y".
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE  1
#define FALSE 0
#define USAGE fprintf(stderr,"Usage: egm-grid [-t] prefix pfile par1 min1 max1 del1 [par2 min2 max2 del2]\n")

void main(int argc, char **argv)
{
  int   a = 0, t = FALSE, s = FALSE;
  char  cmd[1025];
  char  out[81];
  char  tmp[81];
  float val1, val2;

  char  pref[81];
  char  file[81];
  char  par1[3];
  float min1, max1, del1;
  char  par2[3];
  float min2, max2, del2;

  /* check args */
  if (argc > 1 && !strcmp(argv[1],"-t")) { t = TRUE; argc--; a = 1; }
  if (argc != 11 && argc != 7) { USAGE; exit(1); }
  if (argc == 11) s = TRUE;

  /* assign args */
  strcpy(pref,argv[1+a]);
  strcpy(file,argv[2+a]);

  strcpy(par1,argv[3+a]);
  min1 = atof(argv[4+a]); max1 = atof(argv[5+a]); del1 = atof(argv[6+a]);

  /* check arg values */
  if (min1 >= max1 || del1 <= 0.0) { USAGE; exit(1); }

  if (s == TRUE) {
    strcpy(par2,argv[7+a]);
    min2 = atof(argv[8+a]); max2 = atof(argv[9+a]); del2 = atof(argv[10+a]);

    /* check arg values */
    if (min2 >= max2 || del2 <= 0.0) { USAGE; exit(1); }
  }

  /* begin loop - one or two axes */
  if (s == TRUE) {
    for (val1=min1; val1<=max1; val1+=del1) {
      for (val2=min2; val2<=max2; val2+=del2) {
      
	/* assemble output file name */
	strcpy(out,pref); 
	sprintf(tmp,"_%g",val1); strcat(out,tmp);
	sprintf(tmp,"_%g",val2); strcat(out,tmp);
	
	/* assemble command string */
	strcpy(cmd,"egm "); strcat(cmd,file); strcat(cmd," ");
	strcat(cmd,"-o "); strcat(cmd,out); strcat(cmd," ");
	strcat(cmd,par1); sprintf(tmp," %g ",val1); strcat(cmd,tmp);
	strcat(cmd,par2); sprintf(tmp," %g ",val2); strcat(cmd,tmp);

	if (t == TRUE) { printf("%s\n",cmd);} else { system(cmd); }
      }
    }
  } else {
    for (val1=min1; val1<=max1; val1+=del1) {
      
      /* assemble output file name */
      strcpy(out,pref); 
      sprintf(tmp,"_%g",val1); strcat(out,tmp);
      
      /* assemble command string */
      strcpy(cmd,"egm "); strcat(cmd,file); strcat(cmd," ");
      strcat(cmd,"-o "); strcat(cmd,out); strcat(cmd," ");
      strcat(cmd,par1); sprintf(tmp," %g ",val1); strcat(cmd,tmp);
      
      if (t == TRUE) { printf("%s\n",cmd); } else { system(cmd); }
    }
  }
  
  exit(0);
}
/*---------------------------------------------------------------------------*/
