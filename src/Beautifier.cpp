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
        cout << "text file was found to be empty." << endl;
        return false;
    }
    if(code->size() == 0){
        cout << "code file was found to be empty." << endl;
        return false;
    }

    TernaryTrie blacklist;
    bool underscore = true;
    bool redef = true;
    switch(args->getBlacklist()){
        case Arguments::ALL:
            KeyWordTries::fillWithAllKeyWords(blacklist);
            redef = false;
            break;
        case Arguments::OPERATORS:
            KeyWordTries::fillWithOperators(blacklist);
            break;
        case Arguments::NONE:
            underscore = false;
            break;
    }
    if(underscore)text->underscoreBlackList(blacklist);
    
    text->uniquify();
    evenEmOut();

    vector<string> redefinitionList;
    if(redef) {
        //create a keyWord trie
        TernaryTrie keyWordsUsed, redefinitionTrie;
        code->fillTrie(keyWordsUsed);

        text->createKeyWordList(keyWordsUsed, redefinitionTrie, redefinitionList);
        code->replaceWithRedefs(redefinitionTrie, REDEFINITION_PREFIX);
    }
    
    //at this point everything should be all well and dandy just need to put them into the output file
    ofstream out(args->getOut());
    if(!out){
        cout << "Could not find " << args->getOut() << "."<<endl;
        return false;
    }

    if(args->isSingleFile()){
        if(redef)outputRedefinitions(out,redefinitionList);
        outputDefinitions(out);
        outputPrePros(out);
        outputCFile(out);
    }else{
        ofstream hout(args->getHout());
        if(!hout){
            cout << "Could not find " << args->getHout() << "."<<endl;
            return false;
        }

        //if(!checkIfOverRiding(out,hout))return false;

        outputRedefinitions(hout,redefinitionList);
        outputDefinitions(hout);
        outputPrePros(hout);
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

    cout << args->getCode() << " has " << code->size() << " words." << endl;
    cout << args->getTxt() << " has " << text->size() << " words." << endl;
    return true;
}

//todo: don't forget this function
bool Beautifier::checkIfOverRiding(ofstream &out, ofstream &hout) {
    return true;
}

void Beautifier::outputRedefinitions(ofstream &out, vector<string> &redefList) {
    out << "/* Redefine keywords found in the text file */" << endl;
    for(const auto &word : redefList){
        out << "#define " << word << " " << REDEFINITION_PREFIX << word << endl;
    }
    out << endl; //give a little space for next section
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


