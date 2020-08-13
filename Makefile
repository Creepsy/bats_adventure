sDir = src/
bDir = build/

all: $(sDir)run.cpp $(sDir)game.h game $(sDir)utils.h utils animatable $(sDir)animatable.h player $(sDir)player.h
	g++ $(sDir)run.cpp -o bats_adventure -lSDL2 -lSDL2_image $(bDir)game.o $(bDir)utils.o $(bDir)animatable.o $(bDir)player.o

game: $(sDir)game.cpp
	g++ -c $(sDir)game.cpp -o $(bDir)game.o

utils: $(sDir)utils.cpp
	g++ -c $(sDir)utils.cpp -o $(bDir)utils.o

animatable: $(sDir)animatable.cpp
	g++ -c $(sDir)animatable.cpp -o $(bDir)animatable.o

player: $(sDir)player.cpp
	g++ -c $(sDir)player.cpp -o $(bDir)player.o