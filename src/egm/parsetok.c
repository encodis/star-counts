/*
   Function : parsetok.c
   Purpose  : External Galaxy Model.
              Parse string for keywords.
   History  : Began: 13 May 1994. Last edit: 4 August 1995.
   Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
   Comments : 1. Parses a line from the parameter file (or -P option) and
                 sets appropriate value.
*/

#include "egm.h"
#include "keyword.h"

void parsetok(BOOL thick, char *line, Param *pm, Model *ml, Optar *op)
{
  char *word1, *word2;

  word1 = strtok(line,SEPCHARS2);
  word2 = strtok(NULL,SEPCHARS2);

  switch (find_idx(word1)) {
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
      quit_egm(ERR_PARM,word2,ml->pfile);
    }
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
  case DEL_APP :
    pm->dm_app = atof(word2); 
    break;
  case DEL_COL :
    pm->d_col = atof(word2); 
    break;
  case DGC_FILE :
    strcpy(ml->dgbfn,word2);
    break;
  case DISTANCE :
    ml->dist = atof(word2);
    break;
  case DLF_FILE :
    strcpy(ml->dlffn,word2);
    break;
  case DNR :
    strcpy(ml->den,word2);
    break;
  case DR_D :
    pm->dr_d = atof(word2); 
    break;
  case DR_S :
    pm->dr_s = atof(word2); 
    break;
  case DR_T :
    pm->dr_t = atof(word2); 
    break;
  case DSK_ABS :
    pm->dabs = atof(word2);
    break;
  case E_SPHER :
    pm->es = atof(word2); 
    break;
  case FAR_DISK :
    if (ISTRUE(word2[0])) op->far_disk = TRUE;
    break;
  case FAR_SIDE :
    if (ISTRUE(word2[0])) {
      op->far_disk = TRUE; op->far_thik = TRUE; op->far_sphd = TRUE;
    }
    break;
  case FAR_SPHD :
    if (ISTRUE(word2[0])) op->far_sphd = TRUE;
    break;
  case FAR_THIK :
    if (ISTRUE(word2[0])) op->far_thik = TRUE;
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
  case INC :
    ml->inc = atof(word2);
    break;
  case LIBRARY :
    strcpy(ml->libry,word2);
    break;
  case M_BRI :
    pm->m_bri = atof(word2); 
    break;
  case M_DIM :
    pm->m_dim = atof(word2); 
    break;
  case MA_BRT :
    pm->ma_brt = atof(word2);
    break;
  case MA_DIM :
    pm->ma_dim = atof(word2);
    break;
  case MAG_BIN :
    pm->dm_bin = atof(word2); 
    break;
  case MAG_NAME :
    strcpy(ml->mag,word2); 
    break;
  case MAX_COL :
    pm->max_col = atof(word2); 
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
  case MS_FILE  :
    strcpy(ml->dmsfn,word2);
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
  case R_AC :
    pm->rac = atof(word2); 
    break;
  case R_EK :
    pm->rek = atof(word2); 
    break;
  case R_MAX_D :
    pm->r_max_d = atof(word2); 
    break;
  case R_MAX_S :
    pm->r_max_s = atof(word2); 
    break;
  case R_MAX_T :
    pm->r_max_t = atof(word2); 
    break;
  case R_MIN :
    pm->r_min = atof(word2); 
    break;
  case SGC_FILE :
    strcpy(ml->sgbfn,word2);
    break;
  case SLF_FILE :
    strcpy(ml->slffn,word2);
    break;
  case TGC_FILE :
    strcpy(ml->tgbfn,word2);
    break;
  case THICK :
    if (ISTRUE(word2[0])) op->thick = TRUE;
    break;
  case TLF_FILE :
    strcpy(ml->tlffn,word2);
    break;
  case USE_MS :
    if (ISTRUE(word2[0])) op->doms = TRUE;
    break;
  case VERBOSE :
    if (ISTRUE(word2[0])) op->v = TRUE;
    break;
  case X0 :
    ml->x0 = atof(word2); 
    break;
  case Y0 :
    ml->y0 = atof(word2); 
    break;
  case NOT_A_WORD : 
    quit_egm(ERR_PARM,word1,ml->pfile);
  }

  return;
}
/*---------------------------------------------------------------------------*/
