
include Makefile.inc
incs = -I./include

opts = $(libs) $(defs) $(incs)

all: system basic

clean:
	rm -f build/* *.o
	cd ./system && $(MAKE) clean
	
system:
	cd ./system && $(MAKE)

#Hack to fix compilation logic
system/sdl2display.o:
	cd ./system && $(MAKE) sdl2display.o

basic: basic.o system/sdl2display.o
	$(CC) $(incs) basic.cpp system/sdl2display.o -o build/basic $(libs) 

basic.o:
	$(CC) $(incs) basic.cpp -c -o basic.o

