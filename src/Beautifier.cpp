//
// Created by conor on 2019-05-06.
//

#include <algorithm>
#include <fstream>
#include <iostream>
#include "Beautifier.h"
#include "CodeObj.h"
#include "TextObj.h"

bool evenEmOut(TextObj& txt, CodeObj& code){
    if(code.size() > txt.size()){
        return code.condense(txt.size());
    }else if(code.size() < txt.size()){
        if(!code.expand(txt.size())){
            return txt.condense(code.size());
        }
    }
    return true;

}

bool Beautifier::create(Arguments* args){


    string txtfn = args->getTxt();
    auto txtWords = TextObj::create(txtfn);
    string codefn = args->getCode();
    auto codeWords = CodeObj::create(codefn);
    txtWords->uniquify();
    //evenEmOut(*txtWords,*codeWords);

    return true;
}

