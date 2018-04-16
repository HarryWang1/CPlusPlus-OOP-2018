/*
MAX KIM
LAB C
9 February 2018
Minesweeper game.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

class Minesweeper {
public:
    Minesweeper(int row, int column) {
        srand (time(NULL));
        for (int i=0; i < row+2; i++) {     //row size is increased by extras
            std::vector<int> line;  
            if ((i==0) || (i==row+1)) {   //extra rows at top/bottom that does not have bomb
                for (int j=0; j < column+2; j++) {   //column size is increased by extras
                    line.push_back(-2);
                }
                numOfBombs.push_back(line);
            } else {
                for (int j=0; j < column+2; j++) {      //column size is increased by extras
                    if ((j==0) || (j==column+1)) {      //left and right columns are always false b/c extras
                        line.push_back(-2);
                    }
                    else if (rand() % 11 == 0) {      //make bomb for 10% of the time
                        line.push_back(-1);
                    } else {
                        line.push_back(0);
                    }
                }
                numOfBombs.push_back(line);   //add to visible bools 
            }
        }
        //go through and count the number of bombs for each tile
        for (int i=1; i < row+1; i++) {    //avoid extras row(top/bottom) and column (left/right)
            for (int j=1; j < column+1; j++) {
                if (numOfBombs[i][j] == -1) {   //bomb. continue.
                    continue;               //skip to next index
                }
                int countBomb = 0;          //initialize to zero bombs
                for (int row=i-1; row<i+2; row++) {       //count number of bombs around
                    for (int column=j-1; column<j+2; column++) {
                        if ((row==i) && (column==j)) {      //skip what you are looking at
                            continue;
                        } 
                        if (numOfBombs[row][column] == -1) {
                            countBomb++;
                        }
                    }
                }
                numOfBombs[i][j] = countBomb;
            }   
        }
        //initialize visibleBools with zeros with extra column/rows to match index with numOfBombs
        for (int i=0; i < row+2; i++) {
            std::vector<bool> line;
            for (int j=0; j < column+2; j++) {
                line.push_back(false);
            }
            visibleBools.push_back(line);
        }
        for (std::vector<bool> bools: visibleBools) {
            for (bool t: bools) {
                std::cout << t << " | ";
            }
            std::cout << "\n";
        } 
        std::cout << "##################\n";
        for (std::vector<int> test: numOfBombs) {
            for (int t: test) {
                std::cout << t << " | ";
            }
            std::cout << "\n";
        }
        
    }
    //assume that top left coordinate is (1, 1)
    bool validRow(int rowNumber) const {      //return true if within game board's row range
        if ((rowNumber>=1) && (rowNumber <= visibleBools.size())) {   
            return true;
        } else {
            return false;
        }
    }
    bool validColumn(int columnNumber) const {    //return true if within game board's column range
        if ((columnNumber>=1) && (columnNumber <= visibleBools[0].size())) {   
            return true;
        } else {
            return false;
        }
    }
    bool isVisible(int row, int column) const {   //assumes that top left is (1, 1)
        //account for extra rows(top/bottom) and columns(left/right)
        return visibleBools[row][column];
    }
    //assume top left is (1, 1)
    bool play(int row, int column) {    //returns false if explode. change boards as you play. 
        if (numOfBombs[row][column] == -1) {  //account for extra row/column
            return false;
        } else if (numOfBombs[row][column] == 0) {  //no nearby bombs. start exploring
            std::vector<std::vector<int>> stack;
            std::vector<int> index;             //a vector of ints that holds row and column in index 0 and 1
            index.push_back(row);             
            index.push_back(column);
            stack.push_back(index);             //push the first one to the stack
            while (stack.size() != 0) {
                std::vector<int> current = stack.back();
                stack.pop_back();
                int r = current[0];           //account for adding one to fit grid
                int c = current[1];
                //want to take out an extra off by 1. Looking in a square.
                if ((r >= visibleBools.size()) || (c >= visibleBools[0].size())) {  //in case go out of border  
                    continue;   
                }
                if (visibleBools[r][c] == true) {     //if visible already, skip
                    continue;
                }
                visibleBools[r][c] = true;        //process current
                //if the neighbors have no nearby bombs also, add to stack.
                for (int i=r-1; i<r+2; ++i) {
                    for (int j=c-1; j<c+2; ++j) {
                        if ((i==r) && (j==c)) {     //dont look at center you are when looking in 3x3 around center
                            continue;   
                        }
                        if (numOfBombs[i][j] == -2) {   //ignore the borders
                            continue;
                        }
                        if (numOfBombs[i][j] == 0) {    //if another no-nearby-bomb, add to stack
                            std::vector<int> index;
                            index.push_back(i);
                            index.push_back(j);
                            stack.push_back(index);
                        } else {                    //just a number. display it. 
                            visibleBools[i][j] = true;
                        }
                    }
                }
            }
            return true;
        } else {    //nearby bombs. change state of board.
            visibleBools[row][column] = true;
            return true;
        }
    }
    bool done() const {   //returns true if the game is over
        for (int i=1; i<visibleBools.size()-1; i++) {
            for (int j=1; j<visibleBools[0].size()-1; j++) {
                if (visibleBools[i][j] == true) {   //if visible, continue
                    continue;
                } else {        //if not visible and not a bomb test using corresponding index with numofbombs.
                    if (numOfBombs[i][j] != -1) {
                        return false;
                    }
                }
            }
        }
        return true;    //either all are visible or no more bombs left
    }
    void display (bool bombStatus) const {
        if (bombStatus == true) {       //show everything
            for (std::vector<int> test: numOfBombs) {
                for (int t: test) {
                    std::cout << t << "   ";
                }
            std::cout << "\n";
            }
        } else {
            for (int i=1; i<visibleBools.size()-1; i++) {   //only show board if number and is visible
                for (int j=1; j<visibleBools[0].size()-1; j++) {  //account for extra row/columns
                    if (visibleBools[i][j] == true) {
                        std::cout << numOfBombs[i][j] << "   ";
                    } else {
                        std::cout << " _ ";
                    }
                }
                std::cout << "\n";
            }
        }
    }
private:
    std::vector<std::vector<int>> numOfBombs;
    std::vector<std::vector<bool>> visibleBools;
};

int main() {
    int row, column;
    std::cout << "What is the row size of game?\n";
    std::cin >> row;
    std::cout << "What is the column size of game?\n";
    std::cin >> column;
    Minesweeper sweeper(row, column);
    /*
    std::cout << "testing out a valid row\n";
    std::cin >> row;
    std::cout << "testing out a valid column\n";
    std::cin >> column;
    std::cout << sweeper.validRow(row) << ' ' << sweeper.validColumn(column);
    std::cout << "testing is visible, type row and column separated by space\n";
    std::cin >> row >> column;
    std::cout << sweeper.isVisible(row, column);
    */

    // Continue until only invisible cells are bombs

    while (!sweeper.done()) {   
        sweeper.display(false); // display board without bombs

        int row_sel = -1, col_sel = -1;
        while (row_sel == -1) {
            // Get a valid move
            int r, c;
            std::cout << "row? ";
            std::cin >> r;
            if (!sweeper.validRow(r)) {
                std::cout << "Row out of bounds\n";
                continue;
            }
            std::cout << "col? ";
            std::cin >> c;
            if (!sweeper.validRow(c)) {
                std::cout << "Column out of bounds\n";
                continue;
            }
            if (sweeper.isVisible(r,c)) {
                std::cout << "Square already visible\n";
                continue;
            }
            row_sel = r;
            col_sel = c;
        }
        // Set selected square to be visible. May effect other cells.
        if (!sweeper.play(row_sel,col_sel)) {
            std::cout << "Sorry, you died..\n";
            sweeper.display(true); // Final board with bombs shown
            std::cout << "type a number to exit\n";
            int uniquec;
            std::cin >> uniquec;
            exit(0);
        }
    }
    // Ah! All invisible cells are bombs, so you won!
    std::cout << "You won!!!!\n";
    sweeper.display(true); // Final board with bombs shown
    std::cout << "press a number to exit\n";
    int uniquec;
    std::cin >> uniquec;
}