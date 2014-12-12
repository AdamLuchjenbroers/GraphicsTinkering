
incs = -I../include

include ../Makefile.inc

opts = $(libs) $(defs) $(incs)

all: ../build/fw1.a

tests: ../tests/fw1.a

clean:
	rm -f *.o tests/*.o

../build/fw1.a: SDLDisplay.o Shader.o ShaderLibrary.o ShaderProgram.o ShaderRef.o VersionNumber.o
../build/fw1.a: GLVersion.o GLSLVersion.o Logger.o
	ld -r $^ -o $@

# Test Cases

tests/test_glversion.o: tests/test_glversion.cpp tests/test_glversion.h
	$(CC) $(incs) tests/test_glversion.cpp -c -o tests/test_glversion.o

tests/test_glslversion.o: tests/test_glversion.cpp tests/test_glversion.h
	$(CC) $(incs) tests/test_glslversion.cpp -c -o tests/test_glslversion.o

../tests/fw1.a: tests/test_glversion.o tests/test_glslversion.o ../build/fw1.a
	ld -r $^ -o $@
