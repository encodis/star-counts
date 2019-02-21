/*
  Function : bsm.h
  Purpose  : Bahcall - Soneira Galaxy Model.
             Parameter header file.
  History  : Began: 23 May 1991. Last edit: 13 July 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. This file is included in most of the major functions. The main
                purpose of this file is to define the structures used in the 
		rest of the BSM code.
	     2. Initialization is done in the init_def(), read_par(), 
	        init_lum(), init_col() and init_num() functions.
	     3. Also included are the function prototypes.
*/

/** Include files **/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

/** Definitions **/
#define REAL  double      /* definition of floating point type              */
#define BOOL  int         /* definition of boolean type                     */
#define TRUE  1
#define FALSE 0            
 
#define NUM_CMP 4         /* disk, thick disk, spheroid and total           */
#define DSK 0
#define THK 1
#define SPH 2
#define TOT 3

/** Absorption modes **/
#define NA    1           /* no absorption                                  */
#define CS    2           /* cosec law                                      */
#define SA    3           /* Sandage absorption law                         */

/** Miscellaneous **/
#define PI       M_PI
#define SQD2ST   0.0003046174  /* converts sq. degrees to steradians        */
#define MAXFCH   81            /* max. length of filenames = 80 + 1 (null)  */
#define MAXSCH   11            /* max. length of strings = 10 + 1 (null)    */
#define MBLOCK   30            /* block size for reallocation               */
#define NULL_STR "\0"          /* null string                               */
#define NULL_CHR '\0'          /* null character                            */
#define SEPCHARS1 " =\n"       /* for parsing parameter file                */
#define SEPCHARS2 " :\n"       /* for parsing density normalization         */

/** Error Codes **/
#define ERR_NONE 0        /* successful completion                          */
#define ERR_USE1 1        /* usage error - basic help - parameters          */
#define ERR_USE2 2        /* usage error - advanced help - keywords         */
#define ERR_CARG 3        /* invalid command line option                    */
#define ERR_PARM 4        /* invalid parameter                              */
#define ERR_OPEN 5        /* file open error                                */
#define ERR_READ 6        /* file read error                                */
#define ERR_MALC 7        /* memory allocation error                        */
#define ERR_MATH 8        /* math error                                     */

