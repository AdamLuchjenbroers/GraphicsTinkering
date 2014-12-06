
include ../Makefile.inc
incs = -I../include

opts = $(libs) $(defs) $(incs)

all: ../build/fw1.o

tests: ../tests/fw1.o

clean:
	rm -f *.o tests/*.o

../build/fw1.o: SDLDisplay.o Shader.o logger.o config.o ShaderLibrary.o ShaderProgram.o fw1.h 
	ld -r SDLDisplay.o Shader.o logger.o config.o ShaderLibrary.o ShaderProgram.o -o ../build/fw1.o

SDLDisplay.o: SDLDisplay.cpp SDLDisplay.h 
	$(CC) $(incs) SDLDisplay.cpp -c -o SDLDisplay.o $(libs)

logger.o: logger.cpp logger.h 
	$(CC) $(incs) logger.cpp -c -o logger.o $(libs)

config.o: config.cpp config.h 
	$(CC) $(incs) config.cpp -c -o config.o $(libs)

ShaderLibrary.o: ShaderLibrary.cpp ShaderLibrary.h
	$(CC) $(incs) ShaderLibrary.cpp -c -o ShaderLibrary.o
	
Shader.o: Shader.cpp Shader.h 
	$(CC) $(incs) Shader.cpp -c -o Shader.o $(libs)
	
ShaderProgram.o: ShaderProgram.cpp ShaderProgram.h 
	$(CC) $(incs) ShaderProgram.cpp -c -o ShaderProgram.o $(libs)

# Test Cases

tests/test_glversion.o: tests/test_glversion.cpp tests/test_glversion.h
	$(CC) $(incs) tests/test_glversion.cpp -c -o tests/test_glversion.o

tests/test_glslversion.o: tests/test_glversion.cpp tests/test_glversion.h
	$(CC) $(incs) tests/test_glslversion.cpp -c -o tests/test_glslversion.o

../tests/fw1.o: tests.h tests/test_glversion.o tests/test_glslversion.o ../build/fw1.o
	ld -r tests/test_glversion.o tests/test_glslversion.o ../build/fw1.o -o ../tests/fw1.o
