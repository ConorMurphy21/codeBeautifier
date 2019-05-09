//
// Created by conor on 2019-05-04.
//

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include "ArgumentFactory.h"
#include "Beautifier.h"

using namespace std;

int main(int argc, char** argv){

    //ok so here's the deal

    //we can make the code part as long as we want
    //but each word can be made into as much code as needed
    //so the txt file has to be substantially bigger, because each
    //repeat word has to be tied to another word to keep it unique
    //also any keywords can not be used, like return, if or using

    //first step:
    //put both files into arrays of words

    //second step:
    //reduce the txt file so all of the words are unique (while maintaining new lines)

    //third step:
    //reduce the code array by joining lines together

    //then just sender back

    //ok the objects we will need:
    //an argument factory, for creating the arguments from what are past in
    //an argument object for use being created and used
    //a beautifier (the main)

    //maybe turn punctuations into semicolons later

    Arguments* args = ArgumentFactory::getArguments(argc, argv);

    Beautifier beautifier;
    beautifier.create(args);


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

    cout << "1's :";
    for(unsigned char c = 0; c < 128; c++){
        if (specialChars[c] == 1) cout <<" "<< c;
    }
    cout << "\n2's :";
    for(unsigned char c = 0; c < 128; c++){
        if (specialChars[c] == 2) cout <<" "<< c;
    }
    cout << "\n3's :";
    for(unsigned char c = 0; c < 128; c++){
        if (specialChars[c] == 3) cout <<" "<< c;
    }
    //ok at this point all we gotta do is finesse the size of each word array
    //to be the same size, then send'er back


}
