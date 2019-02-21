/*
  Function : scan_com.c
  Purpose  : External Galxay Model.
             Parse command line arguments.
  History  : Began: 6 October 1992. Last edit: 4 May 1995.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. The Optar structure  stores values for  various command line
                options.
	     2. The parameter file has already been read - thus command line
	        options override the parameter file. Only parse for options.
*/
#include "egm.h"

void scan_com(int argc, char **argv, Param *pm, Model *ml, Optar *op)
{
  int p;                               /* Number of parsed arguments   */

  for (p=1; p<argc; p++) {
    switch(argv[p][0]) {
    case '-' :
      switch(argv[p][1]) {
      case 'a' :
	switch (argv[p+1][0]) {            /* absorption mode     */
	case 'c' :
	case 'C' :
	  pm->amode = CS;
	  break;
	  
	case 'n' :
	case 'N' :
	  pm->amode = NA;
	  break;
	  
	case 's' :
	case 'S' :
	  pm->amode = SA;
	  break;
	  
	default :
	  quit_egm(ERR_CARG, argv[p+1], NULL_STR);
	}
	p++;
	break;
	
      case 'A' :                           /* fixed abspn. value  */
	pm->abs = atof(argv[p+1]);
	p++;
	break;
	
      case 'b' :
	pm->dm_bin = atof(argv[p+1]);
	p++;
	break;
	
      case 'c' :
	switch (argv[p][2]) {
	case 'b' :                         /* brt. mag. col. dist */
	  pm->mbc = atof(argv[p+1]);
	  p++;
	  break;
	  
	case 'e' :                         /* colour error        */
	  pm->s_col = atof(argv[p+1]);
	  p++;
	  break;
	  
	case 'f' :                         /* fnt. mag. col. dist */
	  pm->mfc = atof(argv[p+1]);
	  p++;
	  break;
	  
	case 'l' :                         /* min. col.           */
	  pm->min_col = atof(argv[p+1]);
	  p++;
	  break;
	  
	case 'u' :                         /* max. col.           */
	  pm->max_col = atof(argv[p+1]);
	  p++;
	  break;
	  
	default :
	  quit_egm(ERR_CARG, argv[p], NULL_STR);
	}
	break;
	
      case 'd' :
	switch (argv[p][2]) {
	case 'm' :                         /* app. mag. interval  */
	  pm->dm_app = atof(argv[p+1]);
	  p++;
	  break;
	  
	case 'M' :                         /* abs. mag. interval  */
	  pm->dm_abs = atof(argv[p+1]);
	  p++;
	  break;
	  
	case 'n' :                         /* density norm.       */
	  strcpy(ml->den,argv[p+1]);
	  p++;
	  break;
	  
	default :
	  quit_egm(ERR_CARG, argv[p], NULL_STR);
	}
	break;
	
      case 'D' :
	ml->dist = atof(argv[p+1]);        /* distance            */
	p++;
	break;
	
      case 'e' :
	pm->es = atof(argv[p+1]);          /* spheroid ecc.       */
	p++;
	break;
	
      case 'F' :                           /* integrate far side  */
	if (strlen(argv[p]) > 2) {
	  switch (argv[p][2]) {
	  case 'D' :
	    op->far_disk = TRUE;
	    break;
	  case 'T' :
	    op->far_thik = TRUE;
	    break;
	  case 'S' :
	    op->far_sphd = TRUE;
	    break;
	  default :
	  op->far_disk = TRUE; op->far_thik = TRUE; op->far_sphd = TRUE;
	  }
	} else {
	  op->far_disk = TRUE; op->far_thik = TRUE; op->far_sphd = TRUE;
	}
	break;
	
      case 'f' :
	ml->omega = atof(argv[p+1]);       /* field size          */
	p++;
	break;

      case 'h' :                           /* print help          */
	quit_egm(ERR_USE1, NULL_STR, NULL_STR);
	break;

      case 'H' :                           /* print keyword help  */
	quit_egm(ERR_USE2, NULL_STR, NULL_STR);
	break;

      case 'i' :                           /* inclination         */
	ml->inc = atof(argv[p+1]);
	p++;
	break;
	
      case 'L' :
	strcpy(ml->libry,argv[p+1]);       /* location of files   */
	p++;
	break;
	
      case 'm' :
	switch (argv[p][2]) {
	case 'b' :                         /* brightest app. mag. */
	  pm->ma_brt = atof(argv[p+1]);  
	  p++;
	  break;
	  
	case 'f' :                         /* faintest app. mag.  */
	  pm->ma_dim = atof(argv[p+1]);
	  p++;
	  break;
	  
	default :
	  quit_egm(ERR_CARG, argv[p], NULL_STR);
	}
	break;
	
      case 'M' :
	switch (argv[p][2]) {
	case 'f' :                         /* faintest abs. mag.  */
	  pm->m_dim = atof(argv[p+1]);
	  p++;
	  break;
	  
	case 'b' :                         /* brightest. abs. mag.*/
	  pm->m_bri = atof(argv[p+1]);
	  p++;
	  break;
	  
	case 'S' :
	  op->doms = TRUE;                 /* use m-s cmds        */
	  break;
	  
	default :
	  quit_egm(ERR_CARG, argv[p], NULL_STR);
	}
	break;
	
      case 'o' :
	strcpy(ml->ofile,argv[p+1]);       /* output file         */
	p++;
	break;
	
      case 'P' :                           /* in-line par. file   */
	parsetok(op->thick, argv[p+1], pm, ml, op);
	p++;
	break;

      case 'r' :
	pm->rek = atof(argv[p+1]);         /* eff. radius of sphd */
	p++;
	break;
	
      case 's' :
	switch (argv[p][2]) {
	case 'l' :                         /* disk scale length   */
	  pm->psl_d = atof(argv[p+1]);
	  p++;
	  break;
	  
	case 'h' :                         /* disk scale height   */
	  pm->gsh_d = atof(argv[p+1]);
	  p++;
	  break;
	  
	default :
	  quit_egm(ERR_CARG, argv[p], NULL_STR);
	}
	break;
	
      case 'T' :                           /* use thick disk      */
	op->thick = TRUE;
	break;
	
      case 'V' :
	op->v = TRUE;                      /* verbose mode        */
	break;
	
      case 'x' :
	ml->x0 = atof(argv[p+1]);          /* field position      */
	p++;
	break;
	
      case 'y' :
	ml->y0 = atof(argv[p+1]);          /* field position      */
	p++;
	break;
	
      default :
	quit_egm(ERR_CARG, argv[p], NULL_STR);
      }
      break;

    default :                              /* parameter file      */
      strcpy(ml->pfile, argv[p]);
      read_par(op->thick, pm, ml, op);
    }
  }
  
  return;
}
/*---------------------------------------------------------------------------*/
