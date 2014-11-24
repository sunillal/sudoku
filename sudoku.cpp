/* Author: Sunil Lal
 * lal.sunil@gmail.com
 
 The Sudoku class solves a given sudoku puzzle by applying depth first search with backtracking on the list of options 
 available for the empty squares to be filled. Traversal down the search space relies on simple heuristics which consider squares with less options as more promising.
 */

#include "Sudoku.h"

Sudoku::Sudoku(){
    
    //intialize all squares in the grid to unassigned state
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++)
            grid[i][j].value = 0;
}

//Read and validate the input from the supplied puzzle file
bool Sudoku::readPuzzleFile(char *filename){

	int value, row = 0, col = 0;
	char line[LIMIT];
	char *token;

    ifstream infile;
	infile.open(filename,ios::in);

	if(infile.fail()){
		cout<<"\nError accessing the input sudoku puzzle file.";
		cout<<"\nPlease enter a valid filename as an argument to this program on the command line\n";
		
		return false;
	}
	
    while(!infile.fail() && !infile.eof() && row < SIZE){
		
		infile.getline(line, LIMIT);
		token = strtok(line," ,");
		while (token != NULL && col < SIZE){
            //Ignore invalid inputs such as non-numeric characters and digits outside 0-9 range
			if (isdigit(token[0])){
				value = atoi(token);
				if (value >= 0 && value <= 9){
					grid[row][col].value = value;
                    if(value != 0 && !checkSquareValidity(row,col)){ //makesure the input puzzle is valid to begin with
                        cout<<"\nInvalid puzzle. Conflicting value detected at position "<<(row+1)<<" "<<(col+1)<<endl;
                        return false;
                    }
                }
            }
            
            token = strtok(NULL, " ,");
            col++;
		}
		
		col = 0;
		row++;
	}
    
    determineLegalMoves();
    
    return true;
    
}


bool Sudoku::solveSudoku(){

    int row, col;
    
    
    if (solutionFound())  //puzzle is solved when all sqaures are filled with no violations
        return true;
    else if (getNextSquare(row,col)){ //find a square with least number of options to be filled
        
        //cycle through all the options for this square
        for (int i = 0; i < grid[row][col].options.size(); i++){
            grid[row][col].value = grid[row][col].options[i];  //temporarily assign one of the options to the grid
            determineLegalMoves();  //work out the resulting options for the remaining empty squares
            
            if (solveSudoku())  //solve the resulting grid
                return true;
        
            grid[row][col].value = 0;  //unlucky, we revert to the previous grid state
        }
    }
        
    return false;
}


bool Sudoku::solutionFound(){
    

    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            
            //check if the squares are still empty
            if (grid[i][j].value == 0)
                return false;
            
            //check violations with row-wise, column-wise and box-wise neighbours
            if (!checkSquareValidity(i,j))
                return false;
            
        }
    }
    
    return true;
   
}

bool Sudoku::checkSquareValidity(int row, int col){
    
    int startRow, startCol, currNeighbourRow, currNeighbourCol;
    
    //marks the starting position of the 3x3 box
    startRow = row - row%BOX_SIZE;
    startCol = col - col%BOX_SIZE;
    
    for (int i = 0; i < SIZE; i++){
        
        //check violation with column-wise neighbours
        if ((i != row) && (grid[row][col].value == grid[i][col].value))
            return false;
        
        //check violation with row-wise neighbours
        if ((i != col) && (grid[row][col].value == grid[row][i].value))
            return false;
   
        //check violation with 3x3 box neighbours
        currNeighbourRow = startRow + i/BOX_SIZE;
        currNeighbourCol = startCol + i%BOX_SIZE;
        
        if( !((currNeighbourRow == row) && (currNeighbourCol == col)) && (grid[row][col].value == grid[currNeighbourRow][currNeighbourCol].value))
            return false;

    }
    
    return true;
    
}

void Sudoku::determineLegalMoves(){
    
    
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            
            //if a square is empty, we check all possible options which result in a valid grid
            if (grid[i][j].value == 0){
                grid[i][j].options.clear();
                for (int option = 1; option <= SIZE; option++){
                    grid[i][j].value = option;
                    if (checkSquareValidity(i,j))
                        grid[i][j].options.push_back(option); //populate the list of valid options for the empty square
                    
                }
                grid[i][j].value = 0;
                
            }
    
}


bool Sudoku::getNextSquare(int &rowNum, int &colNum){
    
    unsigned long min = SIZE + 1;
    bool found = false;
    
    //for all the empty squares in the grid, find the one which has the least number of options to be filled
    for(int i = 0; i < SIZE; i++)
        for(int j = 0; j < SIZE; j++)
            if (grid[i][j].value == 0 && grid[i][j].options.size() < min){
        
                rowNum = i;
                colNum = j;
                min = grid[i][j].options.size();
                found = true;
            }

    return found;
}

//outputs the solved puzzle as a csv file
void Sudoku::printGrid(char *filename){
    
    ofstream outfile;
    
    outfile.open(filename, ios::out);
    
    if (outfile.fail())
        cout<<"\nError opening output file "<<filename<<endl;
    else {
        for (int i = 0; i < SIZE; i++){
            for (int j = 0; j < SIZE; j++){
                outfile<<grid[i][j].value;
            
                if (j == SIZE - 1)
                    outfile<<endl;
                else
                    outfile<<',';
       
            }

        }
    }
}




