/** Macro definitions **/
#define ALLOC(A,N,E1,E2) \
       if (( (A) = (REAL *) calloc((N),sizeof(REAL)) ) == NULL)  \
       quit_bsm(ERR_MALC,#E1,#E2)

#define ALLOC2(A,N,E1,E2) \
       if (( (A) = (REAL **) calloc((N),sizeof(REAL)) ) == NULL)  \
       quit_bsm(ERR_MALC,#E1,#E2)

#define REALLOC(A,N,E1,E2) \
       if (( (A) = (REAL *) realloc((A),(N)*sizeof(REAL)) ) == NULL) \
       quit_bsm(ERR_MALC,#E1,#E2)

#define DEALLOC(A) \
       ((void) free ((char *)A))

/** Parameter structure **/
typedef struct param {
  REAL ma_brt;            /* brightest app. mag. for calculation            */
  REAL ma_dim;            /* dimmest app. mag. for calculation              */
  REAL dm_app;            /* app. mag. bin size                             */
  REAL dm_abs;            /* abs. mag. integration step size                */
  REAL m_dim;             /* L.F. dim end cutoff                            */
  REAL m_brd;             /* L.F. (disk) bright end cutoff                  */
  REAL m_brs;             /* L.F. (spheroid) bright end cutoff              */
  REAL mbc;               /* bright app. mag. limit for colour distn.       */
  REAL mfc;               /* faint  app. mag. limit for colour distn.       */
  REAL mturn;             /* turn-off mag. for sph MS/GB distn.             */
  REAL dm_bin;            /* magnitude bin size for output                  */
  REAL c_fac;             /* Convergence factor for ending integration      */
  REAL s_col;             /* color error (in mags.) - see conv_color.c      */
  REAL d_col;             /* color interval for calc. before conv.          */
  REAL i_col;             /* color bin size for scaling color plot          */
  REAL max_col;           /* maximum colour                                 */
  REAL min_col;           /* minimum colour                                 */
  REAL dn[NUM_CMP-1];     /* stellar density normalization                  */
  REAL r0;                /* distance to galactic centre, in pc             */
  int  amode;             /* absorption mode                                */
  REAL abs;               /* any arbitrary absorption                       */
  REAL a[4];              /* array containing absorption parameters         */
  REAL es;                /* spheroid axial ratio                           */
  REAL rek;               /* de Vaucouleurs radius for spher, in pc         */
  REAL psl_d;             /* scale length in plane (pc)  (thin disk)        */
  REAL psl_t;             /* scale length in plane (pc)  (thick disk)       */
  REAL gsh_d;             /* giant scale heigth (pc)  (thin disk)           */
  REAL gsh_t;             /* giant scale heigth (pc)  (thick disk)          */
  REAL dr;                /* distance step size in r direction              */
  REAL r_min;             /* min. height for integration (=0, usually)      */
  REAL r_max_d;           /* max. height for integration if b=90 in disk    */
  REAL r_max_t;           /* max. height for integration if b=90 in thick d */
  REAL r_max_s;           /* max. distance for integration in spheroid      */
} Param;

/** Model structure **/
typedef struct model {
  char pfile[MAXFCH];     /* name of parameter file                         */
  char libry[MAXFCH];     /* directory with .cm and .lf files               */
  char ofile[MAXFCH];     /* output file name                               */
  REAL l2;                /* galactic longitude of field                    */
  REAL b2;                /* galactic latitude  of field                    */
  REAL omega;             /* area on sky in square degrees                  */
  char mag[MAXSCH];       /* Name of magnitude filter (e.g. V)              */
  char col[MAXSCH];       /* Name of colour (e.g. B-V)                      */

  char dmsfn[MAXFCH];     /* Disk Main Sequence (dwarf) filename            */ 
  char dgbfn[MAXFCH];     /* Disk giant branch filename (eg diskm67.cm)     */
  char dlffn[MAXFCH];     /* Disk L.F. filename                             */
  REAL dsh_f_h;           /* disk scale height - faint stars (max height)   */
  REAL dsh_f_m;           /* disk scale height - faint stars (max mag.)     */
  REAL dsh_b_h;           /* disk scale height - bright *s (min height)     */
  REAL dsh_b_m;           /* disk scale height - bright *s (min mag.)       */

  char tmsfn[MAXFCH];     /* Thick Disk Main Sequence (dwarf) filename      */
  char tgbfn[MAXFCH];     /* Thick Disk giant branch file (eg diskm67.cm)   */
  char tlffn[MAXFCH];     /* Thick Disk L.F. filename                       */
  REAL tsh_f_h;           /* thick disk sh - faint stars (max height)       */
  REAL tsh_f_m;           /* thick disk sh - faint stars (max mag.)         */
  REAL tsh_b_h;           /* thick disk sh - bright *s (min height)         */
  REAL tsh_b_m;           /* thick disk sh - bright *s (min mag.)           */

  char smsfn[MAXFCH];     /* Spheroid Main Sequence (dwarf) filename        */ 
  char sgbfn[MAXFCH];     /* Spheroid giant branch filename (eg m13.cm etc.)*/
  char slffn[MAXFCH];     /* Spheroid L.F. filename                         */

  char fmsfn[MAXFCH];     /* Fraction of stars on ms filename               */
} Model;

/** Luminosity function structure. **/
typedef struct lumfn {
  int  nl;                /* number of points in L.F. array                 */
  REAL *d;                /* Disk L.F.                                      */
  REAL *t;                /* Thick disk L.F.                                */
  REAL *s;                /* Spheroid L.F.                                  */
} Lumfn;

/** Colour distribution structure. **/
typedef struct color {
  int  nc;                /* Number of points in color arrays               */
  REAL *dms;              /* Disk Main Sequence colour distn.               */
  REAL *dg;               /* Disk Giant colour distn.                       */
  REAL *tms;              /* Thick Disk Main Sequence colour distn.         */
  REAL *tg;               /* Thick disk Giant colour distn.                 */
  REAL *sms;              /* Spheroid Main Sequence colour distn.           */
  REAL *sg;               /* Spheroid Giant colour distn.                   */
  int  ng;                /* Number of points in conv.                      */
  REAL *gcf;              /* Gaussian colour distn. for convolution         */
} Color;

/** Star count structure **/
typedef struct numbr {
  int  nn;                /* number of points in num array                  */
  REAL **num;             /* Differential number count                      */
  REAL **sum;             /* Integral number counts                         */
  int  nf;                /* Number of points in fraction distn.            */
  REAL *fms;              /* Fraction of stars on main sequence             */
  int  nc;                /* Number of points in color distn.               */
  REAL **col;             /* Colour distn. (disk, spher, total) XBV         */
  REAL *tc;               /* Total ... TBV                                  */
  REAL *gb;               /* Giant Branch stuff XGB                         */
  REAL *cb;               /* Colour ... BVB                                 */
  REAL *av;               /* Mean colours for DSK, SPH & TOT colour distn.  */
  REAL fd;                /* "Star Fraction" for DSK                        */
  REAL ft;                /* "Star Fraction" for DSK                        */
  REAL fs;                /* "Star Fraction" for SPH                        */
  int  nzd;               /* number of points in Z dist. array for disk     */
  REAL *zdn;              /* Z distribution of disk stars                   */
  REAL *zdr;              /* distance steps for disk stars                  */
  int  nzt;               /* number of points in Z dist. for thick disk     */
  REAL *ztn;              /* Z distribution of thick disk stars             */
  REAL *ztr;              /* distance steps for thick disk stars            */
  int  nzs;               /* number of points in Z dist. array for spheroid */
  REAL *zsn;              /* Z distribution of spheroid stars               */
  REAL *zsr;              /* distance steps of spheroid stars               */
} Numbr;

/** Optional command line arguments structure **/
typedef struct optar {
  BOOL v;                 /* Verbose output flag                            */
  BOOL z;                 /* Z distribution flag                            */
  BOOL thick;             /* Include thick disk                             */
} Optar;

/** Function prototypes **/
extern void calc_col(BOOL, Param *, Color *, Numbr *);
extern void calc_dsk(BOOL, Param *, Lumfn *, Model *, Color *, Numbr *);
extern void calc_num(BOOL, Param *, Numbr *);
extern void calc_sph(BOOL, Param *, Lumfn *, Model *, Color *, Numbr *);
extern void calc_thk(BOOL, Param *, Lumfn *, Model *, Color *, Numbr *);
extern void col_dist(int, REAL, REAL, REAL, REAL, REAL, REAL, 
		     Param *, Numbr *);
extern void convlv(REAL *, int, REAL *, int);
extern int  find_idx(char *);
extern void init_col(BOOL, Param *, Model *, Color *);
extern void init_def(Param *, Model *, Optar *);
extern void init_fms(Param *, Model *, Numbr *);
extern void init_lum(BOOL, Param *, Model *, Lumfn *);
extern void init_num(BOOL, Param *, Model *, Numbr *);
extern REAL obscure(int, REAL, REAL, REAL *);
extern void pars_com(int, char **, Param *, Model *, Optar *);
extern void parsetok(BOOL, char *, Param *, Model *);
extern int  quit_bsm(int, char *, char *);
extern void read_dat(char *, char *, int *, REAL **, REAL **);
extern void read_par(BOOL, Param *, Model *);
extern void spline(REAL *, REAL *, int, REAL, REAL, REAL *);
extern REAL splint(REAL *, REAL *, REAL *, int, REAL);
extern void writ_col(BOOL, Param *, Model *, Numbr *, FILE *);
extern void writ_hed(Optar *, Param *, Model *, Numbr *, FILE *);
extern void writ_num(BOOL, Param *, Model *, Numbr *, FILE *);
extern void writ_res(Optar *, Param *, Lumfn *, Model *, Color *, Numbr *);
extern void writ_vrb(BOOL, Param *, Model *, Lumfn *, Color *, Numbr *,
		     FILE *);
extern void writ_zed(BOOL, Numbr *, FILE *);
/*---------------------------------------------------------------------------*/

