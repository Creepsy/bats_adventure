#include <iostream>

#include "game.h"

int main() {
    srand(time(nullptr));
    
    game g{1024, 512, "Bat's Adventure"};
    if(!g.init()) return 1;

    g.run();

    return 0;
}