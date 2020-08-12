sDir = src/
bDir = build/

all: $(sDir)run.cpp $(sDir)game.h game $(sDir)utils.h utils
	g++ $(sDir)run.cpp -o bats_adventure -lSDL2 -lSDL2_image $(bDir)game.o $(bDir)utils.o

game: $(sDir)game.cpp
	g++ -c $(sDir)game.cpp -o $(bDir)game.o

utils: $(sDir)utils.cpp
	g++ -c $(sDir)utils.cpp -o $(bDir)utils.o