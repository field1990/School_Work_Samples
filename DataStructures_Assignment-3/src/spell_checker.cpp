//
// Created by Matt on 3/20/2022.
//

#include "spell_checker.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//Constructor
SpellChecker::SpellChecker() : m_count(0), m_output("") {};

void SpellChecker::main_routine(char *argv[]) {

    //Creating the new Binary Search Tree Object
    BST bst;

    //Call the open_dictionary routine to open up the dictionary file
    open_dictionary(argv, bst);

    //Create a vector to store valid words in the file
    vector<string> values;

    //Call the open_document routine to open the document that's going to be spell checked
    open_document(values);

    //Call the output_misspelled routine to
    output_misspelled(values, bst);

}

void SpellChecker::open_dictionary(char *argv[], BST &bst) {

    //Check to see if there's an argv parameter provided, aka a file of a maze provided by the user
    if (!argv[1]) {
        m_dictionary_file = "../tests/dictionary.txt";
    } else {
        m_dictionary_file = argv[1];
    }

    ifstream my_read_dictionary(m_dictionary_file);

    if (my_read_dictionary.is_open()) {
        //Populate the array and get a count of the length of the dictionary
        while (getline(my_read_dictionary, m_word)) {
            m_word_list[m_count] = m_word;
            m_count++;
        }

        //Going through the array of words and inserting them into the binary search tree
        for (int i = 0; i < m_count; i++) {
            bst.insert(m_word_list[i]);
        }

        //In case you want to ouput the binary search tree to the console
        //cout << bst << endl;

    } else {
        cout << "Can't open. Please provide a valid dictionary txt file";
    }
    my_read_dictionary.close();
}

void SpellChecker::open_document(vector<string> &values) {

    cout << "Please enter the name of the file you wish to spell check: " << endl;
    cin >> m_document;

    //Modify the document being read to be placed inside the tests folder directory
    ifstream my_read_document("../tests/" + m_document);

    //Check to make sure that file is able to open, if not use default example
    if (my_read_document.is_open()) {
        cout << "Spell checking " << m_document << endl;
    } else {
        cout << "File does not exist. Using default test.txt" << endl;
        m_document = "../tests/test.txt";
        my_read_document.open(m_document);
    }

    //Go through the document provided and filter out proper words. Once done push them to the vector
    while (my_read_document >> m_check_word) {
        m_output = "";

        for (int i = 0; i < m_check_word.size(); i++) {
            if ((m_check_word[i] >= 'a' && m_check_word[i] <= 'z') ||
                (m_check_word[i] >= 'A' && m_check_word[i] <= 'Z')) {
                m_output += tolower(m_check_word[i]);
            }
        }
        m_check_word = m_output;
        //https://www.programiz.com/cpp-programming/examples/remove-characters-string

        if (m_check_word != "") {
            values.push_back(m_check_word);
        }
    }
}

//Output Misspelled function that checks the vector against the binary search tree and outputs the contents of the tree to a file
void SpellChecker::output_misspelled(vector<string> &values, BST &bst) {
    cout << "\nMisspelled Words: \n" << endl;

    //Go through the vector and check to see if they are in the binary search tree. If they're not then output the word to the console
    for (int i = 0; i < values.size(); i++) {
        if (bst.search(values.at(i)) == false) {
            cout << values.at(i) << endl;
        }
    }
    //Check with user to see what name they want the new name of the file to be. If not writes it to the default file
    cout << "\nWhat is the name of the file that you wish to save the output of the binary search tree to?" << endl;
    cin >> m_tree;

    if (m_tree.size() > 4 && (m_tree.substr(m_tree.size() - 3) == "txt")) {
        cout << "Outputting to the following file: " << m_tree << endl;
    } else {
        cout << "File name not given the proper .txt extension. Using the default output.txt file" << endl;
        m_tree = "output.txt";
    }
    //http://www.cplusplus.com/forum/beginner/268674/

    ofstream output_tree_file;
    output_tree_file.open(m_tree);

    //Outputting the binary search tree to the file
    output_tree_file << bst;

    output_tree_file.close();
}