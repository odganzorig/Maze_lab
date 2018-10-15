// FILE: maze_tests.cpp
// CS 223 Winter 2018, Lab 6
// Provided tests by T. Wilson and B. Wahl, updated 3-11-18
//
// <Name and Date>
//

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <cstdlib>
#include <stdexcept>
#include "maze.h"
#include "gtest/gtest.h"  // declares the testing framework

using namespace std;
using namespace mazelab;

namespace {

    // Lab 6 Unit Testing Plan -- 49 tests, 38 of which are provided

    // 11 tests for BasicMazeFunctionalityWithStringstream
    //   - 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_GetNumRows_and_GetNumCols
    //   - 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_GetStart
    //   - 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_GetExit
    //   - 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_Get_at_0_0
    //   - 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_Get_at_0_1
    //   - 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_Get_at_0_2
    //   - 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_Get_at_0_3
    //   - 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_GetSquare_at_0_0
    //   - 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_GetSquare_at_0_1
    //   - 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_GetSquare_at_0_2
    //   - 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_GetSquare_at_0_3
    
    // 7 tests for BasicMazeFunctionalityWithMazeFile
    //   - 3_by_2_maze_t1_Test_GetNumRows_and_GetNumCols
    //   - 3_by_2_maze_t1_Test_GetStart
    //   - 3_by_2_maze_t1_Test_GetExit
    //   - 3_by_2_maze_t1_Test_Get_at_0_0
    //   - 3_by_2_maze_t1_Test_Get_at_1_0
    //   - 3_by_2_maze_t1_Test_GetSquare_at_1_1
    //   - 3_by_2_maze_t1_Test_GetSquare_at_2_1
    
    // 2 tests for toString
    //   - 1_by_4_maze_WALL_EXIT_UNVISITED_START
    //   - 3_by_2_maze_t1_Test_GetSquare_at_2_1
    
    // 9 tests for getNeighbors
    //   - GetNeighbors_of_Square_in_UpperLeftCorner  <<< NOT PROVIDED
    //   - GetNeighbors_of_Square_in_UpperRightCorner  <<< NOT PROVIDED
    //   - GetNeighbors_of_Square_in_LowerLeftCorner  <<< NOT PROVIDED
    //   - GetNeighbors_of_Square_in_LowerRightCorner  <<< NOT PROVIDED
    //   - GetNeighbors_of_Square_on_UpperMiddleEdge  <<< NOT PROVIDED
    //   - GetNeighbors_of_Square_on_RightMiddleEdge  <<< NOT PROVIDED
    //   - GetNeighbors_of_Square_on_LowerMiddleEdge  <<< NOT PROVIDED
    //   - GetNeighbors_of_Square_on_LeftMiddleEdge  <<< NOT PROVIDED
    //   - GetNeighbors_of_Interior_Square  <<< NOT PROVIDED
    
    // 2 tests for reset
    //   - MakeChangesTo_maze_b1_ThenReset_CheckStatusOfSquares  <<< NOT PROVIDED
    //   - MakeChangesTo_maze_b1_ThenReset_CheckSquarePrevs  <<< NOT PROVIDED
    
    // 2 tests for stream output
    //   - Send_maze_b1_to_OutputStream
    //   - OutputStream_Chaining
    
    // 16 tests for exception handling
    //   - DomainError_Thrown_when_Maze_Has_Invalid_Number_of_Rows
    //   - DomainError_Thrown_when_Maze_Has_Invalid_Number_of_Columns
    //   - DomainError_Thrown_when_Maze_Has_Square_With_Status_NegativeOne
    //   - DomainError_Thrown_when_Maze_Has_Square_With_Status_Four
    //   - DomainError_Thrown_when_Maze_Has_No_StartSquare
    //   - DomainError_Thrown_when_Maze_Has_Multiple_StartSquares
    //   - DomainError_Thrown_when_Maze_Has_No_ExitSquare
    //   - DomainError_Thrown_when_Maze_Has_Multiple_ExitSquares
    //   - Out_of_Range_Thrown_when_Getting_SquarePointer_at_Row_NegativeOne
    //   - Out_of_Range_Thrown_when_Getting_SquarePointer_at_Row_NumRows
    //   - Out_of_Range_Thrown_when_Getting_SquarePointer_at_Col_NegativeOne
    //   - Out_of_Range_Thrown_when_Getting_SquarePointer_at_Col_NumCols
    //   - Out_of_Range_Thrown_when_GetSquare_at_Row_NegativeOne
    //   - Out_of_Range_Thrown_when_GetSquare_at_Row_NumRows
    //   - Out_of_Range_Thrown_when_GetSquare_at_Col_NegativeOne
    //   - Out_of_Range_Thrown_when_GetSquare_at_Col_NumCols

