#
# Makefile for the WE8003 device driver..
#
# Note! Dependencies are done automagically by 'make dep', which also
# removes any old dependencies. DON'T put your own dependencies here
# unless it's something special (ie not a .c file).
#
# Note 2! The CFLAGS definitions are now inherited from the
# parent makes..
#

SUBDIRS	=


.c.s:
	$(CC) $(CFLAGS) -S $<
.s.o:
	$(AS) -c -o $*.o $<
.c.o:
	$(CC) $(CFLAGS) -c $<

OBJS  = main.o


we8003.o:	$(OBJS)
		ld -r -o we8003.o $(OBJS)

clean:
		rm -f core *.o *.a tmp_make .depend
		for i in *.c;do rm -f `basename $$i .c`.s;done

dep:
	$(CPP) -M *.c > .depend
	@for i in $(SUBDIRS); do (cd $$i && echo $$i && $(MAKE) dep) || exit; done

dummy:
#
# include a dependency file if one exists
#
ifeq (.depend,$(wildcard .depend))
include .depend
endif
