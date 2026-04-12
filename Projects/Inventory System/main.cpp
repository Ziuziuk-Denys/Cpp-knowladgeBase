// main.cpp
#include <iostream>

#include "Inventory.h"

// This program demonstrates the functionality of an inventory management system.
// It allows adding items, selling items, updating prices,
// finding the cheapest item, and saving/loading inventory data to/from a file.
int main() {
    // Create an instance of Inventory to manage our items
    Inventory inventory;

    // Reserve space for 3 items to optimize memory allocation
    inventory.items.reserve(3);

    // Add some items to the inventory
    inventory.addItem("ships", 99.99, 5);
    inventory.addItem("potato", 44.44, 54);
    inventory.addItem("coke", 34.44, 65);

    // Print the current inventory items
    for (const auto& item : inventory.items) {
        item.printInfo();
    }

    std::cout << std::endl;

    // Sell 3 units of "ships" and update its price
    inventory.sellItem("ships", 3);
    // Update the price of "ships" to 23 if the new price is lower than the current price
    inventory.updatePrice("ships", 23);

    // Print the updated inventory items
    for (const auto& item : inventory.items) {
        item.printInfo();
    }

    // Remove the item "potato" from the inventory
    inventory.removeItem("potato");
    std::cout << std::endl;

    // Print the inventory items after removal
    std::cout << "Cheapest item: ";
    inventory.findCheapest().printInfo();

    // Save the current inventory to a file named "items.txt"
    inventory.saveToFile("items.txt");

    // Load inventory data from a file named "load.txt"
    inventory.loadFromFile("load.txt");

    std::cout << std::endl;

    // Print the inventory items after loading from the file
    for (const auto& item : inventory.items) {
        item.printInfo();
    }
}
