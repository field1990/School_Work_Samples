//
// Created by Matt on 2/21/2022.
//

#include "maze.h"
#include <iostream>
#include <string>
#include <ctime>
#include <sstream>

using namespace std;

//Constructor
Maze::Maze() : m_column_size(0), m_row_size(0), i(0), j(0), x(0), m_maze_size(0), spot_found(false) {};

//Maze_Solver method that solve the maze
void Maze::maze_solver(char *argv[]) {

    //Call the open_maze routine to open up the maze file
    open_maze(argv);

    //Creating the new Stack Object instance
    Stack stack;

    //Creating the position object to track where we are in the maze
    Position position;

    //Set the seed and time for srand to get a random number out of 4 (Directions N,S,E,W)
    srand((unsigned) time(0));

    while (position.m_column_location != 50 && position.m_row_location != 50) {

        //The direction to go in is randomized, 1-4
        int move = 1 + (rand() % 4);

        //We know the initial position is always going to start here
        if (position.m_column_location == 1 && position.m_row_location == 1) {

            //Start off at 0, 1
            m_maze[1][0] = '#';
            m_maze[position.m_row_location][position.m_column_location] = '#';

            while (spot_found == false) {
                //Randomly select a number between 1 or 2 for EAST and SOUTH. Can't go NORTH or WEST
                move = 1 + (rand() % 2);
                //Move EAST and adjust locations and Maze
                if (move == 1) {
                    maze_direction(0, 1, position, stack);
                }
                    //Move SOUTH
                else {
                    maze_direction(1, 0, position, stack);
                }
            }
            spot_found = false;
        } else {
            while (spot_found == false) {

                move = 1 + (rand() % 4);

                //Moving EAST
                if (move == 1 && m_maze[position.m_row_location][position.m_column_location + 1] != '#' &&
                    m_maze[position.m_row_location][position.m_column_location + 1] != 'N') {
                    maze_direction(0, 1, position, stack);
                }
                    //Moving SOUTH
                else if (move == 2 && m_maze[position.m_row_location + 1][position.m_column_location] != '#' &&
                         m_maze[position.m_row_location + 1][position.m_column_location] != 'N') {
                    maze_direction(1, 0, position, stack);
                }
                    //Moving WEST
                else if (move == 3 && m_maze[position.m_row_location][position.m_column_location - 1] != '#' &&
                         m_maze[position.m_row_location][position.m_column_location - 1] != 'N') {
                    maze_direction(0, -1, position, stack);
                }
                    //Moving NORTH
                else if (move == 4 && m_maze[position.m_row_location - 1][position.m_column_location] != '#' &&
                         m_maze[position.m_row_location - 1][position.m_column_location] != 'N') {
                    maze_direction(-1, 0, position, stack);
                }
                    //Nowhere to Move TRAPPED
                else if (m_maze[position.m_row_location - 1][position.m_column_location] != ' ' &&
                         m_maze[position.m_row_location + 1][position.m_column_location] != ' ' &&
                         m_maze[position.m_row_location][position.m_column_location - 1] != ' ' &&
                         m_maze[position.m_row_location][position.m_column_location + 1] != ' ') {

                    //Call the retreat function to get out of dead end
                    retreat(position, stack);
                }
            }
            spot_found = false;
        }
    }
    //Call the write_maze function to write the maze output to another file
    write_maze(stack, position);
}

