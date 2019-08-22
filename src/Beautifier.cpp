//
// Created by conor on 2019-05-06.
//

#include <algorithm>
#include <fstream>
#include <iostream>
#include "Beautifier.h"
#include "KeyWordTries.h"

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
    if(text->size() == 0){
        cout << "Text file was found to be empty." << endl;
        return false;
    }
    if(code->size() == 0){
        cout << "Code file was found to be empty." << endl;
        return false;
    }

    TernaryTrie excludeList;
    KeyWordTries::fillWithAllKeyWords(excludeList);
    code->fillTrie(excludeList);
    text->underscoreBlackList(excludeList);
    
    text->uniquify();
    evenEmOut();

    
    //at this point everything should be all well and dandy just need to put them into the output file
    ofstream out(args->getOut());
    if(!out){
        cout << "Could not find " << args->getOut() << "."<<endl;
        return false;
    }

    //todo: check if overwriting
    if(args->isSingleFile()){
        outputPrePros(out);
        outputDefinitions(out);
        outputCFile(out);
    }else{
        ofstream hout(args->getHout());
        if(!hout){
            cout << "Could not find " << args->getHout() << "."<<endl;
            return false;
        }
        outputPrePros(hout);
        outputDefinitions(hout);
        out << "/* Include Definitions */" << endl;
        out << "#include \"" << args->getHout() << "\"" << endl;
        out << endl;
        outputCFile(out);
    }

    return true;
}

bool Beautifier::count(){
    if(!text)return false;
    if(!code)return false;
    text->uniquify();

    //expand it out as far as possible
    int i = 200;
    while(code->expand(i))i*=2;

    cout << args->getCode() << " has " << code->size() << " words." << endl;
    cout << args->getTxt() << " has " << text->size() << " words." << endl;
    return true;
}

//todo: don't forget this function
bool Beautifier::checkIfOverRiding(ofstream &out, ofstream &hout) {
    return true;
}

void Beautifier::outputDefinitions(ofstream &out) {
    out << "/* Define all the words in the text file */" << endl;
    vector<string> identifiers = text->getVector();
    vector<string> vals = code->getVector();
    unsigned len = identifiers.size();
    for(int i = 0; i < len; i++){
        string identifier = identifiers[i];
        while(identifier[identifier.length()-1] == '\n')identifier.pop_back();
        out << "#define " << identifier << " " << vals[i] << endl;
    }
    out << endl; // give a little space for next section
}

void Beautifier::outputPrePros(ofstream &out) {
    if(code->getPrePros().empty())return;
    out << "/* preprocessor functions found in source file */" << endl;
    out << code->getPrePros() << endl;
}

void Beautifier::outputCFile(ofstream &out) {
    vector<string> textWords = text->getVector();
    for(const auto &word : textWords){
        out << word;
        if(word[word.length()-1] != '\n')out << " ";

    }
}


