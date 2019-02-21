# Makefile for utilities
CC     = gcc
CFLAGS = -g
LIBS   = -lm
BINDIR = /home/hodder/bin
OBJ1   = readdata.o spline.o splint.o
OBJ2   = trapzd.o qsimp.o
OBJ3   = gammafn.o
ALLEXE = mkalf mkcmd mkfms mkmlf mknlf mkspl mkxlf add2egm egmcmp map2ppm

# all
all:	$(ALLEXE)

mkalf:	mkalf.c
	$(CC) $(CFLAGS) -o mkalf mkalf.c $(LIBS)

mkcmd:	mkcmd.c $(OBJ1)
	$(CC) $(CFLAGS) -o mkcmd mkcmd.c $(OBJ1) $(LIBS)

mkfms:	mkfms.c
	$(CC) $(CFLAGS) -o mkfms mkfms.c $(LIBS)

mkmlf:	mkmlf.c $(OBJ1)
	$(CC) $(CFLAGS) -o mkmlf mkmlf.c $(OBJ1) $(LIBS)

mknlf:	mknlf.c $(OBJ1) $(OBJ2)
	$(CC) $(CFLAGS) -o mknlf mknlf.c $(OBJ1) $(OBJ2) $(LIBS)

mkspl:	mkspl.c $(OBJ1) 
	$(CC) $(CFLAGS) -o mkspl mkspl.c $(OBJ1) $(LIBS)

mkxlf:	mkxlf.c  
	$(CC) $(CFLAGS) -o mkxlf mkxlf.c $(LIBS)

add2egm: add2egm.c
	$(CC) $(CFLAGS) -o add2egm add2egm.c

egmcmp: egmcmp.c $(OBJ3)
	$(CC) $(CFLAGS) -o egmcmp egmcmp.c $(OBJ3) $(LIBS)

map2ppm: map2ppm.c
	$(CC) $(CFLAGS) -o map2ppm map2ppm.c $(LIBS)

.c.o:	$*.c gmutil.h
	$(CC) $(CFLAGS) -c $<

# clean
clean:
	rm -f *.o *~

install:
	mv $(ALLEXE) $(BINDIR)

zip:
	zip -u -9 GmuSrc12.zip *.c *.h Makefile gmu_guide.tex

print:
	cat gmutil.h   bvrijk.h   mkalf.c    mkcmd.c    mkfms.c   >  GMU-1.2
	cat mkmlf.c    mknlf.c    mkspl.c    mkxlf.c    qsimp.c   >> GMU-1.2
	cat readdata.c spline.c   splint.c   trapzd.c   gammafn.c >> GMU-1.2
	cat Makefile                                              >> GMU-1.2

	lwf -r -l -s7 -i0.3 -m -p-2 -l74 GMU-1.2 | lpr

manual:
	latex gmu_guide.tex
	dvips gmu_guide.dvi -o gmu_guide.ps
	rm -f *.aux *.dvi *.log
