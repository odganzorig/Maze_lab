/*
*  square.h
*  square header file for Lab 6
*
*  Barb Wahl & Theresa Wilson
*  Revised 3-10-18
*
*  DO NOT CHANGE THIS FILE
*
*  An instance of the square class represents a single square in the maze.
*
*  The four instance variables of a square are as follows:
*     - int `status`: The current status of the square:
*           0 -- WALL
*           1 -- START
*           2 -- EXIT
*           3 -- plain square, UNVISITED
*           4 -- plain square, WORK_LIST
*           5 -- plain square, EXPLORED
*           6 -- plain square, SOLUTION_PATH
*
*     - int `row`: The row in which the square resides in the maze.
*       Row 0 is the top row.
*
*     - int `col`: The column in which the square resides in the maze.
*       Column 0 is the leftmost column.
*
*     - square* `prev`: Answers the question, "Which square was being explored
*       when the current square was added to the worklist?"  The previous 
*       pointers can be followed from current square back to the start to 
*       construct the path used to find the current square. If the current 
*       square *is* the start square, prev will be NULL. By default, `prev`
*       is NULL when a square is created.
*/

#ifndef square_H
#define square_H

namespace mazelab
{

class square
{
 public:
    // STATUS CODES -- USE THESE CONSTANTS IN YOUR IMPLEMENTATION FILE 
    //    (do not use the actual number values)

    // Special squares:
    static const int WALL = 0;
    static const int START = 1;
    static const int EXIT = 2;
    // Plain squares:
    static const int UNVISITED = 3;
    static const int WORK_LIST = 4;
    static const int EXPLORED = 5;
    static const int SOLUTION_PATH = 6;

    //
    //  Default constructor
    //  Postcondition: Makes a WALL square located in the upper left corner of a maze
    //     (location [0,0]) with `prev` set to NULL.
    //
    square();

    //
    //  Constructor with 3 parameters for status, row, and column
    //  Precondition:   WALL <= status_val <= UNVISITED
    //  Postcondition:  The new square has status, row, and col values
    //     initialized to status_val, row_val, and col_val, respectively.
    //  Postcondition:  The `prev` pointer is initialized to NULL.
    //  Exception: Throws domain_error if status_val is invalid.
    //
    square(int status_val, int row_val, int col_val);

    // *** ACCESSORS *** //

    // 
    // getStatus
    //  Postcondition: Return value is the current status of the square.
    int getStatus() const;

    //
    // getRow
    //  Postcondition: Return value is the row where the square is located.
    //
    int getRow() const;

    //
    // getCol
    //  Postcondition: Return value is the column where the square is located.
    //
    int getCol() const;

    // 
    // getPrev
    //  Postcondition: Return value is a pointer to a square.
    //
    square * getPrev() const;

    //  
    // isWall
    //  Postcondition:  Return true square is WALL square; otherwise
    //     return false.
    //
    bool isWall() const;

    //
    // isStart
    //  Postcondition:  Return true if square is a START square;
    //     otherwise, return false.
    //
    bool isStart() const;

    //
    // isExit
    //  Postcondition:  Return true if square is an EXIT square;
    //     otherwise, return false.
    //
    bool isExit() const;

    //
    // isPlainSquare
    //  Postcondition:  Return true if the square is not a WALL,
    //     START, or EXIT square; otherwise, return false.
    //
    bool isPlainSquare() const;

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
    char toChar() const;

    //
    // toString
    //  Postcondition: Return value is a string for reporting the coordinates
    //     of the square in the form "[row,col]".
    //
    //  Example: If the square is in row 5 and column 0, return "[5,0]".
    //
    std::string toString() const;

    // *** MODIFIERS *** //

    //  
    // setStatus 
    //  Precondition:  UNVISITED <= `new_status` <= SOLUTION_PATH
    //  Precondition:  This is not a WALL, START, or EXIT square.
    //  Postcondition: `status` is set to new_status.
    //  Exception: Throws domain_error if new_status is invalid.
    //  Exception: Throws domain_error if square status may not be changed.
    //
    void setStatus(int new_status);

    //
    // setPrev
    //  Precondition:  This is not a WALL or START square.
    //  Postcondition:  This square's `prev` is set to ptr.
    //  Exception: Throws domain_error if square is WALL or START.
    //
    void setPrev(square* ptr);

    //  
    // reset
    //  Postcondition:  If this is a plain square, `status` is set to UNVISITED.
    //  Postcondition:  The `prev` pointer is set to NULL.
    //
    void reset();

 private:
    int status;
    int row;
    int col;
    square* prev;
};

//    
// STREAM OUTPUT
//  Postcondition:  Puts a single char representing the square status into
//     the output stream `out`, and returns `out` to allow for chaining.
//  Example: If sq.status is WALL, the character `#` is put into the output
//     stream.
//
std::ostream& operator<< (std::ostream &out, const square &sq);

} // End namespace

#endif /* square_H */
