#ifndef SWORDSMAN_H
#define SWORDSMAN_H
#include "Warrior.h"
#include <string>
#include <iostream>

namespace WarriorCraft {
    class Swordsman : public Warrior{
    public:
        Swordsman(const std::string& name, int strength);
        void loseStrength(float factor) override;
    };
}

#endif