
incs = -I../include

include ../Makefile.inc

opts = $(libs) $(defs) $(incs)

all: ../build/philosopher.a ../build/philosopher-naive.a ../build/philosopher-trywait.a

clean:
	rm -f *.o 

../build/philosopher.a: PhilosopherRef.o Philosopher.o PhilosopherCore.o TableState.o Chopstick.o
	ld -r $^ -o $@

../build/philosopher-naive.a: NaiveTable.o NaiveCore.o NaivePhilosopher.o
	ld -r $^ -o $@

../build/philosopher-trywait.a: TryWaitTable.o TryWaitCore.o TryWaitPhilosopher.o
	ld -r $^ -o $@
