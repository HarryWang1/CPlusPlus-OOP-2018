/*
Max Kim
Lab C 
a program that models an arena. There are warriors who have strengths. They battle each other and lose strength. Different outputs based on who wins, who loses, and if they both die. 
No classes allowed, the goal of this assignment is to use struct. Make two struct - one called arena and warrior. Warrior handles the players. Arena handles the battles, status output,
and such. Requires atleast c++11 to run. 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Warrior {
	std::string name;
	int strength;

	void loseStrength(const int points) {
		strength = strength-points;
	}
};

struct Arena {
	std::vector <Warrior> players;

	void printStatus() {
		std::cout << "There are " << players.size() << " Warriors\n";
		for (const Warrior& player : players) {
			std::cout << "Warrior: " << player.name << ", strength: " << player.strength << "\n";
		}
	}
	void battle(Warrior& player1, Warrior& player2) {
		std::cout << player1.name << " battles " << player2.name << "\n";
		if (player1.strength == player2.strength) {
			if ((player1.strength == 0) && (player2.strength == 0)) {	//both players are dead.
				std::cout << "Oh, NO! They're both dead! Yuck!\n";
			} else {													//both players kill themselves
				std::cout << "Mutual Annihilation: " << player1.name << " and " << player2.name << " die at each other's hands\n";
				player1.loseStrength(player1.strength);					//decrease strength for both players
				player2.loseStrength(player2.strength);
			}
		} else {	//one player wins over the other
			if (player1.strength > player2.strength) {		//TODO: find a way to avoid repeating this check
				if (player2.strength == 0) {	//losing player was already dead
					std::cout << "He's dead, " << player1.name << "\n";
				} else {	//both players fought
					std::cout << player1.name << " defeats " << player2.name << "\n";
					player1.loseStrength(player2.strength);		//decrease strength for both players
					player2.loseStrength(player2.strength);
				}
			} else {
				if (player1.strength == 0) {	//losing player was already dead
					std::cout << "He's dead, " << player2.name << "\n";
				} else {	//both players fought
					std::cout << player2.name << " defeats " << player1.name << "\n";
					player2.loseStrength(player1.strength);		//decrease strength for both players
					player1.loseStrength(player1.strength);
				}
			}
		}
	}
};

int main() {
	std::ifstream ifs("warriors.txt");
	if (!ifs) {
		std::cerr << "Could not open file.\n";
		exit(1);
	}
	
}