sDir = src/
bDir = build/

all: $(sDir)run.cpp $(sDir)game.h game $(sDir)utils.h utils animatable $(sDir)animatable.h player $(sDir)player.h blood_bar $(sDir)blood_bar.h entity_types $(sDir)entity_types.h snake $(sDir)snake.h grass_hopper $(sDir)grass_hopper.h
	g++ $(sDir)run.cpp -o bats_adventure -lSDL2 -lSDL2_image -lSDL2_ttf $(bDir)game.o $(bDir)utils.o $(bDir)animatable.o $(bDir)player.o $(bDir)blood_bar.o $(bDir)entity_types.o $(bDir)snake.o $(bDir)grass_hopper.o

game: $(sDir)game.cpp
	g++ -c $(sDir)game.cpp -o $(bDir)game.o

utils: $(sDir)utils.cpp
	g++ -c $(sDir)utils.cpp -o $(bDir)utils.o

animatable: $(sDir)animatable.cpp
	g++ -c $(sDir)animatable.cpp -o $(bDir)animatable.o

player: $(sDir)player.cpp
	g++ -c $(sDir)player.cpp -o $(bDir)player.o

blood_bar: $(sDir)blood_bar.cpp
	g++ -c $(sDir)blood_bar.cpp -o $(bDir)blood_bar.o

entity_types: $(sDir)entity_types.cpp
	g++ -c $(sDir)entity_types.cpp -o $(bDir)entity_types.o

snake: $(sDir)snake.cpp
	g++ -c $(sDir)snake.cpp -o $(bDir)snake.o

grass_hopper: $(sDir)grass_hopper.cpp
	g++ -c $(sDir)grass_hopper.cpp -o $(bDir)grass_hopper.o