    //static const int WALL = square::WALL;
    //static const int START = square::START;
    //static const int EXIT = square::EXIT;
    static const int UNVISITED = square::UNVISITED;
    static const int WORK_LIST = square::WORK_LIST;
    static const int EXPLORED = square::EXPLORED;
    static const int SOLUTION_PATH = square::SOLUTION_PATH;

    // Test Constructor and Basic Getters
    //  The basic maze class functionality (constructor, destructor,
    //  getStart, getExit, getNumRows, getNumCols, get) is tested
    //  first using a 1 x 4 maze inserted into a stringstream.

    TEST(TestBasicMazeFunctionalityWithStringstream, 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_GetNumRows_and_GetNumCols)
    {
        stringstream maze_stream;
        maze_stream << "1 4 0 2 3 1 ";
        maze m1(maze_stream);

        EXPECT_EQ(m1.getNumRows(), 1);
        EXPECT_EQ(m1.getNumCols(), 4);
    }

    TEST(TestBasicMazeFunctionalityWithStringstream, 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_GetStart)
    {
        stringstream maze_stream;
        maze_stream << "1 4 0 2 3 1 ";
        maze m1(maze_stream);

        square* start_ptr = NULL;
        start_ptr = m1.getStart();
        ASSERT_TRUE(start_ptr != NULL);
        EXPECT_TRUE(start_ptr -> isStart());
        EXPECT_EQ(start_ptr -> toString(), "[0,3]");
    }

    TEST(TestBasicMazeFunctionalityWithStringstream, 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_GetExit)
    {
        stringstream maze_stream;
        maze_stream << "1 4 0 2 3 1 ";
        maze m1(maze_stream);

        square* exit_ptr = NULL;
        exit_ptr = m1.getExit();
        ASSERT_TRUE(exit_ptr != NULL);
        EXPECT_TRUE(exit_ptr -> isExit()); 
        EXPECT_EQ(exit_ptr -> toString(), "[0,1]");
    }

    TEST(TestBasicMazeFunctionalityWithStringstream, 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_Get_at_0_0)
    {
        stringstream maze_stream;
        maze_stream << "1 4 0 2 3 1 ";
        maze m1(maze_stream);

        square* sq_ptr = NULL; 
        sq_ptr = m1.get(0, 0);
        ASSERT_TRUE(sq_ptr != NULL);
        EXPECT_TRUE(sq_ptr -> isWall());
        EXPECT_EQ(sq_ptr -> toString(), "[0,0]");
    }

    TEST(TestBasicMazeFunctionalityWithStringstream, 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_Get_at_0_1)
    {
        stringstream maze_stream;
        maze_stream << "1 4 0 2 3 1 ";
        maze m1(maze_stream);

        square* sq_ptr = NULL; 
        sq_ptr = m1.get(0, 1);
        ASSERT_TRUE(sq_ptr != NULL);
        EXPECT_TRUE(sq_ptr -> isExit());
        EXPECT_EQ(sq_ptr -> toString(), "[0,1]");
    }

    TEST(TestBasicMazeFunctionalityWithStringstream, 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_Get_at_0_2)
    {
        stringstream maze_stream;
        maze_stream << "1 4 0 2 3 1 ";
        maze m1(maze_stream);

        square* sq_ptr = NULL; 
        sq_ptr = m1.get(0, 2);
        ASSERT_TRUE(sq_ptr != NULL);
        EXPECT_TRUE(sq_ptr -> getStatus() == UNVISITED);
        EXPECT_EQ(sq_ptr -> toString(), "[0,2]");
    }

    TEST(TestBasicMazeFunctionalityWithStringstream, 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_Get_at_0_3)
    {
        stringstream maze_stream;
        maze_stream << "1 4 0 2 3 1 ";
        maze m1(maze_stream);

        square* sq_ptr = NULL; 
        sq_ptr = m1.get(0, 3);
        ASSERT_TRUE(sq_ptr != NULL);
        EXPECT_TRUE(sq_ptr -> isStart());
        EXPECT_EQ(sq_ptr -> toString(), "[0,3]");
    }

