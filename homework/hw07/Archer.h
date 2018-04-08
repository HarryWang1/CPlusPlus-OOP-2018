#ifndef ARCHER_H
#define ARCHER_H
#include "Warrior.h"
#include <iostream>
#include <string>

namespace WarriorCraft {
    class Archer : public Warrior {
    public:
        Archer(const std::string& name, int strength);
        void loseStrength(float factor) override;
    };
}

#endif