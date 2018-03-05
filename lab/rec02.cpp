/*
Max Kim
Lab C
2 February 2018
A program that reads a file of hydrocarbon names and their formulas and stores them. It will print out
these formulas in an ascending order.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Hydrocarbon {
	std::string name;
	int CNumber;	//carbon and hydrogen number of atoms
	int HNumber;
};

struct HydrocarbonManager {		//outer struct that handles the adding, printing, and sorting of the vector of all the formulas
	std::vector <Hydrocarbon> listOfFormulas;

	void printList() {
		for (const Hydrocarbon& item : listOfFormulas) {
			std::cout << 'C' << item.CNumber << 'H' << item.HNumber << " " << item.name << "\n";
		}
	}

	void insertHydrocarbon(const Hydrocarbon& item) {
		//check if already exists
		for (Hydrocarbon& existingItem: listOfFormulas) {
			if ((existingItem.CNumber == item.CNumber) && (existingItem.HNumber == item.HNumber)) {
				existingItem.name = existingItem.name + " " + item.name;
				return;
			}
		}
		//not found.
		listOfFormulas.push_back(item);
		sortHydrocarbon();
	} 

	void sortHydrocarbon() {
		//uses insertion sort
		for (int i = 0; i < listOfFormulas.size(); ++i) {
			for (int j = i; j >= 0; --j) {
				if (listOfFormulas[i].CNumber < listOfFormulas[j].CNumber) {
					std::swap(listOfFormulas[j], listOfFormulas[i]);
				}
			}
		}
	}
};

void createHydrocarbon(std::ifstream& stream, HydrocarbonManager& manager) {
	std::string name;
	stream >> name;
	char C;
	char H;
	int cnum;
	int hnum;
	//filter out the 'C' and the "H" to get the number of atoms.
	stream >> C >> cnum >> H >> hnum;
	Hydrocarbon item;
	item.name = name;
	item.CNumber = cnum;
	item.HNumber = hnum;
	manager.insertHydrocarbon(item);
}


int main() {
	std::ifstream ifs("formulas.txt");
	if (!ifs) {
		std::cerr << "Could not open file.\n";
		exit(1);
	}

	HydrocarbonManager manager;
	while (ifs.peek() != EOF) {		//while not at the end of file
		createHydrocarbon(ifs, manager);
	}
	ifs.close();
	manager.printList();
}
