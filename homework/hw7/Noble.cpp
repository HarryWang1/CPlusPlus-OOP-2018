#include "Noble.h"
#include <iostream>
#include <string>
using namespace std;

namespace WarriorCraft {
    Noble::Noble(const string& aName): name(aName), isAlive(true) {}
    bool Noble::getLivingStatus() const {
        return this->isAlive;
    }
    string Noble::getName() const {
        return this->name;
    }
    void Noble::battle(Noble& opponent) {
        cout << this->name << " battles " << opponent.name << endl;
        //noble's strengths are both equal
        if (this->getStrength() == opponent.getStrength()) {
            if (!this->isAlive && !opponent.isAlive) {
                cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
            } else {
                cout << "Mutual Annihilation: " << this->name << " and " << opponent.name << " die at each other's hands" << endl;
                this->loseStrength(0);
                opponent.loseStrength(0);
            }
        //one noble was already dead
        } else if ( (this->isAlive == false) | (opponent.isAlive == false) ) {
            if (!opponent.isAlive) {
                cout << "He's dead, " << this->name << endl; 
            } else {
                cout << "He's dead, " << opponent.name << endl; 
            }
        //one noble wins over the other
        } else {		
            //order matters when calling loseStrength() depending on who won
            if (this->getStrength() > opponent.getStrength()) {
                this->loseStrength((opponent.getStrength()/this->getStrength()));
                opponent.loseStrength(0);
                cout << this->name << " defeats " << opponent.name << endl;	
            } else {
                opponent.loseStrength((this->getStrength()/opponent.getStrength()));
                this->loseStrength(0);
                cout << opponent.name << " defeats " << this->name << endl;			
            }
        }
    }
    void Noble::changeLivingStatus(bool status) {
        this->isAlive = status;
    }
}