incs = -I../include

include ../Makefile.inc

opts = $(libs) $(defs) $(incs)

all: ../build/math.a


clean:
	rm -f *.o tests/*.o 

../build/math.a: Vector3H.o Matrix4.o
	ld -r $^ -o $@
	
tests: ../tests/math.a

tests/Vector3HTests.o: Vector3H.o
tests/Matrix4Tests.o: Vector3H.o Matrix4.o

../tests/math.a: tests/Vector3HTests.o tests/Matrix4Tests.o ../build/math.a
	ld -r $^ -o $@
