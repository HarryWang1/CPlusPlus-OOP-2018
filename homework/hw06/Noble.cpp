#include "Noble.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace WarriorCraft {
  Noble::Noble(const string& aName):
      name(aName), isAlive(true) {}		//default noble isAlive = true at creation

  string Noble::getName() const {
    return this->name;
  }
  float Noble::strength() const {  //return the combined strength of the army
    float counter = 0;
    for (size_t i = 0; i < army.size(); ++i) {
      counter += army[i]->getStrength();
    }
    return counter;
  }

  bool Noble::fire(Warrior& warrior) {	//delete warrior in noble's vector, in place without iterator
    if (loseWarrior(warrior)) {   //if successfully delete warrior, print.
      cout << warrior.getName() << ", you're fired! -- " << name << "\n";
      return true;
    } else {
      return false;
    }
  }

  bool Noble::hire(Warrior& warrior) {		//add in a pointer to warrior 
    if (isAlive) {
      if (warrior.getEmploymentStatus() == false) {
        Warrior* pwarrior = &warrior;			//what the pointer points to doesn't change. The object may change. Each pointer points to one warrior object. 
        army.push_back(pwarrior);
        warrior.setEmploymentStatus(true, this);
        return true;
      }
    }
    return false;
  }

  bool Noble::loseWarrior(Warrior& warrior) {  //delete warrior in noble's vector, in place without iterator
    if (isAlive && !army.empty()) {  //noble is alive and has warriors
      for (size_t i = 0; i < army.size(); ++i) {
        if (warrior.getName() == army[i]->getName()) {  //found warrior
          army[i]->setEmploymentStatus(false);   //make warrior unemployed
          while (i + 1 < army.size()) {
            army[i] = army[i+1];  //swap every next one
          }
          army.pop_back();    //delete the repeat
          return true;    //successful delete
        }
      }
    }
    return false;   //warrior not in army/noble is dead/noble has no warriors
  }

  void Noble::loseStrength(float factor) {		//decrease strength of every warrior in this noble's group
    for (size_t i = 0; i < army.size(); ++i) {
      army[i]->loseStrength(factor);
    }
    if (factor == 0) {	//if factor is zero (as in noble died), set isAlive to false.
      this->isAlive = false;
    }
  }

  void Noble::battle(Noble& opponent) {
    cout << this->name << " battles " << opponent.name << "\n";
    int strength_1 = this->strength(), strength_2 = opponent.strength();	//keep this->strength and opponent's strength in integers so that i don't have to repeat
    if (strength_1 == strength_2) {		//noble's strengths are equal
      if ( (!this->isAlive) && (!opponent.isAlive) ) {
        cout << "Oh, NO!  They're both dead!  Yuck!\n";
      } else {
        cout << "Mutual Annihilation: " << this->name << " and " << opponent.name << " die at each other's hands\n";
        this->loseStrength(0);
        opponent.loseStrength(0);
      }
    } else if ( (this->isAlive == false) | (opponent.isAlive == false) ) {		//one noble is dead
      if (!opponent.isAlive) {
        cout << "He's dead, " << this->name << "\n";
      } else {
        cout << "He's dead, " << opponent.name << "\n";
      }
    } else {		//one noble wins over the other
      if (strength_1 > strength_2) {
        cout << this->name << " defeats " << opponent.name << "\n";
        this->loseStrength((strength_2/strength_1));
        opponent.loseStrength(0);			//order matters here
      } else {
        cout << opponent.name << " defeats " << this->name << "\n";
        opponent.loseStrength((strength_1/strength_2));
        this->loseStrength(0);			//order matters here
      }
    }
  }

  ostream& operator<<(ostream& os, const Noble& noble) {
    cout << noble.name << " has an army of " << noble.army.size() << "\n";
    for (const Warrior* warrior: noble.army) {
      cout << "\t" << warrior->getName() << ": " << warrior->getStrength() << "\n";
    }
    return os;
  }
}
