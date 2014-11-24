
include Makefile.inc
incs = -I./include

opts = $(libs) $(defs) $(incs)

all: system basic cube sb2

clean:
	rm -f build/* *.o
	cd ./system && $(MAKE) clean
	
system:
	cd ./system && $(MAKE)

#Hack to fix compilation logic
system/sdl2display.o: system/sdl2/sdl2display.cpp system/sdl2/sdl2display.h
	cd ./system && $(MAKE) sdl2display.o
	
utilities/shader.o: utilities/shader.cpp utilities shader.h
	$(CC) $(incs) utilities/shader.cpp -o utilities/shader.o $(libs)

basic: basic.o system/sdl2display.o
	$(CC) $(incs) basic.o system/sdl2display.o -o build/basic $(libs) 

basic.o:
	$(CC) $(incs) basic.cpp -c -o basic.o

cube: basic.o system/sdl2display.o
	$(CC) $(incs) cube.o system/sdl2display.o -o build/cube $(libs)
	 	
cube.o: cube.cpp
	$(CC) $(incs) cube.cpp -c -o cube.o
	
sb2.o : sb2.cpp
	$(CC) $(incs) sb2.cpp -c -o sb2.o

sb2: sb2.o utilities/shader.o system/sdl2display.o
	$(CC) $(incs) sb2.o utilities/shader.o system/sdl2display.o -o build/cube $(libs)


