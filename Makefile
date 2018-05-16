incs = -I./include

include Makefile.inc

.PHONY: all clean build/fw1.a build/math.a tests/fw1.a tests/math.a

opts = $(libs) $(defs) $(incs)

all: cube_demos heightmap_demos superbible6_demos misc_demos 
all: utilities threading

cube_demos: cube texcube litcube speccube bumpcube heightcube
heightmap_demos: heightmap heighttex heightspec
superbible6_demos: basic sb2 sb2_2 sb3_1 sb3_1ff sb3_2 sb3_3 sb3_4 sb5_1 sb5_1-spin
misc_demos: fakesphere pyramid
threading: philosopher

utilities: height2normal stlviewer

clean:
	rm -f build/* *.o primitives/*.o
	cd ./fw1 && $(MAKE) clean
	cd ./math && $(MAKE) clean

doc:
	doxygen doxygen.cfg

build/fw1.a: fw1/* 
	cd fw1 && $(MAKE)

build/math.a: 
	cd math && $(MAKE)

build/philosopher.a: philosopher/* 
	cd philosopher && ${MAKE}

tests/fw1.a:
	cd ./fw1 && $(MAKE) tests
	
tests/math.a:
	cd ./math && $(MAKE) tests

test: tests.cpp tests/fw1.a tests/math.a
	$(CC) $(incs) $^ -o $@ -lcppunit $(libs)
	./test

basic: basic.o build/fw1.a
	$(CC) $(incs) $^ -o build/$@ $(libs) 

%ube: %ube.o build/fw1.a build/math.a SB6_BasicApp.o CubeApp.o primitives/Cube.o
	$(CC) $(incs) $^ -o build/$@ $(libs) 
	 	
sb%: sb%.o build/fw1.a build/math.a SB6_BasicApp.o
	$(CC) $(incs) $^ -o build/$@ $(libs) 

%viewer: %viewer.o build/fw1.a build/math.a SB6_BasicApp.o
	$(CC) $(incs) $^ -o build/$@ $(libs) 
	 	
pyramid: pyramid.o build/fw1.a build/math.a SB6_BasicApp.o primitives/Pyramid.o
	$(CC) $(incs) $^ -o build/$@ $(libs) 
	 	
fakesphere: fakesphere.o build/fw1.a build/math.a SB6_BasicApp.o primitives/Pyramid.o
	$(CC) $(incs) $^ -o build/$@ $(libs) 
	 	
height%: height%.o build/fw1.a build/math.a SB6_BasicApp.o
	$(CC) $(incs) $^ -o build/$@ $(libs) 
	 	
bumptest: bumptest.o build/fw1.a build/math.a SB6_BasicApp.o 
	$(CC) $(incs) $^ -o build/$@ $(libs) 

philosopher: philosopher.o build/philosopher.a build/fw1.a build/math.a
	$(CC) $(incs) $^ -o build/$@ $(libs) 

