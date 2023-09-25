#include <iostream>
#include "DoublyLinkedList.h"

int main() {
    DoublyLinkedList inventory;
    int choice;

    // Load initial inventory from file
    inventory.loadFromFile("initial_inventory.txt");

    do {
        std::cout << "Menu options:" << std::endl;
        std::cout << "1. Display Inventory" << std::endl;
        std::cout << "2. Sort Inventory" << std::endl;
        std::cout << "3. Add Item" << std::endl;
        std::cout << "4. Delete Item" << std::endl;
        std::cout << "5. Edit Item" << std::endl;
        std::cout << "6. Load Inventory from File" << std::endl;
        std::cout << "7. Save Inventory to File" << std::endl;
        std::cout << "8. Exit" << std::endl;

        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1:
            inventory.displayInventory();
            break;
        case 2: {
            bool ascending;
            std::cout << "Enter 1 for ascending or 0 for descending: ";
            std::cin >> ascending;
            inventory.quickSort(ascending);
            inventory.displayInventory();
            break;
        }
        case 3: {
            std::string name;
            int type;
            float price;
            int quantity;

            std::cout << "Enter item name: ";
            std::getline(std::cin, name);
            std::cout << "Enter item type (0 - Weapon, 1 - Armor, 2 - Consumable, 3 - Utility): ";
            std::cin >> type;
            std::cout << "Enter item price: ";
            std::cin >> price;
            std::cout << "Enter item quantity: ";
            std::cin >> quantity;

            inventory.insert(Item{ name, static_cast<ItemType>(type), price, quantity });
            std::cout << "Item added successfully" << std::endl;
            break;
        }
        case 4: {
            std::string name;
            std::cout << "Enter the name of the item to delete: ";
            std::getline(std::cin, name);

            inventory.remove(name);
            std::cout << "Item removed successfully" << std::endl;
            break;
        }
        case 5: {
            std::string name;
            int type;
            float price;
            int quantity;

            std::cout << "Enter the name of the item to edit: ";
            std::getline(std::cin, name);

            std::cout << "Enter new item type (0 - Weapon, 1 - Armor, 2 - Consumable, 3 - Utility): ";
            std::cin >> type;
            std::cout << "Enter new item price: ";
            std::cin >> price;
            std::cout << "Enter new item quantity: ";
            std::cin >> quantity;

            inventory.edit(name, Item{ name, static_cast<ItemType>(type), price, quantity });
            std::cout << "Item edited successfully" << std::endl;
            break;
        }
        case 6: {
            std::string filePath;
            std::cout << "Enter file path: ";
            std::cin >> filePath;
            inventory.loadFromFile(filePath);
            break;
        }
        case 7: {
            std::string filePath;
            std::cout << "Enter file path: ";
            std::cin >> filePath;
            inventory.saveToFile(filePath);
            break;
        }
        }
    } while (choice != 8);

    return 0;
}