    TEST(TestBasicMazeFunctionalityWithStringstream, 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_GetSquare_at_0_0)
    {
        stringstream maze_stream;
        maze_stream << "1 4 0 2 3 1 ";
        maze m1(maze_stream);

        square sq = m1.getSquare(0, 0);
        EXPECT_TRUE(sq.isWall());
        EXPECT_EQ(sq.toString(), "[0,0]");
    }

    TEST(TestBasicMazeFunctionalityWithStringstream, 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_GetSquare_at_0_1)
    {
        stringstream maze_stream;
        maze_stream << "1 4 0 2 3 1 ";
        maze m1(maze_stream);

        square sq = m1.getSquare(0, 1);
        EXPECT_TRUE(sq.isExit());
        EXPECT_EQ(sq.toString(), "[0,1]");
    }

    TEST(TestBasicMazeFunctionalityWithStringstream, 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_GetSquare_at_0_2)
    {
        stringstream maze_stream;
        maze_stream << "1 4 0 2 3 1 ";
        maze m1(maze_stream);

        square sq = m1.getSquare(0, 2);
        EXPECT_TRUE(sq.getStatus() == UNVISITED);
        EXPECT_EQ(sq.toString(), "[0,2]");
    }

    TEST(TestBasicMazeFunctionalityWithStringstream, 1_by_4_maze_WALL_EXIT_UNVISITED_START_Test_GetSquare_at_0_3)
    {
        stringstream maze_stream;
        maze_stream << "1 4 0 2 3 1 ";
        maze m1(maze_stream);

        square sq = m1.getSquare(0, 3);
        EXPECT_TRUE(sq.isStart());
        EXPECT_EQ(sq.toString(), "[0,3]");
    }
 
    // Test Constructor and Basic Getters
    //  The basic maze class functionality (constructor, destructor,
    //  getStart, getExit, getNumRows, getNumCols, get) is tested
    //  next using the 3 x 2 maze in the file: maze_t1.txt

    TEST(TestBasicMazeFunctionalityWithMazeFile, 3_by_2_maze_t1_Test_GetNumRows_and_GetNumCols)
    {
        // contents of maze_t1.txt:
        // 3 2
        // 0 1 3 3 2 0
        ifstream mazefile("maze_t1.txt");
        maze m1(mazefile);

        EXPECT_EQ(m1.getNumRows(), 3);
        EXPECT_EQ(m1.getNumCols(), 2);
    }

    TEST(TestBasicMazeFunctionalityWithMazeFile, 3_by_2_maze_t1_Test_GetStart)
    {
        // contents of maze_t1.txt:
        // 3 2
        // 0 1 3 3 2 0
        ifstream mazefile("maze_t1.txt");
        maze m1(mazefile);
        cout << m1<<endl;
        square* start_ptr = NULL;
        start_ptr = m1.getStart();
        ASSERT_TRUE(start_ptr != NULL);
        EXPECT_TRUE(start_ptr -> isStart());
        EXPECT_EQ(start_ptr -> toString(), "[0,1]");
    }

    TEST(TestBasicMazeFunctionalityWithMazeFile, 3_by_2_maze_t1_Test_GetExit)
    {
        // contents of maze_t1.txt:
        // 3 2
        // 0 1 3 3 2 0
        ifstream mazefile("maze_t1.txt");
        maze m1(mazefile);

        square* exit_ptr = NULL;
        exit_ptr = m1.getExit();
        ASSERT_TRUE(exit_ptr != NULL);
        EXPECT_TRUE(exit_ptr -> isExit()); 
        EXPECT_EQ(exit_ptr -> toString(), "[2,0]");
    }

    TEST(TestBasicMazeFunctionalityWithMazeFile, 3_by_2_maze_t1_Test_Get_at_0_0)
    {
        // contents of maze_t1.txt:
        // 3 2
        // 0 1 3 3 2 0
        ifstream mazefile("maze_t1.txt");
        maze m1(mazefile);

        square* sq_ptr = NULL;
        sq_ptr = m1.get(0, 0);
        ASSERT_TRUE(sq_ptr != NULL);
        EXPECT_TRUE(sq_ptr -> isWall());
        EXPECT_EQ(sq_ptr -> toString(), "[0,0]");
    }

