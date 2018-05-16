
incs = -I../include

include ../Makefile.inc

opts = $(libs) $(defs) $(incs)

all: ../build/philosopher.a

clean:
	rm -f *.o 

../build/philosopher.a: PhilosopherCore.o TableState.o
	ld -r $^ -o $@

