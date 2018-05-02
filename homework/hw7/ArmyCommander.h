#ifndef ARMYCOMMANDER_H
#define ARMYCOMMANDER_H
#include "Warrior.h"
#include "Noble.h"
#include <iostream>
#include <string>
#include <vector>

namespace WarriorCraft {
    class Warrior;
    class ArmyCommander : public Noble {
    public:
        ArmyCommander(const std::string& name);
        float getStrength() const;
        void loseStrength(float factor);
        bool fire(Warrior& warrior);
        bool hire(Warrior& warrior);
        bool loseWarrior(Warrior& warrior);
    private:
        std::vector<Warrior* > army;
    };
}

#endif