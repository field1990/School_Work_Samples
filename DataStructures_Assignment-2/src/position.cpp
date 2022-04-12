//
// Created by Matt on 2/11/2022.
//

#include "position.h"
#include <iostream>

using namespace std;

//Default constructor
Position::Position() : m_row_location(1), m_column_location(1){};

Position::Position(int row_location, int column_location)
        : m_row_location(row_location)
        , m_column_location(column_location) {
}

bool Position::operator!=(Position position) {
    return (this->m_row_location != position.m_row_location) || (this->m_column_location != position.m_column_location);
}

//Overloaded << operator
std::ostream& operator<<(std::ostream& output, Position position) {

    output << position.m_row_location << " " << position.m_column_location;

    return output;
}