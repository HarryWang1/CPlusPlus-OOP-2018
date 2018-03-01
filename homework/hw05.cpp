/*
MAX KIM
LAB C
February 25 2018
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
  public:
    Warrior(const string& aName, const int aStrength):
      name(aName), strength(aStrength) {}		//default employed to false since not hired yet
    //don't need destructor, string will automatically call its destructor and strength is on stack
    
    const string& getName() const {
      return name;
    }

    int getStrength() const {
    	return strength;
    }

    void loseStrength(int points) {   //special case. Points could be bigger than the strength size
    	strength = strength - points;
      if (strength < 0) {
        strength = 0;
      }
    }

    void display() const {
      cout << this->getName() << ": " << this->getStrength() << "\n";
    }
};

class Noble {
  private:
    string name;
    vector<Warrior*> army;		//vector holds pointers to warriors. All pointers added will be const (in that what the pointer points to will not change, but the object will)
    bool isAlive;
  public:
    Noble(const string& aName):
      name(aName), isAlive(true) {}		//default noble isAlive = true at creation
    
    ~Noble() {    //destructor
      //don't delete the name string because destructor will be called automatically
      army.clear();  //call the destructor of each warrior in army
    }

    int strength() const {  //return the combined strength of the army
      int counter = 0;
      for (size_t i = 0; i < army.size(); ++i) {
        counter += army[i]->getStrength();
      }
      return counter;
    }

    const string& getName() const {
      return this->name;
    }

    vector<Warrior*>& getArmy() {	//not constant since army will be used to change
    	return this->army;
    }

    bool fire(const Warrior& warrior) {	//delete warrior in noble's vector, in place without iterator
      if (isAlive && !army.empty()) {  //noble is alive and has warriors
        for (size_t i = 0; i < army.size(); ++i) {
          if (warrior.getName() == army[i]->getName()) {  //found warrior
            cout << "You don't work for me anymore " << army[i]->getName() << "! -- " << name << ".\n";
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

    bool hire(Warrior* const warrior) {		//add in a pointer to warrior. Precondition: warrior is unemployed
      if (isAlive) {
          //what the pointer points to doesn't change. The object may change. Each pointer points to one warrior object.
          army.push_back(warrior);
          return true;
      }
      return false;
    }

    void loseStrength(int points) {		//decrease strength of every warrior in this noble's group
      for (size_t i = 0; i < army.size(); ++i) {
        army[i]->loseStrength(points);
      }
      if (this->strength() == 0) {	//if any warrior died, noble also dies.
      	this->isAlive = false;
      }
    }

    void display() const {		//output every warrior hired by this noble
      cout << name << " has an army of " << army.size() << "\n";
      for (Warrior* warrior: army) {
        cout << "\t" << warrior->getName() << ": " << warrior->getStrength() << "\n";
      }
    }

    void battle(Noble* opponent) {  //potential problem with loseStrength -> warriors not all same number of strength. This could be bigger than the strength number.
      cout << this->name << " battles " << opponent->name << "\n";
      int strength_1 = this->strength(), strength_2 = opponent->strength();	//keep this->strength and opponent's strength in integers so that i don't have to repeat
      if (strength_1 == strength_2) {		//noble's strengths are equal
        if ( (!this->isAlive) && (!opponent->isAlive) ) {
          cout << "Oh, NO!  They're both dead!  Yuck!\n";
        } else {
          cout << "Mutual Annihilation: " << this->name << " and " << opponent->name << " die at each other's hands\n";
          this->loseStrength(strength_1);
          opponent->loseStrength(strength_2);
        }
      } else if ((this->isAlive == false)|(opponent->isAlive == false)) {		//one noble is dead
        if (!opponent->isAlive) {
          cout << "He's dead, " << this->name << "\n";
        } else {
          cout << "He's dead, " << opponent->name << "\n";
        }
      } else {		//one noble wins over the other. Strength is decreased by whatever amount the loser had.
        if (strength_1 > strength_2) {
          cout << this->name << " defeats " << opponent->name << "\n";
          this->loseStrength(strength_2);
          opponent->loseStrength(strength_2);			//order matters here
        } else {
          cout << opponent->name << " defeats " << this->name << "\n";
          opponent->loseStrength(strength_1);
          this->loseStrength(strength_1);			//order matters here
        }
      }
    }
};

//choose what to do depending on what the first word in each line is
void chooseOption(ifstream& stream, vector<Warrior*>& warriors, vector<Noble*>& nobles) {
  string firstWord;
  stream >> firstWord;
  if ("Warrior" == firstWord) { //create new warrior on heap and add to unemployed list of warriors
    string name;
    int strength;
    stream >> name >> strength;        //check for errors here
    Warrior* warrior = new Warrior(name, strength);
    warriors.push_back(warrior);
  } else if ("Noble" == firstWord) { //create new noble on heap and add to list of nobles
    string name;
    stream >> name;                   //check for errors here
    Noble* noble = new Noble(name);
    nobles.push_back(noble);
  } else if ("Hire" == firstWord) { //search for noble. search for warrior in unemployed warriors list. add to noble's army and remove from unemployed list
    string nobleName, warriorName;	//possible errors: warrior already hired, doesnt exist,or noble doesn't exist
    stream >> nobleName >> warriorName;
    Noble* noble = nullptr;				//hold a temporary pointer to find each object
    Warrior* warrior = nullptr;
    for (size_t i = 0; i < nobles.size(); ++i) {	//find noble pointer
    	if (nobleName == nobles[i]->getName()) {
    		noble = nobles[i];
    		break;
    	}
    }
    if (noble == nullptr) {
    	cout << "Noble does not exist!\n";
    	return;
    }
    for (size_t i = 0; i < warriors.size(); ++i) {	//find warrior pointer
    	if (warriorName == warriors[i]->getName()) {
    		warrior = warriors[i];
    		break;
    	}
    }
    if (warrior == nullptr) {
    	cout << "Warrior does not exist!\n";
    	return;
    }
    if (noble->hire(warrior)) { 			//hire the warrior.
    	for (size_t i = 0; i < warriors.size(); ++i) {
    		if (warriors[i] == warrior) {
          if (warriors.size() == 0) {   //NEED SPECIAL condition for when size is one. Can't use iterators yet here
            warriors[i] = warriors[0];
          }
    			while (i+1 < warriors.size()) {	//delete warrior from vector of unemployed warriors
    				warriors[i] = warriors[i+1];
            ++i;
    			}
    			warriors.pop_back();
    			return;
    		}
    	}
    } else {
      cout << "Noble is dead and can't hire!\n";
      return;
    }

  } else if ("Fire" == firstWord) { //remove the warrior from noble's army
    string nobleName, warriorName;
    stream >> nobleName >> warriorName; //check for errors here
    Noble* noble = nullptr;				//hold a temporary pointer to find each object
    Warrior* warrior = nullptr;
    for (size_t i = 0; i < nobles.size(); ++i) {	//find noble pointer
    	if (nobleName == nobles[i]->getName()) {
    		noble = nobles[i];
    		break;
    	}
    }
    if (noble == nullptr) {
    	cout << "Noble does not exist!\n";
    	return;
    }
    for (size_t i = 0; i < noble->getArmy().size(); ++i) {	//find warrior pointer
    	if (warriorName == noble->getArmy()[i]->getName()) {
    		warrior = noble->getArmy()[i];
    		break;
    	}
    }
    if (warrior == nullptr) {
    	cout << "Warrior does not exist in noble's army!\n";
    	return;
    }
    if (noble->fire(*warrior)) {		//returns true if successfully deleted from noble's army.
    	warriors.push_back(warrior);	//add warrior into unemployed list
    	return;
    } else {
    	cout << "Noble is dead and can't fire!\n";
    	return;
    }

  } else if ("Status" == firstWord) {
    cout << "Status\n======\nNobles:\n";
    for (Noble* noble: nobles) {
      noble->display();
    }
    cout << "Unemployed Warriors:\n";
    if (warriors.size() == 0) {     //special case if no unemployed warriors
      cout << "NONE\n";
    }
    for (Warrior* warrior: warriors) {
      warrior->display();
    }
  } else if ("Battle" == firstWord) {
    string noble1, noble2;
    stream >> noble1 >> noble2;
    Noble* opponent1 = nullptr;         //make two pointers to hold to noble object
    Noble* opponent2 = nullptr;
    for (Noble* noble: nobles) {
      if (noble1 == noble->getName()) {
        opponent1 = noble;
      } else if (noble2 == noble->getName()) {
        opponent2 = noble;
      }
    }
    if (opponent1 == nullptr) {
      cout << noble1 << " does not exist!\n";
      return;
    } else if (opponent2 == nullptr){
    	cout << noble2 << " does not exist!\n";
    } else {
      opponent1->battle(opponent2);
    }
  } else if ("Clear" == firstWord) {
  	warriors.clear();		//clear will call destructor of each item in vector
  	nobles.clear();
  } else {
    cout << "Not a valid option!\n";
    return;
  }
}

int main() {
  ifstream ifs("nobleWarriors.txt");
  if (!ifs) {
    std::cerr << "Could not open file\n";
    exit(1);
  }
  vector<Noble*> nobles;
  vector<Warrior*> warriors;
  while (ifs.peek() != EOF) {
    chooseOption(ifs, warriors, nobles);
  }
  ifs.close();

}
