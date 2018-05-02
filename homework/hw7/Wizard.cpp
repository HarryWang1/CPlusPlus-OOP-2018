#include "Wizard.h"
#include <iostream>
#include <string>
using namespace std;

namespace WarriorCraft {
    Wizard::Wizard(const string& name, int strength) : Warrior(name, strength) {}
    void Wizard::loseStrength(float factor) {
        cout << "POOF!" << endl;
        Warrior::loseStrength(factor);
    }
}