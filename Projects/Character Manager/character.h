#include <iostream>
#include <string>
#include <thread>
#include <chrono>

class Character {
    public:
        std::string name;
        int health;
    Character(std::string n, int h) {
        name = n;
        health = h;
    }
};

void Heal(Character &c){
    c.health += 100;
};

void saveHealth() {
    std::cout << "Saving health..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "Health is saved!" << std::endl;
}







