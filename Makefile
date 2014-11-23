
all: basic

clean:
	rm -f basic

basic: basic.cpp display.cpp
	g++ -o basic basic.cpp display.cpp -lSDL2 -lGL

