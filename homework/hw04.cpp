/*
MAX KIM
LAB C
February 19 2018
A arena simulator with warriors and nobles.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class Warrior {
  private:
    string name;
  	int strength;
  	bool employed;		
  public:
    Warrior(const string& aName, const int aStrength):
      name(aName), strength(aStrength), employed(false) {}		//default employed to false since not hired yet

    string getName() const {
      return name;
    }
    int getStrength() const {
    	return strength;
    }
    void setEmploymentStatus(bool status) {
      employed = status;
    }
    bool getEmploymentStatus() const {
      return employed;
    }
    void loseStrength(int factor) {
    	strength = strength * factor;
    }
};

class Noble {
  private:
    string name;
    vector<Warrior *> army;		//vector holds pointers to warriors. All pointers added will be const (in that what the pointer points to will not change, but the object will)
    bool isAlive;
  public:
    Noble(const string& aName):
      name(aName), isAlive(true) {}		//default noble isAlive = true at creation

    int strength() const {  //return the combined strength of the army
      int counter = 0;
      for (size_t i = 0; i < army.size(); ++i) {
        counter += army[i]->getStrength();
      }
      return counter;
    }

    bool fire(const Warrior& warrior) {	//delete warrior in noble's vector, in place without iterator
      if (isAlive && !army.empty()) {  //noble is alive and has warriors
        for (size_t i = 0; i < army.size(); ++i) {
          if (warrior.getName() == army[i]->getName()) {  //found warrior
            army[i]->setEmploymentStatus(false);   //make warrior unemployed
            cout << army[i]->getName() << ", you're fired! -- " << name << "\n";
            while (i + 1 < army.size()) {
              army[i] = army[i+1];	//swap every next one
            }
            army.pop_back();    //delete the repeat
            return true;  	//successful delete
          }
        }
      }
      return false;   //warrior not in army/noble is dead/noble has no warriors
    }

    bool hire(Warrior& warrior) {		//add in a pointer to warrior 
      if (isAlive) {
        if (warrior.getEmploymentStatus() == false) {
        	Warrior* const pwarrior = &warrior;			//what the pointer points to doesn't change. The object may change. Each pointer points to one warrior object. 
          army.push_back(pwarrior);
          return true;
        }
      }
      return false;
    }

    void loseStrength(int factor) {		//decrease strength of every warrior in this noble's group
      for (size_t i = 0; i < army.size(); ++i) {
        army[i]->loseStrength(factor);
      }
      if (factor == 0) {	//if factor is zero (as in noble died), set isAlive to false.
      	this->isAlive = false;
      }
    }

    void display() const {		//output every warrior hired by this noble
      cout << name << " has an army of " << army.size() << "\n";
      for (Warrior* warrior: army) {
        cout << "\t" << warrior->getName() << ": " << warrior->getStrength() << "\n";
      }
    }

    void battle(Noble& opponent) {
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
};

int main() {
  Noble art("King Arthur");
	Noble lance("Lancelot du Lac");
	Noble jim("Jim");
	Noble linus("Linus Torvalds");
	Noble billie("Bill Gates");

	Warrior cheetah("Tarzan", 10);
	Warrior wizard("Merlin", 15);
	Warrior theGovernator("Conan", 12);
	Warrior nimoy("Spock", 15);
	Warrior lawless("Xena", 20);
	Warrior mrGreen("Hulk", 8);
	Warrior dylan("Hercules", 3);

	jim.hire(nimoy);
	lance.hire(theGovernator);
	art.hire(wizard);
	lance.hire(dylan);
	linus.hire(lawless);
	billie.hire(mrGreen);
	art.hire(cheetah);

	jim.display();
	lance.display();
	art.display();
	linus.display();
	billie.display();

	art.fire(cheetah);
	art.display();

	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);
}
