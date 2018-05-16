
incs = -I../include

include ../Makefile.inc

opts = $(libs) $(defs) $(incs)

all: ../build/philosopher.a

clean:
	rm -f *.o 

../build/philosopher.a: PhilosopherCore.o
	ld -r $^ -o $@

