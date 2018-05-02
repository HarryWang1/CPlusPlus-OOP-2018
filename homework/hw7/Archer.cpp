#include "Archer.h"
#include <iostream>
#include <string>
using namespace std;

namespace WarriorCraft {
    Archer::Archer(const string& name, int strength) : Warrior(name, strength) {}
    void Archer::loseStrength(float factor) {
        cout << "TWANG! ";
        Warrior::loseStrength(factor);
    }
}