    TEST(TestBasicMazeFunctionalityWithMazeFile, 3_by_2_maze_t1_Test_Get_at_1_0)
    {
        // contents of maze_t1.txt:
        // 3 2
        // 0 1 3 3 2 0
        ifstream mazefile("maze_t1.txt");
        maze m1(mazefile);

        square* sq_ptr = NULL;
        sq_ptr = m1.get(1, 0);
        ASSERT_TRUE(sq_ptr != NULL);
        EXPECT_EQ(sq_ptr -> getStatus(), UNVISITED);
        EXPECT_EQ(sq_ptr -> toString(), "[1,0]");
    }

    TEST(TestBasicMazeFunctionalityWithMazeFile, 3_by_2_maze_t1_Test_GetSquare_at_1_1)
    {
        // contents of maze_t1.txt:
        // 3 2
        // 0 1 3 3 2 0
        ifstream mazefile("maze_t1.txt");
        maze m1(mazefile);

        square* sq_ptr = NULL;
        sq_ptr = m1.get(1, 1);
        ASSERT_TRUE(sq_ptr != NULL);
        EXPECT_EQ(sq_ptr -> getStatus(), UNVISITED);
        EXPECT_EQ(sq_ptr -> toString(), "[1,1]");
    }

    TEST(TestBasicMazeFunctionalityWithMazeFile, 3_by_2_maze_t1_Test_GetSquare_at_2_1)
    {
        // contents of maze_t1.txt:
        // 3 2
        // 0 1 3 3 2 0
        ifstream mazefile("maze_t1.txt");
        maze m1(mazefile);

        square* sq_ptr = NULL;
        sq_ptr = m1.get(2, 1);
        ASSERT_TRUE(sq_ptr != NULL);
        EXPECT_TRUE(sq_ptr -> isWall());
        EXPECT_EQ(sq_ptr -> toString(), "[2,1]");
    }

    // Test toString

    TEST(TestToString, 1_by_4_maze_WALL_EXIT_UNVISITED_START)
    {
        stringstream maze_stream;
        maze_stream << "1 4 0 2 3 1 ";
        maze m1(maze_stream);

        string mazestr = m1.toString();
        string correct = "\n# E _ S \n";
        EXPECT_EQ(mazestr, correct);
    }

    TEST(TestToString,  3_by_2_maze_t1_Test_GetSquare_at_2_1)
    {
        // contents of maze_t1.txt:
        // 3 2
        // 0 1 3 3 2 0
        ifstream mazefile("maze_t1.txt");
        maze m1(mazefile);

        string mazestr = m1.toString();
        string correct = "\n# S \n_ _ \nE # \n";
        EXPECT_EQ(mazestr, correct);
    }

    // Test getNeighbors

    TEST(TestGetNeighbors, GetNeighbors_of_Square_in_UpperLeftCorner)
    {
        ifstream mazefile("maze_t1.txt");
        maze m1(mazefile);
        square sq = m1.getSquare(0, 0);
        vector<square*> neighbors = m1.getNeighbors(sq);
        EXPECT_EQ(neighbors.size(),2);
        EXPECT_TRUE(neighbors[0] == m1.get(0, 1));
        EXPECT_TRUE(neighbors[1] == m1.get(1, 0));
    }

    TEST(TestGetNeighbors, GetNeighbors_of_Square_in_UpperRightCorner)
    {
        ifstream mazefile("maze_t1.txt");
        maze m1(mazefile);
        square sq = m1.getSquare(0, 1);
        vector<square*> neighbors = m1.getNeighbors(sq);
        EXPECT_EQ(neighbors.size(),2);
        EXPECT_TRUE(neighbors[0] == m1.get(1, 1));
        EXPECT_TRUE(neighbors[1] == m1.get(0, 0));
    }

    TEST(TestGetNeighbors, GetNeighbors_of_Square_in_LowerLeftCorner)
    {
        ifstream mazefile("maze_t1.txt");
        maze m1(mazefile);
        square sq = m1.getSquare(2, 0);
        vector<square*> neighbors = m1.getNeighbors(sq);
        EXPECT_EQ(neighbors.size(),2);
        EXPECT_TRUE(neighbors[0] == m1.get(1, 0));
        EXPECT_TRUE(neighbors[1] == m1.get(2, 1));
    }

