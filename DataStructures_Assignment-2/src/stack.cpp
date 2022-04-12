//
// Created by Matt on 2/11/2022.
//

#include "stack.h"

//Destructor
Stack::~Stack() {
    while (peek() != Position(-1, -1)) {
        pop();
    }
}

//Push method to push the stack onto the stack
void Stack::push(Position position) {

    auto new_node = new Node();
    new_node->m_data = position;

    // is this the first node?
    if (m_first == nullptr) {
        // yep!
        m_first = new_node;
    } else {
        // nope, one already exists
        new_node->m_next = m_first;
        m_first = new_node;
    }
}

//Peek method to look inside the stack
Position Stack::peek() {
    if (m_first != nullptr) {
        return m_first->m_data;
    }
    return {-1, -1};
}

//Pop method to pop off the stack
void Stack::pop() {

    // Check to see if the stack is empty
    if (m_first != nullptr) {
        auto node = m_first;

        // detach node
        m_first = node->m_next;

        delete node;
    }
}

//Overloaded << operator
std::ostream& operator<<(std::ostream& output, Stack& stack) {

    auto node = stack.m_first;
    while (node != nullptr) {
        output << node->m_data << std::endl;
        node = node->m_next;
    }
    return output;
}