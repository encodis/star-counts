/*
   Program : map2ppm
   Function: External Galaxy Model.
             Make a ppm file from 2 or 3 egm maps (as produced by egm-map etc).
   History : Began: 17 May 1995.
   Author  : P.J.C.Hodder (hodder@geop.ubc.ca)
   Usage   : map2ppm [-log] disk_map [thick_map] sphd_map
   Comments: 1. A bit of a hack really...
             2. disk is red, thick disk is green, spheroid is blue
	     3. max grey levels is 256
*/   

#include "gmutil.h"

#define USAGE fprintf(stderr,"Usage: map2ppm [-l|-n] x y max_val max_gry disk_map [thick_map] sphd_map\n");

int read_dat(char *file, double **x);

/** MAIN **/
void main(int argc, char **argv)
{
  int     a = 0, l = FALSE, k = FALSE;
  double  max_val;
  int     nx, ny, max_gry;
  int     d_num,  t_num,  s_num;
  double *d_dat, *t_dat, *s_dat;
  int     i, d, t, s;

  if (argc > 1 && !strcmp(argv[1],"-l")) {
    l = TRUE; a = 1; argc--;
  } else if (argc > 1 && !strcmp(argv[1],"-n")) {
    l = FALSE; a = 1; argc--;
  }

  if (argc < 7) { USAGE; exit(1); }
  if (argc == 8) k = TRUE;

  nx = atoi(argv[a+1]);
  ny = atoi(argv[a+2]);
  max_val = atof(argv[a+3]);
  max_gry = atoi(argv[a+4]);

  /* read in data from 2 or 3 files */
  d_num = read_dat(argv[a+5], &d_dat);
  if (k) {
    t_num = read_dat(argv[a+6], &t_dat);
    s_num = read_dat(argv[a+7], &s_dat);

    if (d_num != t_num || d_num != s_num || t_num != s_num) {
      fprintf(stderr,"Different number of points in files!\n"); exit(1);
    }

  } else {
    s_num = read_dat(argv[a+6], &s_dat);

    if (d_num != s_num) {
      fprintf(stderr,"Different number of points in files!\n"); exit(1);
    }

  }

  /* scale data and print ppm file */
  printf("P3 \n%d %d \n%d \n", nx, ny, max_gry);

  for (i = 0; i < d_num; i++) {
    if (l) d_dat[i] = (d_dat[i] <= 1.0) ? 0.0 : log10(d_dat[i]);
    d_dat[i] = d_dat[i] * (max_gry / max_val);
    d = ( (int) d_dat[i] < max_gry) ? (int) d_dat[i] : max_gry;

    if (k) {
      if (l) t_dat[i] = (t_dat[i] <= 1.0) ? 0.0 : log10(t_dat[i]);
      t_dat[i] = t_dat[i] * (max_gry / max_val);
      t = ( (int) t_dat[i] < max_gry) ? (int) t_dat[i] : max_gry;
    } else {
      t = 0;
    }

    if (l) s_dat[i] = (s_dat[i] <= 1.0) ? 0.0 : log10(s_dat[i]);
    s_dat[i] = s_dat[i] * (max_gry / max_val);
    s = ( (int) s_dat[i] < max_gry) ? (int) s_dat[i] : max_gry;

    printf("%d %d %d\n", d, t, s);
  }
}

/** FUNCTIONS **/

/** read third column of data file **/

#define LENGTH 129
#define MBLOCK 20

int read_dat(char *file, double **x)
{
  FILE *inp;
  int  i,j;
  char line[LENGTH];

  if (strlen(file) != 0) {
    inp = fopen(file,"r");
  } else {
    inp = stdin;
  }

  if (inp != NULL) {
    /** allocate basic amount of memory **/
    Alloc(*x, MBLOCK);
    i = 0; j = 1;

    /** read file until end **/
    while (fgets(line,LENGTH,inp)) {
      if (i+1 == j*MBLOCK) {
	j++;
	ReAlloc(*x, j*MBLOCK);
      }
      if (line[0] != '#') {
	sscanf(line,"%*lf %*lf %lf",*x+i);
	i++;
      }
    }
    
    /** now trim array sizes **/
    ReAlloc(*x, i); 
    fclose(inp);
  } else {
    EROPN; exit(1);
  } 

  return i;
}
