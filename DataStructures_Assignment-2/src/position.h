//
// Created by Matt on 2/11/2022.
//

#ifndef ASSIGNMENT_2_POSITION_H
#define ASSIGNMENT_2_POSITION_H

#include <iostream>

using namespace std;

class Position {
public:
    //Position location member variables
    int m_row_location;
    int m_column_location;

    //Constructor
    Position();

    Position(int row_location, int column_location);

    bool operator!=(Position position);
};

ostream& operator<<(ostream& output, Position position);


#endif //ASSIGNMENT_2_POSITION_H