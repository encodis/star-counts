/*
  Function : egm.h
  Purpose  : External Galaxy Model.
             Parameter header file.
  History  : Began: 6 October 1992. Last edit: 4 May 1995.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. This file is included in most of the major functions.  The 
                main purpose of this file is to define the structures used
		throughout the BSM code.
	     2. Initialization is done in the init_def(),  read_par(), 
	        init_lf(), init_col() and init_num() functions.
	     3. Also included are the function prototypes.
*/

/** Include files **/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

/** Definitions **/
#define BOOL  int              /* definition of boolean type                 */
#define TRUE  1
#define FALSE 0            
 
#define NUM_CMP 4              /* disk, thick disk, spheroid and total       */
#define DSK 0
#define THK 1
#define SPH 2
#define TOT 3

/** Absorption modes **/
#define NA    1                /* no absorption                              */
#define CS    2                /* cosec law                                  */
#define SA    3                /* Sandage absorption law                     */

/** Integration modes **/
#define NEAR     -1            /* integrate near side                        */
#define FAR       1            /* integrate far side                         */

/** Miscellaneous **/
#define PI       M_PI
#define M_3PI2   3.0*PI/2.0
#define M_2PI    2.0*PI
#define M_PI2    PI/2.0
#define SQD2ST   0.0003046174  /* converts sq. degrees to steradians         */
#define DEG2RAD  0.0174532922  /* converts degrees to radians                */
#define MAXFCH   81            /* max. length of filenames = 80 + 1 (null)   */
#define MAXSCH   11            /* max. length of strings = 10 + 1 (null)     */
#define MBLOCK   30            /* block size for reallocation                */

#define BD 7.66924944          /* bd : r^(1/4) law constant                  */
#define C1 4.6132E-2/2.0       /* c1 : r^(1/4) law constant                  */
#define C2 PI/(8.0*BD)         /* c2 : r^(1/4) law constant                  */

#define SEPCHARS1 ":@"         /* for parsing density norm. string           */
#define SEPCHARS2 " =\n"       /* for parsing keywords                       */
#define NULL_STR "\0"          /* null string                                */
#define NULL_CHR '\0'          /* null character                             */

#define DEFDEN2 "100.0:100.0"     /* default density for 2 component model   */
#define DEFDEN3 "10.0:10.0:10.0"  /* default density for 3 component model   */

/** Error Codes **/
enum error_codes {
  ERR_NONE,                 /* successful completion                         */
  ERR_USE1,                 /* usage error - basic help - parameters         */
  ERR_USE2,                 /* usage error - advanced help - keywords        */
  ERR_CARG,                 /* invalid command line option                   */
  ERR_PARM,                 /* invalid parameter                             */
  ERR_OPEN,                 /* file open error                               */
  ERR_READ,                 /* file read error                               */
  ERR_MALC,                 /* memory allocation error                       */
  ERR_MATH                  /* math error                                    */
};

