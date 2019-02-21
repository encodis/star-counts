# Makefile for Bahcall - Soneira Galaxy Model.
CC     = gcc
CFLAGS = -g -O
BINDIR = /home/hodder/bin
DEFS   = -DBSMLIB=\"/home/hodder/lib/bsm/\"
LIBS   = -lm
OFILES = bacson.o   init_def.o pars_com.o quit_bsm.o read_par.o parsetok.o \
	 find_idx.o init_lum.o read_dat.o init_col.o spline.o   splint.o   \
	 init_num.o init_fms.o calc_dsk.o obscure.o  col_dist.o calc_thk.o \
	 calc_sph.o calc_col.o convlv.o   calc_num.o writ_res.o writ_hed.o \
	 writ_num.o writ_col.o writ_zed.o writ_vrb.o
##
bsm:		$(OFILES) bsm.h
		$(CC) $(CFLAGS) -o bsm $(OFILES) $(LIBS)

bsm.exe:	$(OFILES) bsm.h
		$(CC) $(CFLAGS) -o bsm @ofiles.lst $(LIBS)
		coff2exe bsm

bacson.o:	bacson.c bsm.h
		$(CC) $(CFLAGS) -c bacson.c

init_def.o:	init_def.c bsm.h
		$(CC) $(CFLAGS) $(DEFS) -c init_def.c

parsetok.o:	parsetok.c keyword.h bsm.h
		$(CC) $(CFLAGS) -c parsetok.c

find_idx.o:	find_idx.c keyword.h bsm.h
		$(CC) $(CFLAGS) -c find_idx.c

.c.o:		$*.c bsm.h
		$(CC) $(CFLAGS) -c $<
##
clean:
	rm -f *.o

install:
	mv bsm $(BINDIR)

zip:
	zip -u BsmSrc32.zip *.c *.h ofiles.lst Makefile bsm.sm test.* ./doc/*.tex ./doc/*.eps

print:
	cat bsm.h      bacson.c   calc_col.c calc_dsk.c calc_num.c >  BSM-3.2
	cat calc_sph.c calc_thk.c col_dist.c convlv.c   find_idx.c >> BSM-3.2
	cat init_col.c init_def.c init_fms.c init_lum.c init_num.c >> BSM-3.2
	cat keyword.h  obscure.c  pars_com.c parsetok.c quit_bsm.c >> BSM-3.2
	cat read_dat.c read_par.c spline.c   splint.c   writ_col.c >> BSM-3.2
	cat writ_hed.c writ_num.c writ_res.c writ_vrb.c writ_zed.c >> BSM-3.2
	cat Makefile                                               >> BSM-3.2
	
	lwf -r -l -s7 -i0.3 -m -p-2 -l74 BSM-3.2 | lpr

manual:
	(cd ./doc; latex bsm_guide.tex;	dvips bsm_guide.dvi -o bsm_guide.ps)
