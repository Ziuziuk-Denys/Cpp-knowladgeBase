// Item.h
#pragma once
#include <iostream>
#include <ostream>
#include <string>

// The Item class represents an individual item in the inventory.
// It contains the item's name, price, and count (quantity).
class Item {
public:
// Constructor to initialize an item with a name, price, and count
    std::string name;
    double price;
    int count;
// Constructor to initialize an item with a name, price, and count
    void printInfo() const {
        std::cout << name << " " << price << " " << count << std::endl;
    }
};
