
all: basic

clean:
	rm -f basic

basic: basic.cpp
	g++ -o basic basic.cpp -lSDL

