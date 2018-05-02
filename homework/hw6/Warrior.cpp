#include "Warrior.h"
#include "Noble.h"
#include <iostream>
#include <string>

using namespace std;

namespace WarriorCraft {
  Warrior::Warrior(const string& aName, const int aStrength):
    name(aName), 
    strength(aStrength), 
    employed(false), 
    noble(nullptr) {}		//default employed to false since not hired yet

  string Warrior::getName() const {
    return name;
  }
  float Warrior::getStrength() const {
    return strength;
  }
  void Warrior::setEmploymentStatus(bool status, Noble* hiringNoble) {
    employed = status;
    if (status == false) {    //reset noble pointer if fired
      this->noble = nullptr;
    }
    if (hiringNoble != nullptr) {   //replace noble pointer if new one given
      this->noble = hiringNoble;
    }
  }
  bool Warrior::getEmploymentStatus() const {
    return employed;
  }
  void Warrior::loseStrength(float factor) {
    strength = strength * factor;
  }
  bool Warrior::runaway() {
    if (this->noble != nullptr) {
      string tempNobleName = this->noble->getName();    //save the noble's name because it will be lost in the next line
      if (this->noble->loseWarrior(*this)) {
        cout << this->name << " flees in terror, abandoning his lord, " << tempNobleName << "\n";
        return true;
      }
      return false;
    } else {
      return false;
    }
  }
}