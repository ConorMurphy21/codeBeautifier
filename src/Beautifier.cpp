//
// Created by conor on 2019-05-06.
//

#include <algorithm>
#include <fstream>
#include <iostream>
#include "Beautifier.h"

Beautifier::Beautifier(Arguments *args) : args(args){
    string txtfn = args->getTxt();
    text = TextObj::create(txtfn);
    string codefn = args->getCode();
    code = CodeObj::create(codefn);
}
Beautifier::~Beautifier() {
    delete text;
    delete code;
}

bool Beautifier::evenEmOut(){
    if(code->size() > text->size()){
        return code->condense(text->size());
    }else if(code->size() < text->size()){
        if(!code->expand(text->size())){
            if(!text->condense(code->size())){
                return code->condense(text->size());
            }
        }
    }
    return true;

}

bool Beautifier::create(){
    if(!text)return false;
    if(!code)return false;
    if(text->size() == 0)return false;
    if(code->size() == 0)return false;
    evenEmOut();

    return true;
}

bool Beautifier::count(){
    if(!text)return false;
    if(!code)return false;
    cout << args->getCode() << " has " << code->size() << " words. " << endl;
    cout << args->getTxt() << " has " << text->size() << " words. " << endl;
    return true;
}


