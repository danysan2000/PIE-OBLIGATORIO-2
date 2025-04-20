# Makefile  obligatorio-2
#

#.PHONY: sync

all : libbits.a libHuf.a obligatorio2

COPT = -I./ -Wall -ansi -ggdb
LDFLAGS = -L ./
LDLIBS = -lHuf -lbits -lm

obligatorio2: obligatorio2.o
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

#sync: 

bits.c: ../OBLIGATORIO_1/bits.c
	if [ -f "../OBLIGATORIO_1/bits.c" ]; then \
		cp ../OBLIGATORIO_1/bits.c bits.c; \
		echo "bits.c -> Actualizado desde OBLIGATORIO_1" \
	else \
		echo "ALERTA: ../OBLIGATORIO_1/bits.c  no existe."; \
	fi

bits.h: ../OBLIGATORIO_1/bits.h
	if [ -f ../OBLIGATORIO_1/bits.c  ]; then \
	cp ../OBLIGATORIO_1/bits.h \
	@echo "bits.h -> Actualizado desde OBLIGATORIO_1" \
	fi