    TEST(TestGetNeighbors, GetNeighbors_of_Square_in_LowerRightCorner)
    {
        ifstream mazefile("maze_t1.txt");
        maze m1(mazefile);
        square sq = m1.getSquare(2, 1);
        vector<square*> neighbors = m1.getNeighbors(sq);
        EXPECT_EQ(neighbors.size(),2);
        EXPECT_TRUE(neighbors[0] == m1.get(1, 1));
        EXPECT_TRUE(neighbors[1] == m1.get(2, 0));
    }

    TEST(TestGetNeighbors, GetNeighbors_of_Square_on_UpperMiddleEdge)
    {
        ifstream mazefile("maze_t4.txt");
        maze m1(mazefile);
        square sq = m1.getSquare(0, 1);
        vector<square*> neighbors = m1.getNeighbors(sq);
        EXPECT_EQ(neighbors.size(),3);
        EXPECT_TRUE(neighbors[0] == m1.get(0, 2));
        EXPECT_TRUE(neighbors[1] == m1.get(1, 1));
        EXPECT_TRUE(neighbors[2] == m1.get(0, 0));
    }

    TEST(TestGetNeighbors, GetNeighbors_of_Square_on_RightMiddleEdge)
    {
        ifstream mazefile("maze_t4.txt");
        maze m1(mazefile);
        square sq = m1.getSquare(1, 2);
        vector<square*> neighbors = m1.getNeighbors(sq);
        EXPECT_EQ(neighbors.size(),3);
        EXPECT_TRUE(neighbors[0] == m1.get(0, 2));
        EXPECT_TRUE(neighbors[1] == m1.get(2, 2));
        EXPECT_TRUE(neighbors[2] == m1.get(1, 1));
    }

    TEST(TestGetNeighbors, GetNeighbors_of_Square_on_LowerMiddleEdge)
    {
        ifstream mazefile("maze_t4.txt");
        maze m1(mazefile);
        square sq = m1.getSquare(2, 1);
        vector<square*> neighbors = m1.getNeighbors(sq);
        EXPECT_EQ(neighbors.size(),3);
        EXPECT_TRUE(neighbors[0] == m1.get(1, 1));
        EXPECT_TRUE(neighbors[1] == m1.get(2, 2));
        EXPECT_TRUE(neighbors[2] == m1.get(2, 0));
    }

    TEST(TestGetNeighbors, GetNeighbors_of_Square_on_LeftMiddleEdge)
    {
        ifstream mazefile("maze_t4.txt");
        maze m1(mazefile);
        square sq = m1.getSquare(1, 0);
        vector<square*> neighbors = m1.getNeighbors(sq);
        EXPECT_EQ(neighbors.size(),3);
        EXPECT_TRUE(neighbors[0] == m1.get(0, 0));
        EXPECT_TRUE(neighbors[1] == m1.get(1, 1));
        EXPECT_TRUE(neighbors[2] == m1.get(2, 0));
    }

    TEST(TestGetNeighbors, GetNeighbors_of_Interior_Square)
    {
        ifstream mazefile("maze_t4.txt");
        maze m1(mazefile);
        square sq = m1.getSquare(1, 1);
        vector<square*> neighbors = m1.getNeighbors(sq);
        EXPECT_EQ(neighbors.size(),4);
        EXPECT_TRUE(neighbors[0] == m1.get(0, 1));
        EXPECT_TRUE(neighbors[1] == m1.get(1, 2));
        EXPECT_TRUE(neighbors[2] == m1.get(2, 1));
        EXPECT_TRUE(neighbors[3] == m1.get(1, 0));
    }

    // Test reset

    TEST(TestReset, MakeChangesTo_maze_b1_ThenReset_CheckStatusOfSquares)
    {
        ifstream mazefile("maze_b1.txt");
        maze m1(mazefile);
        square *sq = m1.get(0, 0);
        sq -> setStatus(4);
        square *sq1 = m1.get(0, 1);
        sq1 -> setStatus(5);
        m1.reset();
        EXPECT_EQ(sq -> getStatus(), 3);
        EXPECT_EQ(sq1 -> getStatus(), 3);

    }

