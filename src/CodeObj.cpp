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
    auto arr = new vector<string>();
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
                    if (!word.empty()) arr->push_back(word);
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
                if(!word.empty())arr->push_back(word);
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
                if(!word.empty())arr->push_back(word);
                word.clear();
            }else{
                word += c;
            }
        }

        if(!inLine && !commented) {
            if (!word.empty())arr->push_back(word);
            word.clear();
        }
        inLine = false;
    }
    return new CodeObj(arr, prePros);
}