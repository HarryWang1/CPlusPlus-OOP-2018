#include "ArmyCommander.h"
#include "Warrior.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace WarriorCraft {
    ArmyCommander::ArmyCommander(const string& name) : Noble(name) {}
    float ArmyCommander::getStrength() const {
        float counter = 0;
        for (size_t i = 0; i < army.size(); ++i) {
            counter += army[i]->getStrength();
        }
        return counter;
    }
    void ArmyCommander::loseStrength(float factor) {
        for (size_t i=0; i<army.size(); ++i) {
            army[i]->loseStrength(factor);
        }
        //if factor is zero, kill the noble. 
        if (factor == 0) {	
            changeLivingStatus(false);
        }
    }
    bool ArmyCommander::fire(Warrior& warrior) {
        //check if fire was successful
        if (loseWarrior(warrior)) {   
            cout << warrior.getName() << ", you're fired! -- " << getName() << endl;
            return true;
        } else {
            return false;
        }
    }
    bool ArmyCommander::hire(Warrior& warrior) {
        //check if noble is alive
        if (getLivingStatus()) {
            //check if warrior is not hired
            if (!warrior.getEmploymentStatus()) {
                Warrior* pwarrior = &warrior;	
                army.push_back(pwarrior);
                warrior.setEmploymentStatus(true, this);
                return true;
            }
        }
        return false;
    }
    bool ArmyCommander::loseWarrior(Warrior& warrior) {
        //check if noble is alive and has at least 1 warrior
        if (getLivingStatus() && !army.empty()) {  
            for (size_t i = 0; i < army.size(); ++i) {
                if (warrior.getName() == army[i]->getName()) {
                army[i]->setEmploymentStatus(false, nullptr);   //make warrior unemployed
                army[i] = army[int(army.size()-1)];      //overwrite with last warrior pointer
                army.pop_back();    //delete the last warrior duplicate
                return true;
                }
            }
        }
        return false;
    }
}