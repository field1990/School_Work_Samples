//
// Created by Matt on 3/11/2022.
//

#include <iomanip>
#include "binarysearchtree.h"

//Height function that returns the height of the node
int BST::height(NodePtr& Node){
    if(Node == nullptr){
        return 0;
    }
    return Node->m_height;
}

//Max function that determines the maximum value of two integers
int BST::max(int a, int b){
    return (a > b)? a : b;
}

//Method used to compare the alphabetical order of words
bool BST::my_comp(string a, string b) {
    return a<b;
}
//https://www.includehelp.com/cpp-programs/sort-names-in-an-alphabetical-order.aspx

//Function that rotates the subtree to the right with y
NodePtr BST::right_rotate(NodePtr& y){
    //Create two nodes, one temp and one that is going to be moved
    Node *x = y->m_left;
    Node *T2 = x->m_right;

    //Perform the rotation
    x->m_right = y;
    y->m_left = T2;

    //Update the m_heights
    y->m_height = max(height(y->m_left),height(y->m_right)) + 1;
    x->m_height = max(height(x->m_left),height(x->m_right)) + 1;

    //Return the new node that was modified
    return x;
}

//Function that rotates the subtree to the right with x
NodePtr BST::left_rotate(NodePtr& x){
    //Create two nodes, one temp and one that is going to be moved
    Node *y = x->m_right;
    Node *T2 = y->m_left;

    //Perform the rotation
    y->m_left = x;
    x->m_right = T2;

    //Update the m_heights
    x->m_height = max(height(x->m_left), height(x->m_right)) + 1;
    y->m_height = max(height(y->m_left), height(y->m_right)) + 1;

    //Return the new node that was modified
    return y;
}

//GetBalance function that readjusts the height of the nodes
int BST::get_balance(NodePtr& N){
    if (N == nullptr){
        return 0;
    }
    return height(N->m_left) - height(N->m_right);
}

//Rercursive insert
void BST::insert(string word) {
    //entry point
    m_root = insert(word, m_root);
}

//Recurive insert for others beside the start
Node* BST::insert(string word, Node*& node){
    if (node == nullptr){
        node = new Node();
        node->m_data = word;
        node->m_height = 1;
        return node;
    } if (word < node->m_data) {
        //Go to the left side
        node->m_left = insert(word, node->m_left);
    } else if (word > node->m_data) {
        //Go to the right side
        node->m_right = insert(word, node->m_right);
    } else {
        //Trying to insert node of duplicate value
        cout << "Node value " << node->m_data << " already exists." << endl;
        return node;
    }

    //Update the m_height of this node
    node->m_height = 1 + max(height(node->m_left), height(node->m_right));

    //Check to see if the tree is balanced
    int balance = get_balance(node);

    // Left Left Case
    if (balance > 1 && word < node->m_left->m_data) {
        return right_rotate(node);
    }
    // Right Right Case
    if (balance < -1 && word > node->m_right->m_data) {
        return left_rotate(node);
    }
    // Left Right Case
    if (balance > 1 && word > node->m_left->m_data)
    {
        node->m_left = left_rotate(node->m_left);
        return right_rotate(node);
    }
    // Right Left Case
    if (balance < -1 && word < node->m_right->m_data)
    {
        node->m_right = right_rotate(node->m_right);
        return left_rotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

//Print function to go through the binary search tree and print its contents
void BST::print_tree(ostream& output, NodePtr& node, int indent) {
    if (node != nullptr) {
        print_tree(output, node->m_right, indent + 8); //Indenting by 8 spaces, it could be any number, just to make it look good
        output <<setw(indent) << node->m_data << endl; //Set the width with setw, import iomanip
        print_tree(output, node->m_left, indent + 8);
    }
}

ostream& operator<<(ostream& output, BST& bst) {
    bst.print_tree(output, bst.m_root, 0);

    return output;
}

//Search function used to get to the recursive search function. Provides a boolean value based on if the node exists or not
bool BST::search(string word) {
    //entry point
   NodePtr result = search(m_root, word);

   if(result == nullptr){
       return false;
   } else{
       return true;
   }
}

//Search function to check to see if the word is in the binary search tree
NodePtr BST::search(NodePtr& node, string word){

    //Go through the binary search tree to try and find the corresponding node if it exists
    if(node == nullptr){
        return nullptr;
    }
    if (node->m_data == word){
       return node;
    }
    else if (my_comp(word, node->m_data) == 1){
       return search(node->m_left, word);
    }
    else if (my_comp(word, node->m_data) == 0){
       return search(node->m_right, word);
    }
   //https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/
   //https://hub.packtpub.com/binary-search-tree-tutorial/
}
//https://www.geeksforgeeks.org/avl-tree-set-1-insertion/