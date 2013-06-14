CFLAGS=--std=c++0x -fPIC -g3

all: rpg
rpg: animation.o tiles.o strings.o characterstats.o character.o fade.o items.o events.o start_game.o
	g++ -o rpg rpg.cpp $(CFLAGS) animation.o tiles.o strings.o characterstats.o character.o fade.o items.o events.o start_game.o -lsfml-audio -lsfml-window -lsfml-system -lsfml-graphics -lsfml-network  -g3
animation.o:
	g++ -c -o animation.o animation.cpp $(CFLAGS)
tiles.o:
	g++ -c -o tiles.o tiles.cpp $(CFLAGS)
strings.o:
	g++ -c -o strings.o strings.cpp $(CFLAGS)
characterstats.o:
	g++ -c -o characterstats.o characterstats.cpp $(CFLAGS)
character.o:
	g++ -c -o character.o character.cpp $(CFLAGS)
fade.o:
	g++ -c -o fade.o fade.cpp $(CFLAGS)
items.o:
	g++ -c -o items.o items.cpp $(CFLAGS)
events.o:
	g++ -c -o events.o events.cpp $(CFLAGS)
start_game.o:
	g++ -c -o start_game.o start_game.cpp $(CFLAGS)
	
clean:
	rm -f *.o rpg
