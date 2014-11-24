Sudoku puzzle solver
======

This program inputs a CSV file containing an unsolved sudoku puzzle with 0's representing blanks and outputs the solved puzzle. 
The input file should be passed as an argument to this program on the command line. 
The input filename is prefixed with the string "solved" to create the output filename.
 
    compile: g++ -o sudoku main.cpp Sudoku.cpp
    run (example): ./sudoku puzzleFile.csv
    output (if successful) is then stored in solvedpuzzleFile.csv
    

Sample puzzle files (easyPuzzle.csv & hardpuzzle.csv) are also provided.
For instance, the input CSV file representing an unsolved sudoku puzzle can look like the following:

    0,3,5,2,9,0,8,6,4
    0,8,2,4,1,0,7,0,3
    7,6,4,3,8,0,0,9,0
    2,1,8,7,3,9,0,4,0
    0,0,0,8,0,4,2,3,0
    0,4,3,0,5,2,9,7,0
    4,0,6,5,7,1,0,0,9
    3,5,9,0,2,8,4,1,7
    8,0,0,9,0,0,5,2,6

The corresponding solved puzzle is output as:

    1,3,5,2,9,7,8,6,4
    9,8,2,4,1,6,7,5,3
    7,6,4,3,8,5,1,9,2
    2,1,8,7,3,9,6,4,5
    5,9,7,8,6,4,2,3,1
    6,4,3,1,5,2,9,7,8
    4,2,6,5,7,1,3,8,9
    3,5,9,6,2,8,4,1,7
    8,7,1,9,4,3,5,2,6

##Approach
 The Sudoku class solves a given sudoku puzzle by applying depth first search with backtracking on the list of options available for the empty squares to be filled. 
 Traversal down the search space relies on simple heuristics which consider squares with less options as more promising.
 
 Peter Norvig provides an excellent discourse on solving sudoku puzzles (http://norvig.com/sudoku.html)
 
 


