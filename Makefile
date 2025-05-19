# Makefile  obligatorio-2
#

ARCHIVOS_ENTREGAR= obligatorio2.c bits.c bits.h libHuf.c libHuf.h Makefile

all : libbits.a libHuf.a obligatorio2 entrega

COPT = -I./ -Wall -ansi -ggdb
LDFLAGS = -L ./
LDLIBS = -lHuf -lbits -lm

obligatorio2: obligatorio2.o libbits.a libHuf.a
	cc $(COPT) -o $@ obligatorio2.o $(LDFLAGS) $(LDLIBS)

.c.o:
	cc $(COPT) -c $<

bits.o: bits.c bits.h

libbits.a: bits.o
	ar rcs $@ $<

libHuf.a: libHuf.o
	ar rcs $@ $<

clean:
	rm - rf *.o obligatorio2 libbits.a libHuf.a

entrega: obligatorio2 bits.o  libHuf.o
	zip  alberto_DANIEL_SANCHEZ_LATRONICO.zip   $(ARCHIVOS_ENTREGAR)
	touch entrega

