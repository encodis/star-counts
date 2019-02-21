/*
   Function : parsetok.c
   Purpose  : Bahcall - Soneira Galactic Model.
              Parse string for keywords.
   History  : Began: 28 April 1994. Last edit: 4 August 1994.
   Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
   Comments : 1. Parses a line from the parameter file (or -P option) and
                 sets appropriate value.
*/

#include "mubsm.h"
#include "keyword.h"

void parsetok(BOOL thick, char *line, Param *pm, Model *ml)
{
  char *word1, *word2;

  word1 = strtok(line,SEPCHARS);
  word2 = strtok(NULL,SEPCHARS);
  
  switch (find_index(word1)) {
  case A_0 :
    pm->a[0] = atof(word2); 
    break;
  case A_1 :
    pm->a[1] = atof(word2); 
    break;
  case A_2 :
    pm->a[2] = atof(word2); 
    break;
  case A_3 :
    pm->a[3] = atof(word2); 
    break;
  case ABS :
    pm->abs = atof(word2);
    break;
  case AMODE :
    switch (word2[0]) {
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
      quit_bsm(ERR_PARM,word2,ml->pfile);
    }
    break;
  case B2 :
    ml->b2 = atof(word2); 
    break;
  case COL_BIN :
    pm->i_col = atof(word2); 
    break;
    case COL_ERR :
      pm->s_col = atof(word2); 
    break;
  case COL_NAME :
    strcpy(ml->col,word2); 
    break;
  case CON_FAC :
    pm->c_fac = atof(word2); 
    break;
  case DEL_ABS :
    pm->dm_abs = atof(word2); 
    break;
  case DEL_MU :
    pm->del_mu = atof(word2); 
    break;
  case DEL_COL :
    pm->d_col = atof(word2); 
    break;
  case DGC_FILE :
    strcpy(ml->dgbfn,word2);
    break;
  case DLF_FILE :
    strcpy(ml->dlffn,word2);
    break;
  case DMS_FILE :
    strcpy(ml->dmsfn,word2);
    break;
  case DN :
    if (thick == TRUE) {
      pm->dn[DSK] = atof(strtok(word2,SEPCHARS));
      pm->dn[THK] = atof(strtok(NULL,SEPCHARS));
      pm->dn[SPH] = atof(strtok(NULL,SEPCHARS));
    } else {
      pm->dn[DSK] = atof(strtok(word2,SEPCHARS));
      pm->dn[THK] = 0.0;
      pm->dn[SPH] = atof(strtok(NULL,SEPCHARS));
    }
  case DSH_B_H :
    ml->dsh_b_h = atof(word2); 
    break;
  case DSH_B_M :
    ml->dsh_b_m = atof(word2); 
    break;
  case DSH_F_H :
    ml->dsh_f_m = atof(word2); 
    break;
  case DSH_F_M :
    ml->dsh_f_m = atof(word2); 
    break;
  case E_SPHER :
    pm->es = atof(word2); 
    break;
  case FMS_FILE :
    strcpy(ml->fmsfn,word2);
    break;
  case GSH_D :
    pm->gsh_d = atof(word2); 
    break;
  case GSH_T :
    pm->gsh_t = atof(word2); 
    break;
  case L2 :
    ml->l2 = atof(word2); 
    break;
  case LIBRARY :
    strcpy(ml->libry,word2);
    break;
  case M_BRD :
    pm->m_brd = atof(word2); 
    break;
  case M_BRS :
    pm->m_brs = atof(word2); 
    break;
  case M_DIM :
    pm->m_dim = atof(word2); 
    break;
  case MAG_BIN :
    pm->dm_bin = atof(word2);
    break;
  case MAX_COL :
    pm->max_col = atof(word2); 
    break;
  case MAG :
    pm->mag = atof(word2);
    break;
  case MAG_NAME :
    strcpy(ml->mag,word2); 
    break;
  case MBC :
    pm->mbc = atof(word2); 
    break;
  case MFC :
    pm->mfc = atof(word2); 
    break;
  case MIN_COL :
    pm->min_col = atof(word2); 
    break;
  case MTO :
    pm->mturn = atof(word2);
    break;
  case MU_BRT :
    pm->mu_brt = atof(word2);
    break;
  case MU_DIM :
    pm->mu_dim = atof(word2);
    break;
  case OMEGA :
    ml->omega = atof(word2); 
    break;
  case PSL_D :
    pm->psl_d = atof(word2); 
    break;
  case PSL_T :
    pm->psl_t = atof(word2); 
    break;
  case R_0 :
    pm->r0 = atof(word2); 
    break;
  case R_EK :
    pm->rek = atof(word2); 
    break;
  case SGC_FILE :
    strcpy(ml->sgbfn,word2);
    break;
  case SLF_FILE :
    strcpy(ml->slffn,word2);
    break;
  case SMS_FILE :
    strcpy(ml->smsfn,word2);
    break;
  case TSH_B_H :
    ml->tsh_b_h = atof(word2); 
    break;
  case TSH_B_M :
    ml->tsh_b_m = atof(word2); 
    break;
  case TSH_F_H :
    ml->tsh_f_h = atof(word2); 
    break;
  case TSH_F_M :
    ml->tsh_f_m = atof(word2); 
    break;
  case TGC_FILE :
    strcpy(ml->tgbfn,word2);
    break;
  case TLF_FILE :
    strcpy(ml->tlffn,word2);
    break;
  case TMS_FILE :
    strcpy(ml->tmsfn,word2);
    break;
  case NOT_A_WORD : 
    quit_bsm(ERR_PARM,word1,ml->pfile);
  }
  
  return;
}
/*---------------------------------------------------------------------------*/
