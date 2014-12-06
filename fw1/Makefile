
incs = -I../include

include ../Makefile.inc

opts = $(libs) $(defs) $(incs)

all: ../build/fw1.a

tests: ../tests/fw1.o

clean:
	rm -f *.o tests/*.o

../build/fw1.a: SDLDisplay.o Shader.o logger.o config.o ShaderLibrary.o ShaderProgram.o 
	ld -r $^ -o $@

# Test Cases

tests/test_glversion.o: tests/test_glversion.cpp tests/test_glversion.h
	$(CC) $(incs) tests/test_glversion.cpp -c -o tests/test_glversion.o

tests/test_glslversion.o: tests/test_glversion.cpp tests/test_glversion.h
	$(CC) $(incs) tests/test_glslversion.cpp -c -o tests/test_glslversion.o

../tests/fw1.o: tests.h tests/test_glversion.o tests/test_glslversion.o ../build/fw1.o
	ld -r tests/test_glversion.o tests/test_glslversion.o ../build/fw1.o -o ../tests/fw1.o
