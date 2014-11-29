
include ../Makefile.inc
incs = -I../include

opts = $(libs) $(defs) $(incs)

all: ../build/fw1.o

tests: ../tests/fw1.o

clean:
	rm -f *.o tests/*.o

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

# Test Cases

tests/test_glversion.o: tests/test_glversion.cpp tests/test_glversion.h
	$(CC) $(incs) tests/test_glversion.cpp -c -o tests/test_glversion.o

../tests/fw1.o: tests.h tests/test_glversion.o ../build/fw1.o
	ld -r tests/test_glversion.o ../build/fw1.o -o ../tests/fw1.o
