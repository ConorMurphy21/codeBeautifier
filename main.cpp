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

    //probably should have just made argument factory take a vector this is a mess
    const char* argvv[argc];
    for(int i = 0; i < argc; i++)argvv[i] = argv[i];

    Arguments* args = ArgumentFactory::getArguments(argc, argvv);
    if(!args)return 1;

    Beautifier beautifier(args);

    bool success;

    if(args->isCreate()){
        success = beautifier.create();
    }else{
        success = beautifier.count();
    }
    delete args;

    return !success;
}
