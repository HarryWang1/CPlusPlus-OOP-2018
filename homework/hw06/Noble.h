#ifndef NOBLE_H
#define NOBLE_H
#include "Warrior.h"
#include <string>
#include <iostream>
#include <vector>

namespace WarriorCraft {
  class Noble {
    friend std::ostream& operator<<(std::ostream& os, const Noble& noble);
    private:
      std::string name;
      std::vector<Warrior *> army;		//vector holds pointers to warriors. All pointers added will be const (in that what the pointer points to will not change, but the object will)
      bool isAlive;
    public:
      Noble(const std::string& aName);
      std::string getName() const;
      float strength() const;
      bool fire(Warrior& warrior);
      bool hire(Warrior& warrior);
      bool loseWarrior(Warrior& warrior);
      void loseStrength(float factor);
      void battle(Noble& opponent);
  };
}

#endif