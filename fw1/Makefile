
include ../Makefile.inc
incs = -I../include

opts = $(libs) $(defs) $(incs)

all: ../build/fw1.o

../build/fw1.o: sdldisplay.o shader.o logger.o config.o fw1.h
	ld -r sdldisplay.o shader.o logger.o config.o -o ../build/fw1.o

sdldisplay.o: sdldisplay.cpp sdldisplay.h 
	$(CC) $(incs) sdldisplay.cpp -c -o sdldisplay.o $(libs)

shader.o: shader.cpp shader.h 
	$(CC) $(incs) shader.cpp -c -o shader.o $(libs)

logger.o: logger.cpp logger.h 
	$(CC) $(incs) logger.cpp -c -o logger.o $(libs)

config.o: config.cpp config.h 
	$(CC) $(incs) config.cpp -c -o config.o $(libs)
