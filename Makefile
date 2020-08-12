sDir = src/
bDir = build/

game: $(sDir)run.cpp
	g++ $(sDir)run.cpp -o bats_adventure