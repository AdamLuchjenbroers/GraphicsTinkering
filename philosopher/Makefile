
incs = -I../include

include ../Makefile.inc

opts = $(libs) $(defs) $(incs)

all: ../build/philosopher.a

clean:
	rm -f *.o 

../build/philosopher.a: Philosopher.o PhilosopherCore.o TableState.o Chopstick.o NaiveTable.o
	ld -r $^ -o $@

