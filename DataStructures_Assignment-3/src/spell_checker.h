//
// Created by Matt on 3/20/2022.
//

#ifndef ASSIGNMENT_3_SPELL_CHECKER_H
#define ASSIGNMENT_3_SPELL_CHECKER_H

#include <iostream>
#include <vector>
#include "binarysearchtree.h"

using namespace std;

class SpellChecker{

public:
    //Variables to hold words and outputting for reading from files and outputting
    string m_word;
    string m_check_word;
    string m_output;

    int m_count;

    //Variables to hold file names
    string m_dictionary_file;
    string m_document;
    string m_tree;

    //Array variable to hold word list from dictionary
    string m_word_list[52];

    //Constructor
    SpellChecker();

    //Routines
    void main_routine(char **argv);
    void open_dictionary(char **argv, BST &bst);
    void open_document(vector<string>& values);
    void output_misspelled(std::vector<string>& values, BST &bst);
};

#endif //ASSIGNMENT_3_SPELL_CHECKER_H