//The Open_Maze method that opens up the maze file
void Maze::open_maze(char *argv[]) {

    //Check to see if there's an argv parameter provided, aka a file of a maze provided by the user
    if (!argv[1]) {
        //m_maze_file = "../tests/test.txt";
        //m_maze_file = "../tests/test2.txt";
        m_maze_file = "../tests/test3.txt";
    } else {
        m_maze_file = argv[1];
    }

    ifstream my_read_maze(m_maze_file, ios::in);

    //Going through to populate the 1-D array, character by character
    if (my_read_maze.is_open()) {

        while (!my_read_maze.eof()) {
            my_read_maze.get(m_maze_1d[i]);
            i++;
            m_maze_size++;
        }
        //https://stackoverflow.com/questions/18398167/how-to-copy-a-txt-file-to-a-char-array-in-c/18398230

        //Clear the file stream to reset it, any error flags and to reset the position of the cursor
        my_read_maze.clear();
        my_read_maze.seekg(0);

        //Get the number of rows in the maze txt file
        while (getline(my_read_maze, m_line)) {
            m_row_size++;
        }
        //Generating the column size based on the number of characters in the maze divided by the number of rows minus 1
        m_column_size = m_maze_size / m_row_size - 1;
        cout << "\nCOLUMN SIZE IS: " << m_column_size << endl;
        cout << "\nROW SIZE IS: " << m_row_size << endl;

        //Going through the 1-D array creating when reading in the file and putting it into a 2-D array
        for (int i = 0; i < m_row_size; i++) {
            for (int j = 0; j < m_column_size; j++) {
                if (m_maze_1d[x] != '\n') {
                    m_maze[i][j] = m_maze_1d[x];
                    x++;
                }
                    //What to do when a newline character is found, ignore and adjust counters, will add back in when writing to file
                else {
                    x++;
                    j -= 1;
                }
            }
        }
        //https://www.dreamincode.net/forums/topic/82434-1d-array-into-2d-array/
    } else {
        cout << "Can't open. Please provide a valid txt file";
    }
    my_read_maze.close();
}

//The Maze_Direction method that adjusts the position of where we are in the maze, given the coordinates it is given
void Maze::maze_direction(int row_move, int column_move, Position &position, Stack &stack) {

    if (m_maze[position.m_row_location + row_move][position.m_column_location + column_move] == ' ') {

        //Push the location of the empty location on the stack
        stack.push(position);

        m_maze[position.m_row_location + row_move][position.m_column_location + column_move] = '#';
        position.m_row_location += row_move;
        position.m_column_location += column_move;
        spot_found = true;

    }
}

//The Retreat method used to readjust position based on if there's nowhere else to go
void Maze::retreat(Position &position, Stack &stack) {

    //Setting the trapped spot to a special character to indicate it's part of a dead end and to be able to traverse it
    m_maze[position.m_row_location][position.m_column_location] = 'N';
    spot_found = true;

    //Delete the node from the stack
    stack.pop();

    //Check to see if we came from the NORTH
    if (m_maze[position.m_row_location - 1][position.m_column_location] == '#') {
        position.m_row_location -= 1;
    }
        //Check to see if we came from the SOUTH
    else if (m_maze[position.m_row_location + 1][position.m_column_location] == '#') {
        position.m_row_location += 1;
    }
        //Check to see if we came from the EAST
    else if (m_maze[position.m_row_location][position.m_column_location + 1] == '#') {
        position.m_column_location += 1;
    }
        //Check to see if we came from the WEST
    else if (m_maze[position.m_row_location][position.m_column_location - 1] == '#') {
        position.m_column_location -= 1;
    }
}

//The Write_Maze method writes the output of the solution to a new folder
void Maze::write_maze(Stack &stack, Position &position) {

    //Output stream to output to a new file
    ofstream maze_solved_file;

    m_maze_out = "output.txt";
    maze_solved_file.open(m_maze_out);

    cout << "\nThe Maze at the end: \n";
    for (int i = 0; i < m_row_size; i++) {
        for (int j = 0; j < m_column_size; j++) {
            //Check for invalid characters and replace them with a blank
            if (m_maze[i][j] == 'N') {
                m_maze[i][j] = ' ';
                cout << m_maze[i][j];
            } else {
                //Check to see if the current maze location is equal to the location of the stack location
                if (m_maze[position.m_row_location][position.m_column_location] == m_maze[i][j]) {
                    stack.pop();
                    m_maze[i][j] = '#';
                    cout << m_maze[i][j];
                } else {
                    cout << m_maze[i][j];
                }
            }
            //Write the maze to file new file
            maze_solved_file << m_maze[i][j];
        }
        //Write the newline character back in
        cout << '\n';
        maze_solved_file << '\n';
    }
    maze_solved_file.close();
}