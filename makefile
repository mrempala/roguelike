# Not the best makefile in the world
all:
	g++ main.cpp game.h game.cpp -g -Wno-write-strings -o main.out

run:
	./main.out
