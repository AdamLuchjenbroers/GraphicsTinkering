
include Makefile.inc
incs = -I./include

opts = $(libs) $(defs) $(incs)

all: system basic cube sb2 sb2_2 sb3_1 sb3_2 sb3_3

clean:
	rm -f build/* *.o
	cd ./system && $(MAKE) clean
	
system:
	cd ./system && $(MAKE)

build/fw1.o:
	cd ./fw1 && $(MAKE)

#Hack to fix compilation logic
system/sdl2display.o: system/sdl2/sdl2display.cpp system/sdl2/sdl2display.h
	cd ./system && $(MAKE) sdl2display.o

basic: basic.o build/fw1.o
	$(CC) $(incs) basic.o build/fw1.o -o build/basic $(libs) 

basic.o:
	$(CC) $(incs) basic.cpp -c -o basic.o

cube: cube.o build/fw1.o
	$(CC) $(incs) cube.o build/fw1.o -o build/cube $(libs)
	 	
cube.o: cube.cpp
	$(CC) $(incs) cube.cpp -c -o cube.o
	
sb2.o : sb2.cpp
	$(CC) $(incs) sb2.cpp -c -o sb2.o

sb2: sb2.o build/fw1.o
	$(CC) $(incs) sb2.o build/fw1.o -o build/sb2 $(libs)
	
sb2_2.o : sb2_2.cpp
	$(CC) $(incs) sb2_2.cpp -c -o sb2_2.o	

sb2_2: sb2_2.o build/fw1.o
	$(CC) $(incs) sb2_2.o build/fw1.o -o build/sb2_2 $(libs)
	
sb3_1.o : sb3_1.cpp
	$(CC) $(incs) sb3_1.cpp -c -o sb3_1.o	

sb3_1: sb3_1.o build/fw1.o
	$(CC) $(incs) sb3_1.o build/fw1.o -o build/sb3_1 $(libs)
	
sb3_2.o : sb3_2.cpp
	$(CC) $(incs) sb3_2.cpp -c -o sb3_2.o	

sb3_2: sb3_2.o build/fw1.o
	$(CC) $(incs) sb3_2.o build/fw1.o -o build/sb3_2 $(libs)
	
sb3_3.o: sb3_3.cpp
	$(CC) $(incs) sb3_3.cpp -c -o sb3_3.o	

sb3_3: sb3_3.o build/fw1.o
	$(CC) $(incs) sb3_3.o build/fw1.o -o build/sb3_3 $(libs)

