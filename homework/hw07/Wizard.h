#ifndef WIZARD_H
#define WIZARD_H
#include "Warrior.h"
#include <string>
#include <iostream>

namespace WarriorCraft {
    class Wizard : public Warrior {
    public:
        Wizard(const std::string& name, int strength);
        void loseStrength(float factor) override;
    };
}

#endif