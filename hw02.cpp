/*
Max Kim
Lab C 
A program that models an arena with warriors who have only one characteristic caleld "strength", which determines who wins in a 1v1 battle against each other. The
program simulates this by making the warriors fight and lose strength. Rules: No classes. Program relies on two structs - Arena and Warrior. The Warrior struct
handles the players. Arena handles the battles, printing out status, and managing warriors. Requires atleast c++11 to run. 
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

struct Arena {		//handles the battles, printing the status, and holds the warriors. 
	std::vector <Warrior> players;		//hold a vector of all warriors

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

void chooseOption(std::ifstream& stream, Arena& arena) {
	std::string firstWord;
	stream >> firstWord;
	if ("Warrior" == firstWord) {		//create a warrior and add it into arena's vector 
		std::string nameString;
		int strengthNumber;
		stream >> nameString >> strengthNumber;
		Warrior player;
		player.name = nameString;
		player.strength = strengthNumber;
		arena.players.push_back(player);
	} else if ("Battle" == firstWord) {		//grab warriors and fight
		std::string firstPlayer;
		std::string secondPlayer;
		stream >> firstPlayer >> secondPlayer;
		//have to find the actual object that has the same name. use index to make it easier.
		int firstPlayerIndex;
		int secondPlayerIndex;
		for (size_t i = 0; i < arena.players.size(); ++i) {
			if (arena.players[i].name == firstPlayer) {
				firstPlayerIndex = i;
			} else if (arena.players[i].name == secondPlayer) {
				secondPlayerIndex = i;
			}
		}
		arena.battle(arena.players[firstPlayerIndex], arena.players[secondPlayerIndex]);
	} else if ("Status" == firstWord) {
		arena.printStatus();
	}
}

int main() {
	std::ifstream ifs("warriors.txt");
	if (!ifs) {
		std::cerr << "Could not open file.\n";
		exit(1);
	}

	Arena arena; 	
	while (ifs.peek() != EOF) {		//while not at the end of file
		chooseOption(ifs, arena);
	}
}