    TEST(TestReset, MakeChangesTo_maze_b1_ThenReset_CheckSquarePrevs)
    {
        ifstream mazefile("maze_b1.txt");
        maze m1(mazefile);
        square *sq = m1.get(0, 0);
        sq -> setStatus(4);
        square *sq1 = m1.get(0, 1);
        sq1 -> setStatus(5);
        m1.reset();
        EXPECT_TRUE(sq -> getPrev() == NULL);
        EXPECT_TRUE(sq1 -> getPrev() == NULL);
    }

    // Test stream output

    TEST(TestStreamOutput, Send_maze_b1_to_OutputStream)
    {
        stringstream out;
        ifstream mazefile("maze_b1.txt");
        maze m1(mazefile);

        string correct = "\n_ _ _ _ \nS # # _ \n# E _ _ \n";
    
        out << m1;
        string actual = out.str();
        EXPECT_EQ(actual, correct);
    }

    TEST(TestStreamOutput, OutputStream_Chaining)
    {
        stringstream out;
        ifstream mazefile1("maze_b3.txt");
        maze m1(mazefile1);
        ifstream mazefile2("maze_b1.txt");
        maze m2(mazefile2);
    
        string correct1 = "\nS \nE \n";
        string correct2 = "\n_ _ _ _ \nS # # _ \n# E _ _ \n";
        string correct = correct1 + correct2;
    
        out << m1 << m2;
        string actual = out.str();
        EXPECT_EQ(actual, correct);
    }

    // Test exceptions

    TEST(TestExceptions, DomainError_Thrown_when_Maze_Has_Invalid_Number_of_Rows)
    {
        stringstream maze_stream;
        maze_stream << "0 1 0 1 2";
        try {
            maze m1(maze_stream);  // should throw domain_error
        } catch (domain_error) {
            EXPECT_TRUE(true);
            return;
        }
        EXPECT_TRUE(false);      // shouldn't make it here;
    }

    TEST(TestExceptions, DomainError_Thrown_when_Maze_Has_Invalid_Number_of_Columns)
    {
        stringstream maze_stream;
        maze_stream << "1 0 0 1 2";
        try {
            maze m1(maze_stream);  // should throw domain_error
        } catch (domain_error) {
            EXPECT_TRUE(true);
            return;
        }
        EXPECT_TRUE(false);      // shouldn't make it here;
    }

    TEST(TestExceptions, DomainError_Thrown_when_Maze_Has_Square_With_Status_NegativeOne)
    {
        stringstream maze_stream;
        maze_stream << "3 1 0 0 -1";
        try {
            maze m1(maze_stream);  // should throw domain_error
        } catch (domain_error) {
            EXPECT_TRUE(true);
            return;
        }
        EXPECT_TRUE(false);      // shouldn't make it here;
    }

    TEST(TestExceptions, DomainError_Thrown_when_Maze_Has_Square_With_Status_Four)
    {
        stringstream maze_stream;
        maze_stream << "3 1 0 0 4";
        try {
            maze m1(maze_stream);  // should throw domain_error
        } catch (domain_error) {
            EXPECT_TRUE(true);
            return;
        }
        EXPECT_TRUE(false);      // shouldn't make it here;
    }

    TEST(TestExceptions, DomainError_Thrown_when_Maze_Has_No_StartSquare)
    {
        stringstream maze_stream;
        maze_stream << "3 1 0 0 2";
        try {
            maze m1(maze_stream);  // should throw domain_error
        } catch (domain_error) {
            EXPECT_TRUE(true);
            return;
        }
        EXPECT_TRUE(false);      // shouldn't make it here;
    }

    TEST(TestExceptions, DomainError_Thrown_when_Maze_Has_Multiple_StartSquares)
    {
        stringstream maze_stream;
        maze_stream << "3 1 2 1 1";
        try {
            maze m1(maze_stream);  // should throw domain_error
        } catch (domain_error) {
            EXPECT_TRUE(true);
            return;
        }
        EXPECT_TRUE(false);      // shouldn't make it here;
    }

    TEST(TestExceptions, DomainError_Thrown_when_Maze_Has_No_ExitSquare)
    {
        stringstream maze_stream;
        maze_stream << "3 1 0 0 1";
        try {
            maze m1(maze_stream);  // should throw domain_error
        } catch (domain_error) {
            EXPECT_TRUE(true);
            return;
        }
        EXPECT_TRUE(false);      // shouldn't make it here;
    }