/** Macro definitions **/
#define ALLOC(A,N,E1,E2) \
  if (( (A) = (double*) calloc((N),sizeof(double)) ) == NULL) \
  quit_egm(ERR_MALC,#E1,#E2)

#define ALLOC2(A,N,E1,E2) \
  if (( (A) = (double**) calloc((N),sizeof(double*)) ) == NULL)  \
  quit_egm(ERR_MALC,#E1,#E2)

#define REALLOC(A,N,E1,E2) \
  if (( (A) = (double*) realloc((A),(N)*sizeof(double)) ) == NULL) \
  quit_egm(ERR_MALC,#E1,#E2)

#define DEALLOC(A) ((void) free ((char *)A))

#define ISTRUE(A) (toupper( (A) ) == 'T' || toupper( (A) ) == 'Y')

/** Parameter structure **/
/** Contains model parameters not usually changed from run to run **/

typedef struct param {
  double ma_brt;            /* brightest app. mag. for calculation           */
  double ma_dim;            /* dimmest app. mag. for calculation             */
  double dm_app;            /* app. mag. bin size                            */
  double dm_abs;            /* abs. mag. integration step size               */
  double m_dim;             /* L.F. dim end cutoff                           */
  double m_bri;             /* L.F. bright end cutoff                        */
  double mbc;               /* bright app. mag. limit for colour distn.      */
  double mfc;               /* faint  app. mag. limit for colour distn.      */
  double dm_bin;            /* magnitude bin size for output                 */
  double c_fac;             /* Convergence factor for ending integration     */
  double s_col;             /* color error (in mags.) - see conv_color.c     */
  double d_col;             /* color interval for calc. before conv.         */
  double i_col;             /* color bin size for scaling color plot         */
  double max_col;           /* maximum colour                                */
  double min_col;           /* minimum colour                                */
  double dn[NUM_CMP-1];     /* density norm. relative to r0                  */
  double r0;                /* distance to galactic centre, in pc            */
  double l2;                /* "galactic" longitude of field in radians      */
  double b2;                /* "galactic" latitude  of field in radians      */
  int    amode;             /* absorption mode                               */
  double a[4];              /* array containing absorption parameters        */
  double abs;               /* an arbitrary value for extra absorption       */
  double dabs;              /* absorption looking through plane of disk      */
  double es;                /* spheroid axial ratio                          */
  double rek;               /* de Vaucouleurs radius for spher, in pc        */
  double rac;               /* abs. cutoff radius for spheroid               */
  double psl_d;             /* scale length in plane (pc)  (thin disk)       */
  double psl_t;             /* scale length in plane (pc)  (thick disk)      */
  double gsh_d;             /* giant scale height (pc)  (thin disk)          */
  double gsh_t;             /* giant scale height (pc)  (thick disk)         */
  double dr_d;              /* distance step size in r direction  (dsk)      */
  double dr_t;              /* distance step size in r direction  (thk)      */
  double dr_s;              /* distance step size in r direction  (sph)      */
  double r_min;             /* min. height for integration (=0, usually)     */
  double r_max_d;           /* max. height for integration disk              */
  double r_max_t;           /* max. height for integration thick disk        */
  double r_max_s;           /* max. distance for integration in spheroid     */
  double rpk;               /* dist. from plane of sky to field along l.o.s. */
} Param;

/** Model structure **/
/** Contains values usually input by user for a run **/
/** Also contains values unique to model calculated during a run **/

typedef struct model {
  char   pfile[MAXFCH];     /* name of parameter file                        */
  char   ofile[MAXFCH];     /* (optional) output file                        */
  char   libry[MAXFCH];     /* directory with .cm and .lf files              */
  double x0;                /* field position on major axis (in arcmin)      */
  double y0;                /* field position on minor axis (in arcmin)      */
  double omega;             /* area on sky in square degrees                 */
  double inc;               /* inclination in degrees                        */
  double dist;              /* distance to galaxy centre in parsecs          */
  char   den[MAXFCH];       /* input norm. radius string                     */
  double dnr[NUM_CMP-1];    /* Holds the input density normalisation info.   */
  double rho0;              /* rho0 for the input field                      */

  char   mag[MAXSCH];       /* Name of magnitude filter (e.g. V)             */
  char   col[MAXSCH];       /* Name of colour (e.g. B-V)                     */

  char   dmsfn[MAXFCH];     /* Disk main sequence filename                   */
  char   dgbfn[MAXFCH];     /* Disk giant branch filename (eg diskm67.cm)    */
  char   tgbfn[MAXFCH];     /* Thick Disk giant branch file (eg diskm67.cm)  */
  char   sgbfn[MAXFCH];     /* Spheroid giant branch filename (eg m13.cm &c) */

  char   fmsfn[MAXFCH];     /* Fraction of stars on Main Sequence filename   */

  char   dlffn[MAXFCH];     /* Disk L.F. filename                            */
  char   tlffn[MAXFCH];     /* Thick Disk L.F. filename                      */
  char   slffn[MAXFCH];     /* Spheroid L.F. filename                        */
} Model;

/** Luminosity function structure. **/

typedef struct lumfn {
  int    nl;                /* number of points in L.F. array                */
  double *d;                /* Disk L.F.                                     */
  double *t;                /* Thick disk L.F.                               */
  double *s;                /* Spheroid L.F.                                 */
} Lumfn;

/** Colour distribution structure. **/

typedef struct color {
  int    nc;                /* Number of points in color arrays              */
  double *ms;               /* Main Sequence colour distn.                   */
  double *dg;               /* Disk Giant colour distn.                      */
  double *tg;               /* Thick disk Giant colour distn.                */
  double *sg;               /* Spheroid Giant colour distn.                  */
} Color;

/** Star count structure **/

typedef struct numbr {
  int    nn;                /* number of points in num array                 */
  double **num;             /* Differential number count                     */
  double **sum;             /* Integral number counts                        */
  int    nf;                /* Number of points in fraction distn.           */
  double *fms;              /* Fraction of stars on Main Sequence            */
  int    nc;                /* Number of points in color distn.              */
  double **col;             /* Colour distn. (disk, spher, total) XBV        */
  double *tc;               /* Total ... TBV                                 */
  double *gb;               /* Giant Branch stuff XGB                        */
  double *cb;               /* Colour ... BVB                                */
  double *av;               /* Mean colours for DSK, SPH & TOT colour distn. */
  double fd;                /* "Star Fraction" for DSK                       */
  double ft;                /* "Star Fraction" for DSK                       */
  double fs;                /* "Star Fraction" for SPH                       */
} Numbr;

/** Optional command line arguments structure **/

typedef struct optar {
  BOOL v;                 /* Verbose output flag                             */
  BOOL thick;             /* Include thick disk                              */
  BOOL far_disk;          /* Integrate far side of galaxy for disk           */
  BOOL far_thik;          /* Integrate far side of galaxy for thick disk     */
  BOOL far_sphd;          /* Integrate far side of galaxy for spheroid       */
  BOOL doms;              /* Use the M-S CMD?                                */
} Optar;

/** Function prototypes **/

extern void   calc_col(BOOL, Param *, Color *, Numbr *);
extern void   calc_dsk(int, Param *, Lumfn *, Model *, Color *, Optar *,
		       Numbr *);
extern void   calc_nor(int, Param *, Model *, Lumfn *);
extern void   calc_num(BOOL, Numbr *, Param *);
extern void   calc_prj(int, Param *, Model *);
extern void   calc_spd(int, Param *, Lumfn *, Model *, Color *, Optar *,
		       Numbr *);
extern void   calc_thk(int, Param *, Lumfn *, Model *, Color *, Optar *,
		       Numbr *);
extern void   col_dist(int, double, double, double, double, double, double, 
		       Param *, Numbr *);
extern void   convlv(double *, int, double *, int);
extern int    find_idx(char *);
extern void   init_col(BOOL, BOOL, Param *, Model *, Color *);
extern void   init_def(Param *, Model *, Optar *);
extern void   init_fms(Param *, Model *, Numbr *);
extern void   init_lf(BOOL, Param *, Model *, Lumfn *);
extern void   init_num(BOOL, Param *, Model *, Numbr *);
extern double obscure(int, double, double, double *);
extern void   parsetok(BOOL, char *, Param *, Model *, Optar *);
extern void   read_dat(char *, char *, int *, double **, double **);
extern void   read_par(BOOL, Param *, Model *, Optar *);
extern void   scan_com(int, char **, Param *, Model *, Optar *);
extern void   spline(double *, double *, int, double, double, double *);
extern double splint(double *, double *, double *, int, double);
extern void   writ_col(BOOL, Param *, Model *, Numbr *, FILE *);
extern void   writ_hed(Optar *, Param *, Lumfn *, Model *, Numbr *, FILE *);
extern void   writ_num(BOOL, Param *, Model *, Numbr *, FILE *);
extern void   writ_res(Optar *, Param *, Lumfn *, Model *, Color *, Numbr *);
extern void   writ_vrb(BOOL, BOOL, Param *, Model *, Lumfn *, Color *, Numbr *,
		       FILE *);
extern int    quit_egm(int, char *, char *);

/*---------------------------------------------------------------------------*/
