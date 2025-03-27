#include <iostream>
#include "../include/Game.h"

int main() {
    try {
        Game gioco;
        gioco.run();
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }


    return 0;
}
