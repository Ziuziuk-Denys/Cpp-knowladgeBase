// Inventory.h
#pragma once
#include <iosfwd>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <fstream>

#include "Item.h"

// The Inventory class manages a collection of items.
// It provides functionalities to add, sell, update prices, find the cheapest item,
// remove items, and save/load inventory data to/from a file.
class Inventory {
public:
    std::vector<Item> items;

    // Adds a new item to the inventory with the specified name, price, and count.
    void addItem(const std::string& name, double price, int count) {
        items.emplace_back(Item{name, price, count});
    }

    // Sells a specified quantity of an item by its name.
    // If the item exists and has enough quantity, it reduces the count.
    void sellItem(const std::string& name, int quantity) {
        // Iterate through the items to find the item with the given name
        for (auto& item : items) {
            // If the item is found, check if there is enough quantity to sell
            if (item.name == name) {
                // If there is enough quantity, reduce the count by the quantity sold
                if (item.count >= quantity) {
                    item.count -= quantity;
                    return;
                }
                else {
                    std::cout << "Not enough items" << std::endl;
                }
            }
        }

    }

    // Updates the price of an item if the new price is lower than the current price.
    void updatePrice(const std::string& name, double newPrice) {
        for (auto& item : items) {
            // If the item is found and the new price is lower than the current price, update the price
            if (item.name == name && item.price > newPrice) {
                item.price = newPrice;
                return;
            }
        }
    }


    // Finds and returns a reference to the cheapest item in the inventory.
    Item& findCheapest() {
        // Start by assuming the first item is the cheapest
        Item* cheapest = &items[0];
        for (auto& item : items) {
            // If the current item is cheaper than the cheapest found so far, update the cheapest pointer
            if (item.price < cheapest->price) {
                cheapest = &item;
            }
        }
        return *cheapest;
    }

    // Removes an item from the inventory by its name.
    void removeItem(const std::string& name) {
        // Iterate through the items to find the item with the given name
        for (auto it = items.begin(); it != items.end(); ++it) {
            // If the item is found, erase it from the vector and return
            if (it->name == name) {
                items.erase(it);
                return;
            }
        }
    }

    // Saves the current inventory to a file with the specified filename.
    void saveToFile(std::string filename) {
        // Open the file for writing
        std::ofstream outfile(filename);
        // If the file cannot be opened, print an error message and return
        for (const auto& item : items) {
            // Write the item's name, price, and count to the file, separated by spaces
            outfile << item.name << " " << item.price << " " << item.count << std::endl;
        }
    }

    // Loads inventory data from a file with the specified filename.
    void loadFromFile(std::string filename) {
        // Open the file for reading
        std::ifstream infile(filename);
        // If the file cannot be opened, print an error message and return
        if (!infile.is_open()) {
            // If the file cannot be opened, print an error message and return
            std::cerr << "Could not open file: " << filename << std::endl;
            return;
        }
        // Clear the current inventory before loading new data
        std::string n;
        double p;
        int c;
        // Read the file line by line, extracting the name, price, and count for each item
        while (infile >> n >> p >> c) {
            addItem(n, p, c);
        }
    }
};
