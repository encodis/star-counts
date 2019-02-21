/*
   File    : util.h
   Purpose : Header file for Galaxy Model utilities.
   History : Began: 29 April 1994.
   Author  : P.J.C.Hodder (hodder@geop.ubc.ca)
   Comments: 1.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define TRUE  1
#define FALSE 0

#define EROPN fprintf(stderr,"Could not open file.\n")
#define ERFIL fprintf(stderr,"File type error.\n")
#define ERMEM fprintf(stderr,"Memory allocation error.\n")
#define ERMAT fprintf(stderr,"Math error.\n")
#define ERMTH fprintf(stderr,"Methodology error.\n")

#define Alloc(A,N) \
  if (( (A) = (double *) calloc((N),sizeof(double)) ) == NULL) \
  { ERMEM; exit(1); }
#define ReAlloc(A,N) \
  if (( (A) = (double *) realloc((A),(N)*sizeof(double)) ) == NULL) \
  { ERMEM; exit(1); }
#define DeAlloc(A) ((void) free ((char *)A))

int    readdata(char *, double **, double **);
void   spline(double *, double *, int, double, double, double *);
double splint(double *, double *, double *, int, double);
double trapzd(double *, double *, double *, int, double, double, int);
double qsimp(double *, double *, double *, int, double, double);
double gammq(double, double);
void   gcf(double *, double, double, double *);
void   gser(double *, double, double, double *);
double gammln(double);

/*---------------------------------------------------------------------------*/
