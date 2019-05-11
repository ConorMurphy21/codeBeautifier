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
    //2's : ! % & * + - / : = ^ | (these sometimes need to be grouped)
    //3's : " ' (just skip words that start with these) they already as reduced as possible
    //4's : < > these unfortunately have  <<= and >>= which sucks
    char specialChars[256] = {
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //15
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //31
                           0, 2, 3, 0, 0, 2, 2, 3, 1, 1, 2, 2, 0, 2, 0, 2, //47
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 4, 2, 4, 1, //63
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //79
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 2, 0, //95
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //111
                           0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 1, 0  //127

    };

    //keep expandin
    while(code.size() < expectedSize){

        int lastViewed = 0;

        for(int i = 0; i < code.size(); i++){

            string word = code[i];

            for(int j = 0; j < word.length(); j++){

                if(lastViewed){



                }else {


                    switch (specialChars[word[j]]) {

                        case 1:
                            //this one is ez, just break before and after it and move on

                        case 2:
                            //this one is the hardest as these have special chars that have to come next

                        case 3:
                            //this case is special too, gotta cut before the quote, and after the second quote

                        default:
                            //this case ain't special at all
                            break;
                    }


                    lastViewed = specialChars[word[j]];
                }
            }


        }

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
