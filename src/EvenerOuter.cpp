//
// Created by conor on 2019-05-06.
//


#include <iostream>
#include "EvenerOuter.h"


bool EvenerOuter::evenEmOut(vector<string> &code, vector<string> &text) {
    int cs = code.size(), ts = text.size();
    if(cs > ts){
        return condenseCode(code, text.size());
    } else if(ts > cs){
        if(!expandCode(code,text.size())){
            return condenseText(text,code.size());
        }
        //already even boi
    }else return true;
}

bool EvenerOuter::expandCode(vector <string> &code, int expectedSize) {

    //todo: something to remember when writing this function, a quoted section needs to stay together
    //ok so I painstakingly went through every ascii characters to see if they were immediately seperable: 1
    //extrawork seperable: 2, quotes: 3, everything else 0
    //1's : ( ) ; ? [ ] { } ~ (as far as I know these never need to be grouped)
    //2's : ! % & * + - / : < = > ^ | (these sometimes need to be grouped)
    //3's : " ' (this shit I just have to worry about)
    char specialChars[256] = {
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //15
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //31
                           0, 2, 3, 0, 0, 2, 2, 3, 1, 1, 2, 2, 0, 2, 0, 2, //47
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 2, 2, 2, 1, //63
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //79
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 2, 0, //95
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //111
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 1, 0  //127

    };

    //keep expandin
    int i=0;
    while(code.size() < expectedSize){


    }
    return false;
}

bool EvenerOuter::condenseCode(vector<string> &code, int expectedSize) {
    for(int i = 0; i < expectedSize; i++){

    }
    return false;
}

bool EvenerOuter::condenseText(vector<string> &text, int expectedSize) {
    for(int i = 0; i < expectedSize; i++){

    }
    return false;
}
