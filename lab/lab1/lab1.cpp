/*
Max Kim
Lab C
Lab 1
REQUIRES C++11 TO RUN
Shows the Conway's game of life by rotating between two grids. 
The program makes a copy of the existing grid using a vector full of 
vectors of booleans. False is dead, true is alive. Keep two grids. One is the actual and the
other is the grid that is the same size full of false.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//returns the number of rows from the input file
int find_row(std::ifstream& stream) {
	int number = 0;
	std::string line;
	while (getline(stream, line)) {
		number += 1;
	}
	stream.clear();
	stream.seekg(0); //reset stream back to zero
	return number+1;
}

//returns the number of columns from the input file
int find_column(std::ifstream& stream) {
	int number = 0;
	std::string first_line;
	getline(stream, first_line);
	for (char c : first_line) {
		number += 1;
	}
	stream.clear();
	stream.seekg(0); //reset stream back to zero
	return number+1; 
}

//initializes the vector grid with vectors of bool, each row and column holding true or false.
void initialize_grid(std::vector<std::vector<bool>>& grid, int row, int column, std::ifstream& stream) { 
	for (int i=0; i < row; ++i) {	//initialize a vector row * column full of false
		std::vector <bool> list;
		for (int j=0; j < column; ++j) {
			list.push_back(false);
		}
		grid.push_back(list);
	}
	//fill in the true parts *
	std::string line;
	int row_txt = 0;
	int column_txt = 0;
	while (getline(stream, line)) {
		for (char c : line) {
			if (('*' == c)) {
				grid[row_txt+1][column_txt+1] = true;
			}
			column_txt += 1;
		}
		row_txt += 1;
		column_txt = 0;
	}
	stream.clear();
	stream.seekg(0);
}

//makes a grid with the same size, but full of false (dead cells)
void create_empty_grid(const std::vector<std::vector<bool>>& grid, std::vector<std::vector<bool>>& next_grid) {
	//clear the next grid
	next_grid.clear();
	for (size_t i=0; i < grid.size(); ++i) {	//initialize a vector row * column full of false
		std::vector <bool> list;
		for (int j=0; j < grid[i].size(); ++j) {
			list.push_back(false);
		}
		next_grid.push_back(list);
	}
}

//saves the grid with the updated values. Move the updated grid back into the original grid.
void copy_over(std::vector<std::vector<bool>>& grid, const std::vector<std::vector<bool>>& next_grid) {
	grid.clear();	//erase old grid
	for (std::vector<bool> list : next_grid) {
		grid.push_back(list);
	}
}

//return the number of cells alive in a cell
int number_of_alive(const std::vector<std::vector<bool>>& grid, const int row, const int column) {
	int counter = 0;
	if (grid[row][column] == true) { //subtract yourself if you are alive
		counter -= 1;
	}
	for (int left=row-1; left<row+2; ++left) {
		for (int right=column-1; right<column+2; ++right) {
			if ((grid[left][right] == true)) {
				counter += 1;
			}
		}
	}
	return counter;
}

//runs one generation step. The four rules. 
void run_generation(const std::vector<std::vector<bool>>& grid, std::vector<std::vector<bool>>& next_grid) {
	for (size_t i=1; i<grid.size()-1; ++i) {	//start at 1 to avoid boundary errors
		for (size_t j=1; j<grid[i].size()-1; ++j) {		//ACCOUNT FOR BORDERS 1 to size-1
			int number_alive = number_of_alive(grid, i, j);
			if (grid[i][j] == true) {
				if ((number_alive<2) || (number_alive>3)) { //dies
					next_grid[i][j] = false;
				} else { //survives next generation
					next_grid[i][j] = true;
				}
			} else {
				if (number_alive == 3) { //becomes alive
					next_grid[i][j] = true;
				} else {	//stays dead
					next_grid[i][j] = false;
				}
			}
		}
	}
}

//prints out the grid, converting true into * (alive cells) and false into ' ' (dead cells)
void print_generation(const std::vector<std::vector<bool>>& grid) {
	for (std::vector<bool> list : grid) {
		for (bool c: list) {
			if (c) {
				std::cout << '*';
			} else {
				std::cout << ' ';
			}
		}
		std::cout << std::endl;
	}
}

int main() {
	std::ifstream ifs("life.txt");
	if (!ifs) {
		std::cerr << "Could not open file.\n";
		exit(1);
	}

	//do the actual initialization first
	std::vector<std::vector<bool>> grid;
	std::vector<std::vector<bool>> next_grid;
	int row = find_row(ifs);
	int column = find_column(ifs);
	initialize_grid(grid, row, column, ifs);
	create_empty_grid(grid, next_grid);
	std::cout<< "This is initial generation" << std::endl;
	print_generation(grid);

	//show the next 10 generations
	for (int i=0; i < 10; ++i) { 
		run_generation(grid, next_grid);
		std::cout << "This is generation " << i+1 << std::endl;
		print_generation(next_grid);
		copy_over(grid, next_grid);
		create_empty_grid(grid, next_grid);
	} 		

	ifs.close();
	return 0;
}
