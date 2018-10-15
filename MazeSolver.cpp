/*
*  MazeSolver.cpp -- Implementation of MazeSolver Class
*  Lab 6, CS 223
*
*  Name: Od Ganzorig
*  Date: 03/18/2018
*
*  A MazeSolver has a worklist for managing the exploration of a maze, and a
*  specific maze to solve.  MazeSolver returns a path from Start to Exit if
*  such a path exists, or reports that the maze is unsolvable.
*
*  Instance variables:
*     maze * maze_ptr;  // pointer to the maze to be solved
*     std::deque <square *> worklist;
*/


#include <stdexcept>    // provides standard exceptions
#include <cassert>      // provides assert
#include <sstream>      // provides string streams
#include <iostream>
#include "MazeSolver.h"

using namespace std;
using namespace mazelab;

// implement your MazeSolver functions here...

MazeSolver::MazeSolver(std::istream &in)
{
    maze_ptr = new maze(in);
    worklist.push_front(maze_ptr -> getStart());
    try
    {
        maze_ptr = new maze(in);
        worklist.push_front(maze_ptr -> getStart());  
    }
    catch(domain_error e)
    {
       
        e.what();
    }

}

MazeSolver::~MazeSolver()
{
    delete maze_ptr;
    maze_ptr = NULL;
}

std::string MazeSolver::tracePath(mazelab::square * sq, bool mark_solution)
{
    string path = "";
    square* current_square = sq;
    
    while(current_square != NULL)
    {
        if (path != "")
        {
            path = " " + path;
        }
        path = current_square -> toString() + path;
        if (mark_solution && current_square -> isPlainSquare())
        {
            current_square -> setStatus(square::SOLUTION_PATH);
        }
        current_square = current_square -> getPrev();
    }
    return path;
}

void MazeSolver::reset()
{
    maze_ptr -> reset();
    worklist.clear();
    worklist.push_front(maze_ptr -> getStart());
}

bool MazeSolver::neverOnWorklist(mazelab::square * sq)
{
    return (sq -> getStatus() == 3 || sq -> getStatus() == 2);
            
}

mazelab::square * MazeSolver::step(bool withBFS)
{
    square * current;
    vector<square*> neighbors;
    if (worklist.empty())
        return NULL;
    
    current = worklist.front();
    worklist.pop_front();
    if (current -> getStatus() == square::EXIT)
        return NULL;

    neighbors = maze_ptr -> getNeighbors(*current);
    for (unsigned i = 0; i < neighbors.size(); i++)
    {
        if ((neighbors[i] -> getStatus() != square::WALL) && (neverOnWorklist(neighbors[i])))
        {
            neighbors[i] -> setPrev(current);
            if (neighbors[i] -> isPlainSquare())
            {
                neighbors[i] -> setStatus(square::WORK_LIST);
            }
            if (withBFS == true)
            {
                worklist.push_back(neighbors[i]);
            }
            else
            {
                worklist.push_front(neighbors[i]);
            }
        }

    }
    if (current -> isPlainSquare())
    {
        current -> setStatus(square::EXPLORED);
    }
    return current;
    
}

std::string MazeSolver::solve(bool printMaze, bool withBFS)
{
    worklist.push_front(maze_ptr -> getStart());
    while(!worklist.empty())
    {
        bool rando = false;
        for( unsigned i =0; i < worklist.size(); i++)
        {
            if (worklist[i] -> isExit())
            {
                rando = true;
                break;
            }
        }
        if (rando)
        {
            tracePath(maze_ptr -> getExit(), true);
            if (printMaze == true)
            {
                cout << *maze_ptr;
            }
            return tracePath(maze_ptr -> getExit(), false);
        }
        else
            step(withBFS);
    }
    return "unsolvable!";
}

std::ostream& operator<< (std::ostream &out, const MazeSolver &solver)
{
    out << *(solver.maze_ptr);
    for ( unsigned i = 0; i < solver.worklist.size(); i++)
    {
        out << solver.worklist[i];
    }
    return out;
}

// Provided main function for very initial testing;
// REMOVE or COMMENT OUT this main function before you build 
// and run with MazeSolver_test.cpp.

// int main()
// {
//     // stringstream maze_stream;
//     // maze_stream << "2 3 0 3 1 2 3 3 ";
//     // MazeSolver solver(maze_stream);

//     // cout << "Depth-first Search:\n";
//     // string solverout = solver.solve(true, false);  
//     // cout << "\nDFS path found: " << solverout << endl;


//     //cout << "\nBreadth-first Search:\n";
//     //solver.reset();
//     //solverout = solver.solve(true, true);  
//     //cout << "\nBFS path found: " << solverout << endl;

//     return 0;
// }
