#pragma once
#include <string>

enum ItemType { Weapon, Armor, Consumable, Utility };

class Item {
public:
    std::string name;
    ItemType type;
    float price;
    int quantity;

    Item(const std::string& name, ItemType type, float price, int quantity);
};
