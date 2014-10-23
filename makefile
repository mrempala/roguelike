main.out:	goblin.o player.o game.o main.o
			g++ -g -o main.out goblin.o player.o game.o main.o

goblin.o:	goblin.cpp goblin.h
				g++ -c -g goblin.cpp

player.o:		player.cpp player.h
			g++ -c -g player.cpp 

game.o:		game.cpp game.h 
			g++ -c -g game.cpp 
			
main.o:		main.cpp
			g++ -c -g -Wno-write-strings main.cpp

run:
			./main.out
			
clean:
			rm *.o main.out
