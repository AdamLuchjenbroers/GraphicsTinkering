
include ../Makefile.inc
incs = -I../include

opts = $(defs) $(incs)

ifeq ($(display), windows)
  displayclass = wgldisplay
else
  displayclass = sdl2display
endif

all: sdl2display.o

#engine.o: engine.cpp 
#	$(CC) engine.cpp $(opts) -c -o engine.o

#wgldisplay.o: win32/wgldisplay.cpp win32/wgldisplay.h ../include/system/display.h
#	$(CC) win32/wgldisplay.cpp $(opts) -c -o wgldisplay.o

#glxdisplay.o: linux/glxdisplay.cpp linux/glxdisplay.h ../include/system/display.h
#	$(CC) linux/glxdisplay.cpp $(opts) -c -o glxdisplay.o

#bindings.o: bindings.cpp ../include/system/system.h
#

sdl2display.o: sdl2/sdl2display.cpp sdl2/sdl2display.h ../include/system/display.h
	$(CC) sdl2/sdl2display.cpp $(opts) -c -o sdl2display.o

clean:
	rm -f *.o
