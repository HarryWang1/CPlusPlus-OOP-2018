#ifndef ONEMANARMY_H
#define ONEMANARMY_H
#include "Noble.h"
#include <iostream>
#include <string>

namespace WarriorCraft {
    class OneManArmy : public Noble {
    public:
        OneManArmy(const std::string& name, int strength);
        float getStrength() const override;
        void loseStrength(float factor) override;
    private:
        float strength; 
    };
}

#endif