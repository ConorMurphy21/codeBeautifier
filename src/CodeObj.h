//
// Created by conor on 2019-05-11.
//

#pragma once

#include "ArrObj.h"
#include <fstream>

class CodeObj : public ArrObj{

private:
    //all prePros functions will be stored in here
    string prePros;

    //todo: something to remember when writing this function, a quoted section needs to stay together
    //ok so I painstakingly went through every ascii characters to see if they were immediately seperable: 1
    //extrawork seperable: 2, quotes: 3, everything else 0
    //1's : ( ) ; ? [ ] { } ~ (as far as I know these never need to be grouped)
    //2's : ! % & * + - / : = ^ | (these sometimes need to be grouped)
    //3's : " ' (just skip words that start with these) they already as reduced as possible
    //4's : < > these unfortunately have  <<= and >>= which sucks
    const char specialChars[256] = {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //15
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //31
            0, 2, 3, 0, 0, 2, 2, 3, 1, 1, 2, 2, 0, 2, 0, 2, //47
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 4, 2, 4, 1, //63
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //79
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 2, 0, //95
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //111
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 1, 0  //127

    };

public:

    static CodeObj* create(string& filename);

    explicit CodeObj(vector<string>* list, string& prePros):ArrObj(list){
        this->prePros = prePros;
    }

    bool condense(int expectedSize);

    bool expand(int expectedSize);
};


