#include "Item.h"

Item::Item(const std::string& name, ItemType type, float price, int quantity)
    : name(name), type(type), price(price), quantity(quantity) {}
