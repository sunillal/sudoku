/* Author: Sunil Lal
 * lal.sunil@gmail.com
 * This program inputs a CSV file containing sudoku puzzle and outputs the solved puzzle. The input file should be passed as an argument to this program on the command line. The input filename is prefixed with the string "solved" to create the output filename.
 
    compile: g++ -o sudoku main.cpp Sudoku.cpp
    run (example): ./sudoku puzzleFile.csv
    output (if successful) is then stored in solvedpuzzleFile.csv
 */

#include "Sudoku.h"


int main(int argc, char**argv){

	Sudoku puzzleSolver;
    char outputfile[LIMIT] = "solved";
    
    if (argc <= 1)
        cout<<"\nUsage: "<<argv[0]<<" puzzleFile.csv\n";
        
    else if (puzzleSolver.readPuzzleFile(argv[1])){
        if (puzzleSolver.solveSudoku()){
            puzzleSolver.printGrid(strcat(outputfile,argv[1]));
            cout<<"\nPuzzle solved. Solution is saved in "<<outputfile<<endl;
        }
        else
            cout<<"\nSolution not found\n";
    }
		
	return 0;
	
}








