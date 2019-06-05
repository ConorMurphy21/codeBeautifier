//
// Created by conor on 2019-05-06.
//


#pragma once

#include "Arguments.h"
#include "CodeObj.h"
#include "TextObj.h"

#define REDEFINITION_PREFIX "REDEF_"

using namespace std;
class Beautifier {

private:

    Arguments* args;
    CodeObj* code;
    TextObj* text;

    bool evenEmOut();

    bool checkIfOverRiding(ofstream &out, ofstream &hout);

    void outputRedefinitions(ofstream &out, vector<string> &redefList);

    void outputDefinitions(ofstream &out);

    void outputPrePros(ofstream &out);

    void outputCFile(ofstream &out);


public:

    explicit Beautifier(Arguments* args);

    ~Beautifier();

    bool create();

    bool count();

};



