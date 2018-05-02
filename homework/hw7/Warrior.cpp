#include "Warrior.h"
#include "ArmyCommander.h"
#include "Noble.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace WarriorCraft {
    Warrior::Warrior(const string& name, int strength) : name(name),strength(strength),employed(false), commander(nullptr) {}
    string Warrior::getName() const {
        return this->name;
    }
    float Warrior::getStrength() const {
        return this->strength;
    }
    bool Warrior::getEmploymentStatus() const {
        return this->employed; 
    }
    void Warrior::loseStrength(float factor) {
        cout << getName() << " says: Take that in the name of my lord, " << this->commander->getName() << endl;
        strength = strength * factor;
    }
    void Warrior::setEmploymentStatus(bool status, ArmyCommander* hiringCommander) {
        employed = status;
        this->commander = hiringCommander; 
    }
    bool Warrior::runaway() {
        //check if warrior is employed
        if (employed) {
            //save noble's name because it will be lost later if success
            const string commanderName = this->commander->getName();
            //successful in firing warrior
            if (this->commander->loseWarrior(*this)) {
                cout << this->name << " flees in terror, abandoning his lord, " << commanderName << endl;
                return true;
            }
        }
        return false;
    }
}