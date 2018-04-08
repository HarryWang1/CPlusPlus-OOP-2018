#include "Noble.h"
#include "Warrior.h"
#include "OneManArmy.h"
#include "ArmyCommander.h"
#include "Archer.h"
#include "Swordsman.h"
#include "Wizard.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
using namespace WarriorCraft;

/* NOTE!!! "Lord" is replaced with "ArmyCommander". "PersonWithStrengthToFight" is replaced with
"OneManArmy". "hires" method has been replaced with "hire". No output operator is included because
the main function does not use it, and no specification was given to how the output operator is suppoed
to work. */

int main() {
    ArmyCommander sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hire(samantha);
    ArmyCommander joe("Joe");
    OneManArmy randy("Randolf the Elder", 250); 	
    joe.battle(randy);	
    joe.battle(sam);	
    ArmyCommander janet("Janet");	
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hire(hardy);	
    janet.hire(stout);	
    OneManArmy barclay("Barclay the Bold", 300);	
    janet.battle(barclay);	
    janet.hire(samantha);	
    Archer pethora("Pethora", 50);	
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hire(pethora);
    janet.hire(thora);
    sam.hire(merlin);
    janet.battle(barclay);	
    sam.battle(barclay);	
    joe.battle(barclay);
}