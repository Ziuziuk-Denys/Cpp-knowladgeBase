#include <vector>
#include <iostream>
#include <thread>
#include <chrono>
#include "character.h"



int main() {
    std::thread backgroundWorker(saveHealth);
    std::vector<Character> characters;

    Character miku("miku", 999);
    characters.push_back(miku);

    Character sukuna("sukuna", 543);
    characters.push_back(sukuna);

    Character stone("stone", 54);
    characters.push_back(stone);

    Heal(characters[0]);

    for (size_t i = 0; i < characters.size(); ++i) {
        std::cout << "Character name: " << characters[i].name << "Character health:  " << characters[i].health << std::endl;
    }

    backgroundWorker.join();
};

