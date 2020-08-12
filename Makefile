sDir = src/
bDir = build/

all: $(sDir)run.cpp $(sDir)game.h game
	g++ $(sDir)run.cpp -o bats_adventure -lSDL2 -lSDL2_image $(bDir)game.o

game: $(sDir)game.cpp
	g++ -c $(sDir)game.cpp -o $(bDir)game.o