    TEST(TestExceptions, DomainError_Thrown_when_Maze_Has_Multiple_ExitSquares)
    {
        stringstream maze_stream;
        maze_stream << "3 1 2 2 1";
        try {
            maze m1(maze_stream);  // should throw domain_error
        } catch (domain_error) {
            EXPECT_TRUE(true);
            return;
        }
        EXPECT_TRUE(false);      // shouldn't make it here;
    }

    TEST(TestExceptions, Out_of_Range_Thrown_when_Getting_SquarePointer_at_Row_NegativeOne)
    {
        stringstream maze_stream;
        maze_stream << "3 1 0 1 2";
        maze m1(maze_stream);  
        try {
            m1.get(-1, 0);  // should throw out_of_range
        } catch (out_of_range) {
            EXPECT_TRUE(true);
            return;
        }
        EXPECT_TRUE(false);      // shouldn't make it here;
    }

    TEST(TestExceptions, Out_of_Range_Thrown_when_Getting_SquarePointer_at_Row_NumRows)
    {
        stringstream maze_stream;
        maze_stream << "3 1 0 1 2";
        maze m1(maze_stream);  
        try {
            m1.get(m1.getNumRows(), 0);  // should throw out_of_range
        } catch (out_of_range) {
            EXPECT_TRUE(true);
            return;
        }
        EXPECT_TRUE(false);      // shouldn't make it here;
    }

    TEST(TestExceptions, Out_of_Range_Thrown_when_Getting_SquarePointer_at_Col_NegativeOne)
    {
        stringstream maze_stream;
        maze_stream << "3 1 0 1 2";
        maze m1(maze_stream);  
        try {
            m1.get(0, -1);  // should throw out_of_range
        } catch (out_of_range) {
            EXPECT_TRUE(true);
            return;
        }
        EXPECT_TRUE(false);      // shouldn't make it here;
    }

    TEST(TestExceptions, Out_of_Range_Thrown_when_Getting_SquarePointer_at_Col_NumCols)
    {
        stringstream maze_stream;
        maze_stream << "3 1 0 1 2";
        maze m1(maze_stream);  
        try {
            m1.get(0, m1.getNumCols());  // should throw out_of_range
        } catch (out_of_range) {
            EXPECT_TRUE(true);
            return;
        }
        EXPECT_TRUE(false);      // shouldn't make it here;
    }

    TEST(TestExceptions, Out_of_Range_Thrown_when_GetSquare_at_Row_NegativeOne)
    {
        stringstream maze_stream;
        maze_stream << "3 1 0 1 2";
        maze m1(maze_stream);  
        try {
            m1.getSquare(-1, 0);  // should throw out_of_range
        } catch (out_of_range) {
            EXPECT_TRUE(true);
            return;
        }
        EXPECT_TRUE(false);      // shouldn't make it here;
    }

    TEST(TestExceptions, Out_of_Range_Thrown_when_GetSquare_at_Row_NumRows)
    {
        stringstream maze_stream;
        maze_stream << "3 1 0 1 2";
        maze m1(maze_stream);  
        try {
            m1.getSquare(m1.getNumRows(), 0);  // should throw out_of_range
        } catch (out_of_range) {
            EXPECT_TRUE(true);
            return;
        }
        EXPECT_TRUE(false);      // shouldn't make it here;
    }

    TEST(TestExceptions, Out_of_Range_Thrown_when_GetSquare_at_Col_NegativeOne)
    {
        stringstream maze_stream;
        maze_stream << "3 1 0 1 2";
        maze m1(maze_stream);  
        try {
            m1.getSquare(0, -1);  // should throw out_of_range
        } catch (out_of_range) {
            EXPECT_TRUE(true);
            return;
        }
        EXPECT_TRUE(false);      // shouldn't make it here;
    }

    TEST(TestExceptions, Out_of_Range_Thrown_when_GetSquare_at_Col_NumCols)
    {
        stringstream maze_stream;
        maze_stream << "3 1 0 1 2";
        maze m1(maze_stream);  
        try {
            m1.getSquare(0, m1.getNumCols());  // should throw out_of_range
        } catch (out_of_range) {
            EXPECT_TRUE(true);
            return;
        }
        EXPECT_TRUE(false);      // shouldn't make it here;
    }

} // end namespace

// main() for testing -- boilerplate
int main(int argc, char* argv[]){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

