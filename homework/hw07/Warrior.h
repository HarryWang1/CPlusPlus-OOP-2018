#ifndef WARRIOR_H
#define WARRIOR_H
#include "ArmyCommander.h"
#include <string>
#include <iostream>

namespace WarriorCraft {  
    class ArmyCommander; 
    class Warrior {
    public:
        Warrior(const std::string& name, int strength);
        std::string getName() const;
        float getStrength() const;
        bool getEmploymentStatus() const;
        virtual void loseStrength(float factor) =0;
        void setEmploymentStatus(bool status, ArmyCommander* hiringcommander);
        bool runaway();
    private:
        std::string name;
        float strength; 
        bool employed;
        ArmyCommander* commander;
    };
}

#endif