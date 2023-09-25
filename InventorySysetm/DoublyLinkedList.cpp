#include "DoublyLinkedList.h"
#include <iostream>
#include <fstream>
#include <sstream>

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

DoublyLinkedList::~DoublyLinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

void DoublyLinkedList::insert(const Item& item) {
    Node* newNode = new Node{ item, nullptr, nullptr };

    if (head == nullptr) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void DoublyLinkedList::remove(const std::string& name) {
    Node* current = head;
    while (current != nullptr) {
        if (current->item.name == name) {
            if (current->prev) {
                current->prev->next = current->next;
            }
            else {
                head = current->next;
            }

            if (current->next) {
                current->next->prev = current->prev;
            }
            else {
                tail = current->prev;
            }

            delete current;
            return;
        }
        current = current->next;
    }
}

Node* DoublyLinkedList::search(const std::string& name) {
    Node* current = head;
    while (current != nullptr) {
        if (current->item.name == name) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void DoublyLinkedList::edit(const std::string& name, const Item& newItem) {
    Node* node = search(name);
    if (node) {
        node->item = newItem;
    }
    else {
        std::cout << "Item not found" << std::endl;
    }
}

void DoublyLinkedList::loadFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name, typeStr, priceStr, quantityStr;

        std::getline(iss, name, '/');
        std::getline(iss, typeStr, '/');
        // Skip the extra '/' delimiter
        iss.ignore();
        std::getline(iss, priceStr, '/');
        std::getline(iss, quantityStr, '/');

        try {
            // Use stringToItemType function to convert typeStr to ItemType
            ItemType type = stringToItemType(typeStr);
            float price = std::stof(priceStr);
            int quantity = std::stoi(quantityStr);

            insert(Item{ name, type, price, quantity });
        }
        catch (const std::invalid_argument & e) {
            std::cerr << "Error: " << e.what() << " in line: " << line << std::endl;
        }
    }

    file.close();
}


ItemType DoublyLinkedList::stringToItemType(const std::string& typeStr) {
    std::string trimmedTypeStr;
    for (char c : typeStr) {
        if (!std::isspace(c)) {
            trimmedTypeStr.push_back(c);
        }
    }

    if (trimmedTypeStr == "Weapon") {
        return ItemType::Weapon;
    }
    else if (trimmedTypeStr == "Armor") {
        return ItemType::Armor;
    }
    else if (trimmedTypeStr == "Consumable") {
        return ItemType::Consumable;
    }
    else if (trimmedTypeStr == "Utility") {
        return ItemType::Utility;
    }
    else {
        throw std::invalid_argument("Invalid item type string");
    }
}



void DoublyLinkedList::saveToFile(const std::string& filePath) {
    std::ofstream file(filePath);
    Node* current = head;

    while (current != nullptr) {
        file << current->item.name << '/'
            << current->item.type << '/'
            << current->item.price << '/'
            << current->item.quantity << std::endl;
        current = current->next;
    }

    file.close();
}

void DoublyLinkedList::displayInventory() const {
    Node* current = head;

    while (current != nullptr) {
        std::cout << "Name: " << current->item.name
            << ", Type: " << current->item.type
            << ", Price: " << current->item.price
            << ", Quantity: " << current->item.quantity << std::endl;
        current = current->next;
    }
}

void DoublyLinkedList::quickSort(bool ascending) {
    quickSortHelper(head, tail, ascending);
}

void DoublyLinkedList::quickSortHelper(Node* left, Node* right, bool ascending) {
    if (left && right && left != right && left != right->next) {
        Node* pivot = partition(left, right, ascending);
        quickSortHelper(left, pivot->prev, ascending);
        quickSortHelper(pivot->next, right, ascending);
    }
}

Node* DoublyLinkedList::partition(Node* left, Node* right, bool ascending) {
    // Use the right node as the pivot
    Item pivot = right->item;

    Node* i = left->prev;

    for (Node* j = left; j != right; j = j->next) {
        if ((ascending && j->item.price < pivot.price) || (!ascending && j->item.price > pivot.price)) {
            if (i == nullptr) {
                i = left;
            }
            else {
                i = i->next;
            }
            std::swap(i->item, j->item);
        }
    }

    if (i == nullptr) {
        i = left;
    }
    else {
        i = i->next;
    }
    std::swap(i->item, right->item);

    return i;
}
