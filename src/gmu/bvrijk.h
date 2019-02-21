/*
   File    : bvrijk.h
   Purpose : Header file for Galaxy Model utilities.
   History : Began: 18 May 1994. Last edit: 27 June 1994.
   Author  : P.J.C.Hodder (hodder@geop.ubc.ca)
   Comments: 1. Formula for LF data is
                 phi(M) =         ns * 10^(b(M-Ms))           Mb <= M <= Mc
                           -----------------------------
			   (1 + 10^(-(a-b)d(M-Ms))^(1/d)
		 phi(M) = phi(Mc)                             Mc <= M <= Ma
		 phi(m) = 0                                   M <= Mb, M >= Md
		where the first 9 elements of Data[X][] are:
		 ns, ms, a, b, 1/d, Mb, Mc, Md, N(Mc)
             2. Formula for FMS data is
	         f(M) =  C * e^(a(M+b)^g)   M <  Ma
		 f(M) =  1                  M >= Ma
		where the last five elements of Data[X][] are:
		 C, a, b, g, Ma
*/

enum Filt {
  B = 0, V, R, I, J, K, NF
};

static double Data[6][14] = {
  { 2.55e-3, 2.2, 0.6, 0.05, 2.3, -6.0, 15.0, 18.0, 1.0, 
      0.53, 2.4e-31, 75.0, 16.0, 4.6 }, 
  { 4.03e-3, 1.28, 0.74, 0.04, 3.40, -6.0, 15.0, 16.0, 0.01414, 
      0.44, 1.5e-4, 8.0, 3.5, 3.7 },
  { 4.80e-3, 1.40, 0.74, 0.045, 3.0, -6.0, 14.0, 13.0, 1.0, 
      0.31, 6.5e-4, 7.5, 3.2, 2.9 },
  { 1.75e-2, 0.85, 0.81, 0.01, 5.20, -6.0, 14.0, 11.0, 1.0, 
      0.08, 0.37, 4.4, 1.0, 2.4 },
  { 2.50e-2, 0.6, 0.8, 0.01, 5.65, -5.0, 11.0, 10.0, 1.0, 
      0.0069, 2.0, 4.0, 0.5, 2.2 },
  { 2.90e-2, 2.0, 0.625, 0.01, 4.0, -5.0, 9.0, 9.0, 1.0,
      0.0047, 2.5, 3.0, 0.5, 1.6 }
};

/*---------------------------------------------------------------------------*/
