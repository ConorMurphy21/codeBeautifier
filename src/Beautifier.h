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

    bool evenEmOut();

    Arguments* args;

    CodeObj* code;
    TextObj* text;


public:

    explicit Beautifier(Arguments* args);

    ~Beautifier();

    bool create();

    bool count();

};



