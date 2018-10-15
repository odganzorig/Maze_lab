// maze.cpp -- Implementation of Maze Class
// CS 223, Lab 6
//
// Name: Od Ganzorig
// Date: 03/18/2018

/*
*  INSTANCE VARIABLES
*     square ** arr;  // pointer to a 2-dimensional dynamic array of squares
*     int numRows;    // number of rows in the maze
*     int numCols;    // number of columns in the maze
*     square * start; // pointer to the start square
*     square * exit;  // pointer to the exit square
*
*  CLASS INVARIANTS
*     1. arr[i][j] is the maze square in ROW i and COLUMN j.
*     2. Each maze has exactly one START square and one EXIT square.
*/

#include <stdexcept>    // provides standard exceptions
#include <cassert>      // provides assert
#include <sstream>      // provides stringstreams
#include <iostream>
#include "maze.h"

using namespace std;

namespace mazelab
{

//
//  constructor -- initializes a maze from an input stream
//  Input: `in` is a stream of whitespace-separated tokens, and there
//     is at least one whitespace character after the last token.
//  Precondition:  The first two tokens of `in` can be read as positive
//     integers (they represent the rows (R) and columns (C) for the
//     dimensions of the maze).
//  Precondition:  There are R*C tokens to be extracted following the maze
//     dimensions, and each of these is a digit in the range 0 to 3.
//  Precondition:  There is exactly one start square and one exit square.
//  Postcondition: `arr` points to the R x C array of maze squares.
//  Postcondition: `numRows` and `numCols` have been properly initialized.
//  Postcondition: `start` points to the start square and `exit` points to 
//     the exit square.
//  Exception: Throws domain_error if there is an error in the format of 
//     the maze being read from the input stream.
//  Exception: Throws domain_error if any of the preconditions are violated.
//
maze::maze(std::istream &in)
{
	int status;
	in >> numRows >> numCols;
	if (numRows < 1)

        throw domain_error("Wrong row number!");
    if (numCols < 1 )

        throw domain_error("Wrong column number!");
	arr = new square* [numRows];
	for (int row = 0; row < numRows; row++)
    {
        arr[row] = new square[numCols];
    }
    int start_acc = 0;
    int end_acc = 0;
    for (int row = 0; row < numRows; row++)
    {
       	for (int col = 0; col < numCols; col++)
        {
            in >> status;
            arr[row][col] = square(status, row, col);
            if(status == square::START)
            {
            	start = &arr[row][col];
            	start_acc++;
            }
            if(status == square::EXIT)
            {
            	exit = &arr[row][col];
            	end_acc++;
            }
        }
         
    }   
    if(start_acc == 0 || start_acc > 1)
    	throw domain_error("Invalid number of start square!");
    if(end_acc == 0 || end_acc > 1)
    	throw domain_error("Invalid number of end square!");
}



//
// Destructor
//
maze::~maze()
{
	for (int row = 0; row < numRows; row++)
        {
        	delete [] arr[row];
        }
        delete [] arr;
}


// *** Getters *** //

//
// getNumRows
//  Postcondition:  Return value the number of rows in the maze.
//
int maze::getNumRows() const
{
	return numRows;

}


//
// getNumCols
//  Postcondition:  Return value the number of columns in the maze.
//
int maze::getNumCols() const
{
	return numCols;

}


//
// getStart
//  Postcondition:  Return value is a pointer to the start
//     square of the maze.
//
square* maze::getStart() const
{
	return start;

}


//
// getExit
//  Postcondition:  Return value is a pointer to the exit
//     square of the maze.
//
square* maze::getExit() const
{
	return exit;

}


//
// get -- get a pointer to a square by row and column indices
//  Precondition:  `i` is in range 0 through numRows - 1.
//  Precondition:  `j` is in range 0 through numCols - 1.
//  Postcondition:  Return value is a pointer to the square in
//     row i and column j of this maze.
//  Exception: Throws out_of_range if `i` is invalid.
//  Exception: Throws out_of_range if `j` is invalid.
//
square* maze::get(int i, int j) const
{
	if (i < 0 || i >= numRows) 
	 	throw std::out_of_range("index is out of range");
	if (j < 0 || j >= numCols) 
	 	throw std::out_of_range("index is out of range");
	square* sqr = &arr[i][j];
	return sqr;

}


//
// getSquare -- get a reference to a square by row and column indices
//  Precondition:  `i` is in range 0 through numRows - 1.
//  Precondition:  `j` is in range 0 through numCols - 1.
//  Postcondition:  Return value is a reference to the square in
//     row i and column j of this maze.
//  Exception: Throws invalid_argument if `i` is invalid.
//  Exception: Throws invalid_argument if `j` is invalid.
//
square& maze::getSquare(int i, int j) const
{
	if (i < 0 || i >= numRows) 
	 	throw std::out_of_range("index is out of range");
	if (j < 0 || j >= numCols) 
	 	throw std::out_of_range("index is out of range");
	return arr[i][j];

}


// *** Other Accessors *** //

//
// toString
//  Postcondition: Return value is a string for printing the text version
//     of the maze, with a '\n' at the very front, a single space after each
//     square's status symbol, and a '\n' after each row.
//  EXAMPLE:  If the maze was constructed from a stream holding the following
//     information:  3 4   3 3 3 3  1 0 0 3  0 2 3 3
//     then the printed version of the maze would look as follows:
//         _ _ _ _
//         S # # _
//         # E _ _
//
std::string maze::toString() const
{
	stringstream temp;
	temp << endl;
    for (int row = 0; row < numRows; row++)
        {
        	for (int col = 0; col < numCols; col++)
            {
            	
    			temp << arr[row][col] << " ";
    			
    		}
    		temp << endl;
    	}
	return temp.str();

}


//
// getNeighbors
//  Precondition:  `sq` is a square in this maze.
//  Postcondition:  Return value is a vector of pointers to the squares
//     in this maze that are neighbors of `sq`, where the vector is filled
//     in this order:  North (up one), East (right one), South (down one),
//     and West (left one).
//  Note:  If there is NO neighbor in a given direction, the vector will
//     have size less than 4.  Corner squares have just two neighbors, and
//     side squares have three neighbors.
//
//  EXAMPLE:  In the maze below
//             _ _ _ _
//             S # # _
//             # E _ _
//
//     if sq is the start square (position [1,0]) then the return value will
//     be a vector of length 3 storing:
//        - a pointer to the [0,0] square
//        - followed by a pointer to the [1,1] square
//        - followed by a pointer to the [2,0] square
//
std::vector<square *> maze::getNeighbors(square sq) const
{
	vector<square*> neighbors;
	if (sq.getRow() > 0)
	{
		neighbors.push_back(&arr[sq.getRow()-1][sq.getCol()]);
	}
	if (sq.getCol() < numCols - 1)
	{
		neighbors.push_back(&arr[sq.getRow()][sq.getCol()+1]);
	}
	if (sq.getRow() < numRows - 1)
	{
		neighbors.push_back(get(sq.getRow()+1, sq.getCol()));
	}
	if (sq.getCol() > 0)
	{
		neighbors.push_back(get(sq.getRow(), sq.getCol()-1));
	}
	return neighbors;
}


// *** Modifiers *** //

//
// reset - erase all "markings" on maze squares
//  Postcondition:  All squares in the maze with status WORK_LIST,
//     EXPLORED, or SOLUTION_PATH now have status UNVISITED.
//  Postcondition:  The value of `prev` for all squares is NULL.
//
void maze::reset()
{
	for (int row = 0; row < numRows; row++)
        {
        	for (int col = 0; col < numCols; col++)
            {
            	arr[row][col].reset();
            	
            }
        }	

}


//
// output stream operator
//  Postcondition:  The string representation of this maze is put into
//     `out`, and `out` is returned to allow for chaining of output.
//
ostream& operator<< (std::ostream &out, const maze &maze)
{
    out << maze.toString();
    return out;
}


} // End namespace
