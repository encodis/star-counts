/*
   Program : egmcmp
   Function: External Galaxy Model.
             Compare egm model against a data file with observed counts
	     and compute a quality factor - for any number of pairs of files.
   History : Began: 23 April 1995.
   Author  : P.J.C.Hodder (hodder@geop.ubc.ca)
   Usage   : egmcmp [options] comp bright faint egm_file data_file  [e d ...]
   Comments: 1. A bit of a hack really...
*/   

#include "gmutil.h"

#define DSK 1
#define SPH 2
#define TOT 3

#define USAGE fprintf(stderr,"Usage: egmcmp [-cqrv#] d|s|t br ft egm_file dat_file [egm_file data_file...]\n")

int read_egm(char *, double **, double **, int);
int read_dat(char *, double **, double **, double **, double **, 
	     double **, double **);

/** MAIN **/
void main(int argc, char **argv)
{
  int    a = 0, v = 0, c = 0, r = 0, m = 1, p;
  char   egm[128], dat[128];
  double br, ft;
  double chisq = 0.0, num = 0.0;        /* chi sq stat and num of points */
  int    i, j, k;

  double t1, t2, t3, t4;                /* temp variables                */

  int    e_num;
  double *e_mag, *e_mod;
  int    d_num;
  double *d_mag, *d_raw, *d_rer, *d_obs, *d_oer, *d_con;
  
  /** parse command line **/
  if (argc < 6) { USAGE; exit(1); }

  if (argv[1][0] == '-') {
    a = 1;
    for (i=1; i<strlen(argv[1]); i++) {
      switch(argv[1][i]) {
      case 'c' :
	c = 1; break;
      case 'q' :
        c = 0; break;
      case 'r' :
	r = 1; break;
      case 'v' :
	v = 1; break;
      default :
        if (isdigit(argv[1][i])) {
	  m = (int) argv[1][i] - 48;
        } else {
	  USAGE; exit(1); 
        }
      }
    }
  }

  switch (argv[a+1][0]) {
  case 'd' :
    p = DSK; break;
  case 's' :
    p = SPH; break;
  case 't' :
    p = TOT; break;
  default :
    USAGE; exit(1);
  }

  br = atof(argv[a+2]);
  ft = atof(argv[a+3]);
  
  if (br > ft) { USAGE; exit(1); }

  if (v) printf("# V      MOD      RAW      OBS      CON\n");

  /** read pairs of files **/
  for (k=4+a; k<argc; k+=2) {

    strcpy(egm,argv[k]);
    strcpy(dat,argv[k+1]);

    /** read data **/
    d_num = read_dat(dat, &d_mag, &d_raw, &d_rer, &d_obs, &d_oer, &d_con);
    e_num = read_egm(egm, &e_mag, &e_mod, p);

    if (d_num <= 0 || e_num <= 0) { ERFIL; exit(1); }

    /** compare **/
    for (i=0; i<e_num; i++) {
      if (e_mag[i] <= ft && e_mag[i] >= br) {
	for (j=0; j<d_num; j++) {
	  if (e_mag[i] != d_mag[j]) continue;
	  if (d_obs[j] < 0) continue;
	  
	  switch(m) {
            case 1 :
              t1 = e_mod[i] - (d_obs[j] - d_con[j]);
              chisq = chisq + ( (t1 * t1) / (d_oer[j] * d_oer[j] + d_con[j]) );
              num = num + 1.0;
              break;

            case 2 :
              t1 = d_obs[j] / d_raw[j];          /* incompleteness  */
              t2 = d_raw[j] - (d_con[j] / t1);   /* cont. corrected */
              t3 = e_mod[i] - t1 * t2;           /* difference      */
              chisq = chisq + ( (t3 * t3) / (t1 * t1 * t2) );
              num = num + 1.0;
              break;

            case 3 :
              t1 = e_mod[i] - (d_obs[j] - d_con[j]);
              chisq = chisq + ( (t1 * t1) / (d_obs[j] + d_con[j]) );
              num = num + 1.0;
              break;

	    default :
              ERMTH;
	      exit(1);
          }
	  
	  if (v) printf("%5.2f %8.3f %8.3f %8.3f %8.3f\n",
		         e_mag[i], e_mod[i], d_raw[j], d_obs[j], d_con[j]);
	  
	}
      }
    }

    DeAlloc(d_mag); DeAlloc(d_raw); DeAlloc(d_rer);
    DeAlloc(d_obs); DeAlloc(d_oer); DeAlloc(d_con);
    DeAlloc(e_mag); DeAlloc(e_mod);

  }

  if (c) {
    if (v) printf("%g (%.0f)\n",gammq(0.5*num,0.5*chisq), num);
    if (r) chisq = chisq / num;
    printf("%g\n",chisq);
  } else {
    if (v) printf("%g (%.0f)\n",chisq, num);
    printf("%g\n",gammq(0.5*num,0.5*chisq));
  }

  exit(0);
}

