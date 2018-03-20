#ifndef WARRIOR_H
#define WARRIOR_H
#include <string>
#include <iostream>

namespace WarriorCraft {
  class Noble;
  class Warrior {
    private:
      std::string name;
  	  float strength;
  	  bool employed;
      Noble* noble;
    public:
      Warrior(const std::string& aName, const int aStrength);
      std::string getName() const;
      float getStrength() const;
      void setEmploymentStatus(bool status, Noble* hiringNoble=nullptr);
      bool getEmploymentStatus() const;
      void loseStrength(float factor);
      bool runaway();
  };
}
#endif