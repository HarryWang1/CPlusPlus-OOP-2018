#ifndef NOBLE_H
#define NOBLE_H
#include <string>
#include <iostream>

namespace WarriorCraft {
    class Noble {
    public:
        Noble(const std::string& aName);
        virtual float getStrength() const =0;
        bool getLivingStatus() const;
        std::string getName() const;
        virtual void loseStrength(float factor) =0;
        void battle(Noble& opponent);
        void changeLivingStatus(bool status);
    private:
        std::string name;
        bool isAlive;
    };
}

#endif