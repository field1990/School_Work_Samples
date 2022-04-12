#include <iostream>
#include <fstream>
#include <cstring>
#include "spell_checker.h"

using namespace std;

int main(int argc, char* argv[]) {

    //Create an instance of the Spell_Checker class
    SpellChecker spell_checker;

    //Check to see if there's any commandline arguments. If not let the user know that the default will be used
    if (argc > 1) {
        if (strlen(argv[1]) > 4 && strcmp(strrchr(argv[1], '.'), ".txt") != 0 && argv[1]){
            cout << "The file provided is not in the proper format. Invalid argument. Using dictionary.txt instead" << endl;
        }
        else {
            cout << "You are reading in the following dictionary: " << argv[1] << endl;
        }
    }
    else {
        cout << "No dictionary file provided. dictionary.txt is the dictionary being used" << endl;
    }

    //Run the main_routine for SpellChecker
    spell_checker.main_routine(argv);

    return 0;
}