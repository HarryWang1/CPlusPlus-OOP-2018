/*
MAX KIM
LAB C
January 26 2018
A program that decrypts an input file, given a "step" on the first line, and the actual text on the next
line. Assumes that first line is supposed to be last line (as in reversed input). Prints out the
decrypted message at the end. Utilizes a vector full of strings, which are each line from input file. 
Then for each line, decrypt each character, ignoring uppercase, numbers, and whitespaces. 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//convert char to number and subtract steps. OK to have step as copy and singleletter as copy too. 
char decryptchar(char singleLetter, int step) { 
	int digit = singleLetter;
	//reduce steps if it is more than the range of a to z. 25 is # of alphabets.
	while (step > 25) {
		step -= 25;
	}
	if (digit-step >= 97) {	//check if decrypting makes the letter go below 'a', or 97. 
		digit = digit-step;
	} else {	//number is out of range, so subtract remaining number from 'z', or 123. 
		digit = 123 - (step-(digit-97));
	}
	return char (digit);
}

//for each line in the vector of strings, and then for each character, decrypt. 
void decryptstring(std::vector<std::string>& block, const int step) {
	for (std::string& line : block) {
		std::string newLine;
		for (char letter : line) {
			//don't decrypt numbers, uppercase, whitespace.
			if ((std::isupper(letter)) || (std::isdigit(letter)) || (std::isspace(letter)) || ('.' == letter)) { 
				newLine += letter;	
			} else {
				newLine += decryptchar(letter, step);;
			}
		}
		line = newLine;
	}
}

void print_vector(std::vector<std::string>& list) {
	for (size_t i=list.size()-1; ; --i) {
		std::cout << list[i];
		if (i==0) {
			break;
		}
	}
}

int main() {

	std::ifstream ifs("encrypted.txt");
	if (!ifs) {
		std::cerr << "Could not open file.\n";
		exit(1);
	}
	//grab number of steps
	int steps;
	ifs >> steps;
	std::string line;
	getline(ifs, line); //gobble up extra newline character
	std::vector<std::string> lineList; //hold the input string into the vector
	while (getline(ifs, line)) {
		lineList.push_back(line + "\n");
	}

	decryptstring(lineList, steps);
	print_vector(lineList);
	ifs.close();
	return 0;
}


