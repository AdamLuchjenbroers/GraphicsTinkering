incs = -I./include

include Makefile.inc

.PHONY: all clean build/fw1.a build/math.a tests/fw1.o

opts = $(libs) $(defs) $(incs)

all: basic cube sb2 sb2_2 sb3_1 sb3_2 sb3_3 sb3_4 sb5_1

clean:
	rm -f build/* *.o
	cd ./fw1 && $(MAKE) clean

build/fw1.a: 
	cd fw1 && $(MAKE)

build/math.a: 
	cd math && $(MAKE)

tests/fw1.o:
	cd ./fw1 && $(MAKE) tests

tests: tests.cpp fw1/tests.h tests/fw1.a
	$(CC) $(incs) tests.cpp tests/fw1.o -o build/tests -lcppunit $(libs)

basic: basic.o build/fw1.a
	$(CC) $(incs) $^ -o build/$@ $(libs) 

cube: cube.o build/fw1.a
	$(CC) $(incs) $^ -o build/$@ $(libs) 
	 	
sb%: sb%.o build/fw1.a build/math.a SB6_BasicApp.o
	$(CC) $(incs) $^ -o build/$@ $(libs) 

