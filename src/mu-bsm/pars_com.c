/*
  Function : pars_com.c
  Purpose  : MU space. Bahcall - Soneira Galaxy Model. 
             Parse command line arguments.
  History  : Began: 25 June 1991. Last edit: 4 August 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. The Optar structure stores values for various command line
                options.
	     2. Changed alot - parameter file no longer required. Parameter 
	        file is processed immediately, therefore values in the 
		parameter file can be overidden by following arguments. Also 
		can now specify multiple parameter files which will be read 
		in turn.
*/

#include "mubsm.h"

void pars_com(int argc, char *argv[], Param *pm, Model *ml, Optar *op)
{
  int  p;                              /* number of parsed arguments      */

  for (p=1; p<argc; p++) {
    switch(argv[p][0]) {
    case '-' :
      switch(argv[p][1]) {
      case 'a' :                                      /* absorption mode     */
	switch (argv[p+1][0]) {
	case 'c':
	case 'C' :
	  pm->amode = CS;
	  break;
	  
	case 'n':
	case 'N' :
	  pm->amode = NA;
	  break;
	  
	case 's':
	case 'S' :
	  pm->amode = SA;
	  break;
	  
	default :
	  quit_bsm(ERR_CARG, argv[p+1], NULL_STR);
	}
	p++;
	break;
	      
      case 'A' :                                      /* fixed abs value     */
	pm->abs = atof(argv[p+1]);
	p++;
	break;
	
      case 'b' :                                      /* gal. latitude       */
	ml->b2 = atof(argv[p+1]);
	p++;
	break;
	
      case 'c' :                                      /* colour error        */
	pm->s_col = atof(argv[p+1]);
	p ++;
	break;
	
      case 'd' :
	switch (argv[p][2]) {
	case 'u' :                                    /* mu interval         */
	  pm->del_mu = atof(argv[p+1]);
	  p++;
	  break;
	  
	case 'M' :                                    /* abs. mag. interval  */
	  pm->dm_abs = atof(argv[p+1]);
	  p++;
	  break;
	  
	case 'n' :                                    /* density norm.       */
	  if (op->thick == TRUE) {
	    pm->dn[DSK] = atof(strtok(argv[p+1],SEPCHARS));
	    pm->dn[THK] = atof(strtok(NULL,SEPCHARS));
	    pm->dn[SPH] = atof(strtok(NULL,SEPCHARS));
	  }  else {
	    pm->dn[DSK] = atof(strtok(argv[p+1],SEPCHARS));
	    pm->dn[THK] = 0.0;
	    pm->dn[SPH] = atof(strtok(NULL,SEPCHARS));
	  }
	  p++;                          
	  break;
	  
	default :
	  quit_bsm(ERR_CARG,argv[p],NULL_STR);
	}
	break;
	      
      case 'h' :                                      /* print help          */
	quit_bsm(ERR_USE1,NULL_STR,NULL_STR);
	break;

      case 'H' :                                      /* print more help     */
	quit_bsm(ERR_USE2,NULL_STR,NULL_STR);
	break;
		 
      case 'l' :
	ml->l2 = atof(argv[p+1]);                     /* gal. longitude      */
	p++;
	break;
	
      case 'L' :
	strcpy(ml->libry,argv[p+1]);                  /* location of files   */
	p++;
	break;
	      
      case 'u' :
	switch (argv[p][2]) {
	case 'b' :                                    /* brightest mu        */
	  pm->mu_brt = atof(argv[p+1]);
	  p++;
	  break;
		  
	case 'f' :                                    /* faintest mu         */
	  pm->mu_dim = atof(argv[p+1]);
	  p++;
	  break;
	  
	default :
	  quit_bsm(ERR_CARG,argv[p],NULL_STR);
	}
	break;
	
      case 'm' :                                      /* THE magnitude!      */
	pm->mag = atof(argv[p+1]);
	p++;
	break;

      case 'M' :
	switch (argv[p][2]) {
	case 'd' :                                    /* brt. abs. mag. disk */
	  pm->m_brd = atof(argv[p+1]);
	  p++;
	  break;
	  
	case 'f' :                                    /* faintest abs. mag.  */
	  pm->m_dim = atof(argv[p+1]);
	  p++;
	  break;
	  
	case 's' :                                    /* brt. abs. mag. spher*/
	  pm->m_brs = atof(argv[p+1]);
	  p++;
	  break;

	case 't' :                                    /* abs. mag. turn off  */
	  pm->mturn = atof(argv[p+1]);
	  p++;
	  break;
	  
	default :
	  quit_bsm(ERR_CARG,argv[p],NULL_STR);
	}
	break;
	
      case 'o' :                                      /* output file         */
	strcpy(ml->ofile,argv[p+1]);
	p++;
	break;
	
      case 'P':                                       /* in-line par. file   */
	parsetok(op->thick,argv[p+1], pm, ml);
	p++;
	break;
	
      case 's' :                                      /* field size          */
	ml->omega = atof(argv[p+1]);
	p++;
	break;
	
      case 't' :                                      /* use thick disk      */
	op->thick = TRUE;
	break;
	
      case 'v' :
	op->v = TRUE;                                 /* verbose mode        */
	break;
	
      default :
	quit_bsm(ERR_CARG,argv[p],NULL_STR);
      }
      break;
      
    default :                                         /* parameter file      */
      strcpy(ml->pfile,argv[p]);
      read_par(op->thick, pm, ml);
    }
  }
  
  return;  
}
/*---------------------------------------------------------------------------*/
