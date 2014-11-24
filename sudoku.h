/* Author: Sunil Lal
 * lal.sunil@gmail.com
 
 The Sudoku class solves a given sudoku puzzle by applying depth first search with backtracking on the list of options
 available for the empty squares to be filled. Traversal down the search space relies on simple heuristics which consider
 squares with less options as more promising.
 */

#include <iostream>
#include <cstring>
#include <fstream>
#include <ctype.h>
#include <vector>

const int SIZE = 9; //size of grid is 9x9
const int BOX_SIZE = 3; //size of a major box within the grid is 3x3
const int LIMIT = 256; //max limit of number of characters including whitespace in the input file

using namespace std;

#ifndef SUDOKU_H
#define SUDOKU_H

//square represents an individual cell within the sudoku grid
struct square{
    
    int value;  //values range from 1 - 9; 0 means the square is empty
    vector<int> options; //range of values that can be legally filled in an empty square
};

class Sudoku{
    
public:
    
    Sudoku();
    bool readPuzzleFile(char *);
    bool solveSudoku();
    void printGrid(char *);
    
    
private:
    
    square grid[SIZE][SIZE];
    
    bool solutionFound();
    bool checkSquareValidity(int, int);
    void determineLegalMoves();
    bool getNextSquare(int &, int&);
    
    
};

#endif






