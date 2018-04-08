#include "Swordsman.h"
#include <iostream>
#include <string>
using namespace std;

namespace WarriorCraft {
    Swordsman::Swordsman(const string& name, int strength) : Warrior(name, strength) {}
    void Swordsman::loseStrength(float factor) {
        cout << "CLANG! ";
        Warrior::loseStrength(factor);
    }
}