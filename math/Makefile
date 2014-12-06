incs = -I../include

include ../Makefile.inc

opts = $(libs) $(defs) $(incs)

all: ../build/math.a


clean:
	rm -f *.o 

../build/math.a: Vector4.o 
	ld -r $^ -o $@
