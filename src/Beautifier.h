//
// Created by conor on 2019-05-06.
//


#pragma once

#include "Arguments.h"
#include "CodeObj.h"
#include "TextObj.h"

using namespace std;
class Beautifier {

private:

    Arguments* args;
    CodeObj* code;
    TextObj* text;

    //desc: expands and condenses the code and text until the text and code has the same number of words
    //returns whether it is a success
    bool evenEmOut();

    //desc: checks if the file names given already exist
    bool checkIfOverRiding(ofstream &out, ofstream &hout);

    //desc: outputs the preprocessor functions found in the file into the designated output destination
    void outputPrePros(ofstream &out);

    //desc: outputs all of the definitions into the designated output destination
    void outputDefinitions(ofstream &out);

    //desc: outputs the text word by word
    void outputCFile(ofstream &out);


public:

    //constructor
    explicit Beautifier(Arguments* args);

    //destructor
    ~Beautifier();

    //creates a beautiful file from the arguments
    bool create();

    //counts the number of words in both files
    bool count();

};



