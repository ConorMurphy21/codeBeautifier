//
// Created by conor on 2019-05-04.
//

#include "ArgumentFactory.h"

Arguments* ArgumentFactory::getArguments(int argc, char **argv) {
    /*TODO: ways to make interface better:
     * - add inplace flag (ie overwrite the original file)
     * - add option to choose new file name
     */

    Arguments* args = new Arguments();

    if(argc != 3){
        args->setValid(false);
        return args;
    }

    args->setCode(argv[1]);
    args->setTxt(argv[2]);
    args->setOut(argv[1]);

    return args;

}
