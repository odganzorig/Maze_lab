// square.cpp -- Implementation of Square Class
// CS 223, Lab 6
//
// Name: Theresa Wilson
// Date: 3-10-2018
//
// REMINDERS:  
//    1) In place of literal integers (i.e., "magic numbers"), use 
//       class constants THROUGHOUT to create readable code. For example, 
//       to ask if the square named `sq` is a wall square, you would write:
//
//          if (sq.getStatus() == square::WALL)
//
//       rather than:
//
//          if (sq.getStatus() == 0)
//
//    2) The value of `status` is always one of the following:
//          0 -- WALL
//          1 -- START 
//          2 -- EXIT
//          3 -- UNVISITED (plain square that has not yet been visited)
//          4 -- WORK_LIST (plain square that is currently on the worklist)
//          5 -- EXPLORED (plain square that has been explored and not on the
//                 solution path, possibly because exploration is still ongoing)
//          6 -- SOLUTION_PATH (plain square that is on the solution path)
//
//    3) The value of `prev` for START and WALL, and UNVISITED squares is NULL.
//

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "square.h"

using namespace std;

namespace mazelab
{

//
//  Default constructor
//  Postcondition: Makes a WALL square located in the upper left corner 
//     of a maze (location [0,0]) with `prev` set to NULL.
//
square::square()
{
    row = 0;
    col = 0;
    status = 0;
    prev = NULL;
}

//
//  Constructor with 3 parameters for status, row, and column
//  Precondition:   WALL <= status_val <= UNVISITED
//  Postcondition:  The new square has status, row, and col values
//     initialized to status_val, row_val, and col_val, respectively.
//  Postcondition:  The `prev` pointer is initialized to NULL.
//  Exception: Throws domain_error if status_val is invalid.
//
square::square(int status_val, int row_val, int col_val)
{
    if (status_val < WALL || status_val > UNVISITED)
        throw domain_error("Given status is invalid.");

    status = status_val;
    row = row_val;
    col = col_val;
    prev = NULL;
}

// *** ACCESSORS *** //

// 
// getStatus
//  Postcondition: Return value is the current status of the square.
//
int square::getStatus() const
{
    return status;
}

// 
// getRow
//  Postcondition: Return value is the row where the square is located.
//
int square::getRow() const
{
    return row;
}

// 
// getCol
//  Postcondition: Return value is the column where the square is located.
//
int square::getCol() const
{
    return col;
}

// 
// getPrev
//  Postcondition: Return value is a pointer to a square.
//
square* square::getPrev() const
{
    return prev;
}

//
// isWall
//  Postcondition:  Return true square is WALL square; otherwise
//     return false.
//
bool square::isWall() const
{
    return status == WALL;
}

//
// isStart
//  Postcondition:  Return true if square is a START square;
//     otherwise, return false.
//
bool square::isStart() const
{
    return status == START;
}

//
// isExit
//  Postcondition:  Return true if square is an EXIT square;
//     otherwise, return false.
//
bool square::isExit() const
{
    return status == EXIT;
}

//
// isPlainSquare
//  Postcondition:  Return true if the square is not a WALL,
//     START, or EXIT square; otherwise, return false.
//
bool square::isPlainSquare() const
{
    return (status != WALL && status != START && status != EXIT);
}

//
// toChar
//  Helper method for printing the maze.
//  Postcondition: Return value is a char representation of the status:
//
//        WALL -> '#'
//        START  -> 'S'
//        EXIT -> 'E'
//        UNVISITED -> '_'
//        WORK_LIST -> '@'
//        EXPLORED -> '.'
//        SOLUTION_PATH -> 'X'
//        any other value -> '?'
//
char square::toChar() const
{
    switch (status)
    {
        case WALL: return '#';
        case START: return 'S';
        case EXIT: return 'E';
        case UNVISITED: return '_';
        case WORK_LIST: return '@';
        case EXPLORED: return '.';
        case SOLUTION_PATH: return 'X';
        default: return '?';
    }
}

//
// toString
//  Postcondition: Return value is a string for reporting the coordinates
//     of the square in the form "[row,col]".
//
//  Example: If the square is in row 5 and column 0, return "[5,0]".
//
string square::toString() const
{
    stringstream temp;
    temp << "[" << row << "," << col << "]";
    return temp.str();
}

// *** MODIFIERS *** //

//
// setStatus
//  Precondition:  This is not a WALL, START, or EXIT square.
//  Precondition:  `new_status` must be a possible status for a plain square.
//  Postcondition: `status` is set to new_status.
//  Exception: Throws domain_error if square status may not be changed.
//  Exception: Throws domain_error if new_status is invalid.
//
void square::setStatus(int new_status)
{
    if (isPlainSquare())
    {
        if (new_status < UNVISITED || new_status > SOLUTION_PATH)
            throw domain_error("Given status is invalid.");
        else
            status = new_status;
    }
    else 
    {
        throw domain_error("Square status cannot be changed.");
    }
}

//
// setPrev
//  Precondition:  This is not a WALL or START square.
//  Postcondition:  This square's `prev` is set to ptr.
//  Exception: Throws domain_error if square is WALL or START.
//
void square::setPrev(square* ptr)
{
    if (status != WALL && status != START)
    {
        prev = ptr;
    }
    else 
    {
        throw domain_error("Square prev cannot be changed.");
    }
}

//
// reset
//  Postcondition:  If this is a plain square, `status` is set to UNVISITED.
//  Postcondition:  The `prev` pointer is set to NULL.
//
void square::reset()
{
    if (isPlainSquare())
    {
        status = UNVISITED;
    }

    prev = NULL;
}

//
// STREAM OUTPUT
//  Postcondition:  Puts a single char representing the square status into
//     the output stream `out`, and returns `out` to allow for chaining.
//  Example: If sq.status is WALL, the character `#` is put into the output
//     stream.
//
ostream& operator<< (ostream &out, const square &sq)
{
    out << sq.toChar();
    return out;
}

} // End namespace
