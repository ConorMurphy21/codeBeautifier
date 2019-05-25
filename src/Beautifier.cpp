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
            if(!txt.condense(code.size())){
                return code.condense(txt.size());
            }
        }
    }
    return true;

}

bool Beautifier::create(Arguments* args){


    string txtfn = args->getTxt();
    auto txtWords = TextObj::create(txtfn);
    if(!txtWords)return false;
    string codefn = args->getCode();
    auto codeWords = CodeObj::create(codefn);
    if(!codeWords)return false;
    txtWords->uniquify();

    if(txtWords->size() == 0){
        return false;
    }
    if(codeWords->size() == 0){
        return false;
    }
    evenEmOut(*txtWords,*codeWords);

    delete txtWords;
    delete codeWords;
    return true;
}

