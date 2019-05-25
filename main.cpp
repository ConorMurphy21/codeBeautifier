//
// Created by conor on 2019-05-04.
//

#include <vector>
#include <iostream>
#include "ArgumentFactory.h"
#include "Beautifier.h"

using namespace std;

int main(int argc, char** argv){

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
    if(!args->isValid())return 5;

    Beautifier beautifier;
    bool success = beautifier.create(args);

    delete args;

    return !success;
}
