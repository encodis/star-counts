# Makefile for External Galaxy Model.
CC     = gcc
CFLAGS = -g
BINDIR = /home/hodder/bin
DEFS   = -DEGMLIB=\"/home/hodder/lib/bsm/\"
#DEFS  = -DEGMLIB=\"f:/lib/egm/\"
LIBS   = -lm
OFILES = extgal.o   init_def.o scan_com.o quit_egm.o read_par.o find_idx.o \
	 init_lf.o  read_dat.o init_col.o spline.o   splint.o   init_num.o \
	 init_fms.o calc_prj.o parsetok.o calc_nor.o calc_dsk.o obscure.o  \
	 col_dist.o calc_thk.o calc_spd.o calc_col.o convlv.o   calc_num.o \
	 writ_res.o writ_hed.o writ_num.o writ_col.o writ_vrb.o 
##
egm:		$(OFILES) egm.h
		$(CC) $(CFLAGS) -o egm $(OFILES) $(LIBS)

egm.exe:	$(OFILES)
		$(CC) $(CFLAGS) -o egm @ofiles.lst $(LIBS)
		coff2exe egm

extgal.o:	extgal.c egm.h
		$(CC) $(CFLAGS) -c extgal.c

init_def.o:	init_def.c egm.h
		$(CC) $(CFLAGS) $(DEFS) -c init_def.c

find_idx.o:	find_idx.c keyword.h egm.h
		$(CC) $(CFLAGS) -c find_idx.c

.c.o:		$*.c egm.h
		$(CC) $(CFLAGS) -c $<
##
clean:
	rm -f *.o

install:
	mv egm $(BINDIR)

zip:
	zip -u EgmSrc17.zip *.c *.h ofiles.lst README INSTALL MANIFEST \
	Makefile test.egm default.pm ./doc/*.tex ./doc/*.eps

taz:
	tar cvf - ./*.c ./*.h ./ofiles.lst ./README ./INSTALL ./MANIFEST \
	./Makefile ./test.egm ./default.pm ./doc/*.tex ./doc/*.eps | compress > EgmSrc17.tar.Z

tgz:
	tar cvf - ./*.c ./*.h ./ofiles.lst ./README ./INSTALL ./MANIFEST \
	./Makefile ./test.egm ./default.pm ./doc/*.tex ./doc/*.eps | gzip > EgmSrc17.tar.gz

print:
	cat egm.h      extgal.c   calc_col.c calc_dsk.c calc_nor.c >  EGM-1.7
	cat calc_num.c calc_prj.c calc_spd.c calc_thk.c col_dist.c >> EGM-1.7
	cat convlv.c   find_idx.c init_col.c init_def.c init_fms.c >> EGM-1.7
	cat init_lf.c  init_num.c keyword.h  obscure.c  parsetok.c >> EGM-1.7
	cat quit_egm.c read_dat.c read_par.c scan_com.c spline.c   >> EGM-1.7
	cat splint.c   writ_col.c writ_hed.c writ_num.c writ_res.c >> EGM-1.7
	cat writ_vrb.c Makefile                                    >> EGM-1.7
	
	lwf -r -l -s7 -i0.3 -m -p-2 -l74 EGM-1.7 | lpr

manual:
	(cd ./doc; latex egm_guide.tex; dvips egm_guide.dvi -o egm_guide.ps)
