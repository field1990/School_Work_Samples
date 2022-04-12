#include <iostream>
#include "position.h"
#include "maze.h"

using namespace std;

int main(int argc, char* argv[]) {

    //Create an instance of the Maze class
    Maze maze_runner;

    if (argc > 1) {
        cout << "You are opening this maze: " << argv[1] << endl;
    } else {
        cout << "test.txt maze is being edited" << endl;
    }

    //Run the maze solver routine
    maze_runner.maze_solver(argv);

    return 0;
}

