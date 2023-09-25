#pragma once
#include "Item.h"

struct Node {
    Item item;
    Node* prev;
    Node* next;
};

class DoublyLinkedList {
public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void insert(const Item& item);
    void remove(const std::string& name);
    Node* search(const std::string& name);
    void edit(const std::string& name, const Item& newItem);
    void loadFromFile(const std::string& filePath);
    void saveToFile(const std::string& filePath);
    void displayInventory() const;
    void quickSort(bool ascending);
    ItemType stringToItemType(const std::string& typeStr);
private:
    void quickSortHelper(Node* left, Node* right, bool ascending);
    Node* partition(Node* left, Node* right, bool ascending);
    Node* head;
    Node* tail;
};
