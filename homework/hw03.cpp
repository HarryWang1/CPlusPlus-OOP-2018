/*
Max Kim
Lab C
February 14 2018
Make a fighting emulator with warriors and weapons. A weapon is the warrior's strength and the strength
decreases each time a warrior fights.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//A warrior has a a name and a weapon. A weapon has a name and a strength.
class Warrior {
private:
  class Weapon {
  	friend class Warrior;
  public:
    Weapon(const std::string aName, const int aStrength): name(aName), strength(aStrength) {}
    void loseStrength(int points) {
      strength = strength - points;
    }
  private:
    std::string name;
    int strength;
  };
  std::string name;
  Weapon weapon;
public:
  Warrior(const std::string& aName, const std::string& aWeaponName, const int aStrength): name(aName), weapon(aWeaponName, aStrength) {}
  void battle(Warrior& warrior_2) {
    std::cout << this->name << " battles " << warrior_2.name << "\n";
    int strength_1 = this->weapon.strength, strength_2 = warrior_2.weapon.strength;  //hold the strength of weapons to avoid repeat
    if (strength_1 == strength_2) {
			if ((strength_1 == 0) && (strength_2 == 0)) {	//both players are dead.
				std::cout << "Oh, NO! They're both dead! Yuck!\n";
			} else {   //both players kill themselves
				std::cout << "Mutual Annihilation: " << this->name << " and " << warrior_2.name << " die at each other's hands\n";
				this->weapon.loseStrength(strength_1);  //decrease strength for both players
				warrior_2.weapon.loseStrength(strength_2);
			}
	} else {	//one player wins over the other
		if (strength_1 > strength_2) {		//TODO: find a way to avoid repeating this check
			if (strength_2 == 0) {	//losing player was already dead
				std::cout << "He's dead, " << this->name << "\n";
			} else {	//both players fought
				std::cout << this->name << " defeats " << warrior_2.name << "\n";
				this->weapon.loseStrength(strength_2);		//decrease strength for both players
				warrior_2.weapon.loseStrength(strength_2);
			}
		} else {
			if (strength_1 == 0) {	//losing player was already dead
				std::cout << "He's dead, " << warrior_2.name << "\n";
			} else {	//both players fought
				std::cout << warrior_2.name << " defeats " << this->name << "\n";
				warrior_2.weapon.loseStrength(strength_1);		//decrease strength for both players
				this->weapon.loseStrength(strength_1);
			}
		}
    }
  }
  void display() const {
  	std::cout << "Warrior: " << this->name << ", weapon: " << this->weapon.name << ", " << this->weapon.strength << "\n";
  }
  std::string getName() const {
  	return this->name;
  }
};

void printStatus(const std::vector <Warrior>& warriors) {
  std::cout << "There are " << warriors.size() << " Warriors\n";
  for (const Warrior& warrior : warriors) {
    warrior.display();
  }
}

//choose what to do depending on what the first word in each line is
void chooseOption(std::ifstream& stream, std::vector <Warrior>& warriors) {
	std::string firstWord;
	stream >> firstWord;
	if ("Warrior" == firstWord) {		//create a warrior and add it into vector
		std::string aName, aWeaponName;
		int aStrength;
		stream >> aName >> aWeaponName >> aStrength;
		Warrior warrior(aName, aWeaponName, aStrength);
		warriors.push_back(warrior);
	} else if ("Battle" == firstWord) {
		std::string firstPlayer, secondPlayer;
		stream >> firstPlayer >> secondPlayer;
		int warrior_1, warrior_2; //Find warrior object with same name. use index to make it easier.
		for (size_t i = 0; i < warriors.size(); ++i) {   	//TODO: optimize better
			if (warriors[i].getName() == firstPlayer) {
				warrior_1 = i;
			} else if (warriors[i].getName() == secondPlayer) {
				warrior_2 = i;
			}
		}
		warriors[warrior_1].battle(warriors[warrior_2]);
	} else if ("Status" == firstWord) {
		printStatus(warriors);
	}
}

int main() {
	std::ifstream ifs("warriors2.txt");
	if (!ifs) {
		std::cerr << "Could not open file.\n";
		exit(1);
	}
  	std::vector <Warrior> warriors;
	while (ifs.peek() != EOF) {		//while not at the end of file
		chooseOption(ifs, warriors);
	}
}
