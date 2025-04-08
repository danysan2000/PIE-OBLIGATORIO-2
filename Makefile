# Makefile  obligatorio-2
#


all : libbits . a libHuf . a obligatorio2

COPT = - Wall - ansi - ggdb
LDFLAGS = - L ./
LDLIBS = - lHuf - lbits - lm

obligatorio2 : obligatorio2 . o
	cc $ ( COPT ) -o $@ obligatorio2 . o $ ( LDFLAGS ) $ ( LDLIBS )

. c . o :
	cc $ ( COPT ) -c $ <

libbits . a : bits . o
	ar rcs $@ $ <

libHuf . a : libHuf . o
	ar rcs $@ $ <

clean :
	rm - rf *. o obligatorio2 libbits . a libHuf . a

