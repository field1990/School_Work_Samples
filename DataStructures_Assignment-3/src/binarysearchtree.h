//
// Created by Matt on 3/11/2022.
//

#ifndef ASSIGNMENT_3_BINARYSEARCHTREE_H
#define ASSIGNMENT_3_BINARYSEARCHTREE_H

#include <iostream>

using namespace std;

class Node;//Put declaration before so that Node* is known before to redefine it

typedef Node* NodePtr; //Giving Mode*, a known type, a new name, an alias

class Node{

public:
    string m_data;
    int m_height;
    NodePtr m_left {nullptr};
    NodePtr m_right {nullptr};
};

class BST {

private:
    NodePtr m_root{nullptr};

public:
    //Basic routines to get to recursive methods inside binary search tree class
    void insert(string word);
    bool search(string word);

    //Calculation functions
    static int max(int a, int b);
    static int height(NodePtr& Node);
    static bool my_comp(string a, string b);

protected:
    //Recursive functions
    NodePtr insert(string word, Node*&);
    NodePtr search(NodePtr& node, string word);

    //Balancing functions
    NodePtr right_rotate(NodePtr& y);
    NodePtr left_rotate(NodePtr& x);
    int get_balance(NodePtr& N);

    //Printing functions
    void print_tree(ostream& output, NodePtr& node, int indent);
    friend ostream& operator<<(ostream& output, BST& bst);
};

ostream& operator<<(ostream& output, BST& bst);

#endif //ASSIGNMENT_3_BINARYSEARCHTREE_H