/** ADDITIONAL FUNCTIONS **/

#define MAXFCH 81
#define MBLOCK 10

/** Read egm file **/

int read_egm(char *file, double **x, double **y, int cmp)
{
  FILE   *e;
  char   line[MAXFCH];  
  double m, d, s, t;
  int    i, n;

  if (!strcmp(file,"-")) {
    e = stdin;
  } else {
    e = fopen(file,"r");
  }
      
  if (e == NULL) { EROPN; exit(1); }

  Alloc(*x,MBLOCK); Alloc(*y,MBLOCK);
  i = 0; n = 1;
  
  /* read past header */
  while (fgets(line,MAXFCH,e)) {
    if (line[0] != '#') break;
  }

  /* need that line! */
  sscanf(line,"%*lf %lf %*lf %lf %*lf %lf %*lf %lf %*lf", &m, &d, &s, &t);
  *(*x+i) = m;
  switch (cmp) {
  case DSK :
    *(*y+i) = d; break;
  case SPH :
    *(*y+i) = s; break;
  case TOT :
    *(*y+i) = t; break;
  }
  i++;

  while(fgets(line,MAXFCH,e)) {
    if (i+1 == n*MBLOCK) {
      n++; ReAlloc(*x,n*MBLOCK); ReAlloc(*y,n*MBLOCK); 
    }
    if (line[0] == '#') break;
    
    sscanf(line,"%*lf %lf %*lf %lf %*lf %lf %*lf %lf %*lf", &m, &d, &s, &t);

    *(*x+i) = m;
    switch (cmp) {
    case DSK :
      *(*y+i) = d; break;
    case SPH :
      *(*y+i) = s; break;
    case TOT :
      *(*y+i) = t; break;
    }
    i++;
  }

  ReAlloc(*x,i); ReAlloc(*y,i); 

  fclose(e);

  return i;
}

/** Read data file for comparison (a ".num" file) **/

int read_dat(char *file, double **a, double **b, double **c, double **d,
	     double **e, double **f)
{
  FILE   *dat;
  char   line[MAXFCH];  
  int    i, n;
  double fg, bg;

  if ((dat = fopen(file,"r")) == NULL) { EROPN; exit(1); }

  Alloc(*a,MBLOCK); Alloc(*b,MBLOCK); Alloc(*c,MBLOCK);
  Alloc(*d,MBLOCK); Alloc(*e,MBLOCK); Alloc(*f,MBLOCK);
  i = 0; n = 1;
 
  while (fgets(line,MAXFCH,dat)) {
    if (i+1 == n*MBLOCK) {
      n++; 
      ReAlloc(*a,n*MBLOCK); ReAlloc(*b,n*MBLOCK); ReAlloc(*c,n*MBLOCK);
      ReAlloc(*d,n*MBLOCK); ReAlloc(*e,n*MBLOCK); ReAlloc(*f,n*MBLOCK);
    }
    if (line[0] != '#') {
      sscanf(line,"%lf %lf %lf %lf %lf %lf %lf",
	     *a+i, *b+i, *c+i, *d+i, *e+i, &fg, &bg);
      *(*f+i) = fg + bg;
      i++;
    }
  }
  
  ReAlloc(*a,i); ReAlloc(*b,i); ReAlloc(*c,i);
  ReAlloc(*d,i); ReAlloc(*e,i); ReAlloc(*f,i);
  
  fclose(dat);

  return i;
}
/*---------------------------------------------------------------------------*/
