#include <iostream>

#include "../include/Game.h"

int main() {
    try {
        Game gioco;
        gioco.run();
        return 0;
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}
