#include <iostream>

#include <vector>

#include <list>

#include <string>

#include <queue>

using namespace std;

class Player {
public:

    int strength;
    int agility;
    int intelligence;
    int health = 20;
    queue < int > inventory;

    Player() {}

    Player(int strength, int agility, int intelligence) {
        this->strength = strength;
        this->agility = agility;
        this->intelligence = intelligence;
    }

    int getStrength() const {
        return strength;
    }

    void setStrength(int strength) {
        this->strength = strength;
    }

    int getAgility() const {
        return agility;
        return agility;
    }

    void setAgility(int agility) {
        this->agility = agility;
    }

    int getIntelligence() const {
        return intelligence;
    }

    void setIntelligence(int intelligence) {
        this->intelligence = intelligence;
    }

    void addItemToInventory(int item) {
        if (inventory.size() >= 5) {
            inventory.pop();
        }
        inventory.push(item);
    }

    bool checkItemInInventory(int item) {
        vector<int> temp;
        while (!inventory.empty()) {
            temp.push_back(inventory.front());
            inventory.pop();
        }

        bool found = find(temp.begin(), temp.end(), item) != temp.end();

        // Restore the original queue
        for (int num : temp) {
            inventory.push(num);
        }

        return found;
    }

    void printInventory() {
        cout << "Inventory:\n";
        queue < int > temp = inventory;
        while (!temp.empty()) {
            cout << "- " << temp.front() << endl;
            temp.pop();
        }
    }
};