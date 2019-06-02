//
// Created by conor on 2019-05-11.
//

#include <iostream>
#include "CodeObj.h"


CodeObj* CodeObj::create(string& filename) {
    //open file
    string prePros;
    ifstream in(filename);
    if(!in){
        cout << filename << " could not be opened" << endl;
        return nullptr;
    }
    vector<string> arr;
    string line;
    bool commented, quoted, inLine;
    commented = quoted = inLine = false;
    char quote = 0;

    while(std::getline(in,line)){
        int length = line.length();
        string word;

        //throw it in prePros and not in the vector
        if(line[0] == '#'){
            line += '\n';
            prePros.append(line);
            continue;
        }

        for(int i = 0; i < length; i++){
            char c = line[i];

            if(quoted){
                word += c;
                if(c == quote){
                    //push back the quote
                    if (!word.empty()) arr.push_back(word);
                    word.clear();
                    //end quote
                    quoted = false;
                }
                continue;
            }else if(commented){
                //if it's the end of a quote
                if(i != length && c == '*' && line[i+1] == '/'){
                    i++;
                    commented = false;
                }
                //if commented we don't want to append any characters to the word
                continue;
            }

            if(c == '\"' || c == '\''){
                quoted = true;
                if(!word.empty())arr.push_back(word);
                word.clear();
                word += c;
                quote = c;

            }else if(c == '/') {
                if (i != length) {
                    if (line[i+1] == '/') {
                        inLine = true;
                        break;
                    } else if (line[i+1] == '*') {
                        commented = true;
                        i++;
                        continue;
                    }
                }
            }else if(c == ' '){
                if(!word.empty())arr.push_back(word);
                word.clear();
            }else{
                word += c;
            }
        }

        if(!inLine && !commented) {
            if (!word.empty())arr.push_back(word);
            word.clear();
        }
        inLine = false;
    }
    return new CodeObj(arr, prePros);
}

//todo: this needs hella testing
//it works on the file I gave it but damn I am scared
bool CodeObj::expand(unsigned int expectedSize) {

    int last = 0;
    bool expanded = false;
    for(int i = 0; i < list.size(); i++){
        string word = list[i];

        for(int j = 0; j < word.size(); j++){

            int type = specialChars[word[j]];

            bool br = false;

            if(last){

                switch (last){
                    case 1:
                        breakWordAtIndex(i,j+1);
                        break;
                    case 2:
                        if(type < 2)breakWordAtIndex(i,j+1);
                        if(type == 2)breakWordAtIndex(i,j+2);
                        break;
                }
                //so last will = 0
                br = true;
                last = 0;
            } else {

                switch (type) {
                    case 1:
                    case 2:
                        if(breakWordAtIndex(i, j)) {
                            br = true;
                            last = type;
                        }
                        else last = 0;

                        break;
                    case 3:
                        br = true;
                        break;
                    case 4:
                    default:
                        last = type;
                        break;

                }
            }

            if(list.size() == expectedSize){
                expanded = true;
                break;
            }
            if(br)break;
        }
        if(expanded)break;
    }


    return expanded;
}

bool CodeObj::condense(unsigned expectedSize) {

    if(expectedSize == 0)return false;

    while(list.size() > expectedSize){

        int size = list.size();
        unsigned min = list[0].length();
        for(int i = 1; i < size; i++) {
            if (list[i].length() < list[min].length())min = i;
        }

        unsigned tieInd;
        if (min == 0) tieInd = min;
        else if (min == list.size()-1){
            tieInd = min-1;
        }else{
            tieInd = (list[min-1] < list[min+1]) ? min-1 : min+1;
        }

        joinWords(tieInd,' ');

    }
    //should basically never fail
    return true;
}

void CodeObj::fillTrie(TernaryTrie &newTrie) {

    for(const auto & word : list){

        trie.resetState();
        bool alphaWordStarted = false;
        int last = 0;
        for(const char c : word){
            //if the word has not started, and the character is not alpha continue
            if(!isalpha(c) || c != '_'){
                if(!alphaWordStarted)continue;
                break;
            }
            alphaWordStarted = true;
            if(!(last = trie.search(c)))break;

        }
        //could technically optimize the ternary trie, but tbh it should be a very small trie and no big deal
        if(last == 2) newTrie.putWord(word);

    }
}

void CodeObj::replaceWithRedefs(TernaryTrie &redef, const string &redefPrefix) {

    for(auto & word : list){

        redef.resetState();
        bool alphaWordStarted = false;
        int last = 0;


        int len = word.length();
        unsigned i, beforeLength = 0;
        for(i = 0; i < len; i++){
            char c = word[i];
            //if the word has not started, and the character is not alpha continue
            if(!isalpha(c) || c != '_'){
                if (!alphaWordStarted)continue;
                break;
            }else if(!alphaWordStarted){
                beforeLength = i;
                alphaWordStarted = true;
            }
            if(!(last = redef.search(c)))break;

        }
        if(last == 2) {
                                    //before the keyword      //toMakeItUncommon  //The Keyword                         //What is after
                                    //in the example of something like: }else{
                                    // }                    +   REDEF_      +   else + {
                                    //to give }REDEF_else{
            string replacement = word.substr(0,beforeLength) + redefPrefix + word.substr(beforeLength,i-beforeLength) + word.substr(i);
            word = replacement;
        }

    }
}
