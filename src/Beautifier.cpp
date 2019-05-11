//
// Created by conor on 2019-05-06.
//

#include <algorithm>
#include <fstream>
#include <iostream>
#include "Beautifier.h"
#include "CodeObj.h"
#include "TextObj.h"


void Beautifier::create(Arguments* args){


    string txtfn = args->getTxt();
    auto txtWords = TextObj::create(txtfn);
    string codefn = args->getCode();
    auto codeWords = CodeObj::create(codefn);

    txtWords->uniquify();

    //ok at this point we just need to make the arrays the same size
}

