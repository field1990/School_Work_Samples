//
// Created by Matt on 2/21/2022.
//

#ifndef ASSIGNMENT_2_MAZE_H
#define ASSIGNMENT_2_MAZE_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <windows.h>
#include "position.h"
#include "stack.h"

using namespace std;

class Maze{

public:
    //Variables used to read the maze files
    string m_line;
    string m_maze_file;
    string m_maze_out;

    //Count variables for maze dimensions and size
    int m_column_size;
    int m_row_size;
    int m_maze_size;

    //Index Variables
    int i;
    int j;
    int x;

    //Array variables to hold 1D and 2D Array
    char m_maze[52][52];
    char m_maze_1d[52 * 52];

    //Boolean variables
    bool spot_found;

    //Constructor
    Maze();

    //Routines
    void maze_solver(char** argv);
    void open_maze(char** argv);
    void write_maze(Stack &stack, Position &position);
    void maze_direction(int row_move, int column_move, Position &position, Stack &stack);
    void retreat(Position &position, Stack &stack);
};

#endif //ASSIGNMENT_2_MAZE_H
