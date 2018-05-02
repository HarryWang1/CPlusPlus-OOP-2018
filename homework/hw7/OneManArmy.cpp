#include "OneManArmy.h"
#include <iostream>
#include <string>
using namespace std;

namespace WarriorCraft {
    OneManArmy::OneManArmy(const string& name, int strength) : Noble(name), strength(strength) {}
    float OneManArmy::getStrength() const {
        return strength;
    }
    void OneManArmy::loseStrength(float factor) {
        strength = strength*factor;
        if (strength == 0) {
            changeLivingStatus(false);
        }
    }
}