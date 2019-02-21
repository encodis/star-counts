# Makefile for Bahcall - Soneira Galaxy Model.
CC     = gcc
CFLAGS = -g 
BINDIR = /home/hodder/bin
DEFS   = -DBSMLIB=\"/home/hodder/lib/bsm/\"
LIBS   = -lm
OFILES = mubsm.o    init_def.o pars_com.o quit_bsm.o read_par.o parsetok.o \
	 find_idx.o init_lum.o read_dat.o init_col.o spline.o   splint.o   \
	 init_num.o init_fms.o calc_dsk.o obscure.o  col_dist.o calc_thk.o \
	 calc_sph.o calc_col.o convlv.o   calc_num.o writ_res.o writ_hed.o \
	 writ_num.o writ_col.o writ_vrb.o solve4r.o  zbrent.o
#
mubsm:		$(OFILES) mubsm.h
		$(CC) $(CFLAGS) -o mubsm $(OFILES) $(LIBS)

mubsm.exe:	$(OFILES) mubsm.h
		$(CC) $(CFLAGS) -o mubsm @ofiles.lst $(LIBS)
		aout2exe mubsm

mubsm.o:	mubsm.c mubsm.h
		$(CC) $(CFLAGS) -c mubsm.c

init_def.o:	init_def.c mubsm.h
		$(CC) $(CFLAGS) $(DEFS) -c init_def.c

parsetok.o:	parsetok.c keyword.h mubsm.h
		$(CC) $(CFLAGS) -c parsetok.c

find_idx.o:	find_idx.c keyword.h mubsm.h
		$(CC) $(CFLAGS) -c find_idx.c

.c.o:		$*.c mubsm.h
		$(CC) $(CFLAGS) -c $<
##
clean:
	rm -f *.o

install:
	mv mubsm $(BINDIR)

zip:
	zip MuBSrc10.zip *.c *.h ofiles.lst Makefile *test

