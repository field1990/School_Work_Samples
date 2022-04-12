//
// Created by Matt on 2/11/2022.
//

#ifndef ASSIGNMENT_2_STACK_H
#define ASSIGNMENT_2_STACK_H

#include <iostream>
#include "position.h"

using namespace std;

class Node {
public:
    Position m_data;
    Node* m_next {nullptr};
};

class Stack {
private:
    Node* m_first {nullptr};

public:
    //Constructors and destructors
    Stack() = default;
    virtual ~Stack();

    //Methods
    void push(Position num);
    Position peek();
    void pop();

    //Overloaded operator
    friend ostream& operator<<(ostream& output, Stack& stack);
};

ostream& operator<<(std::ostream& output, Stack& stack);



#endif //ASSIGNMENT_2_STACK_H