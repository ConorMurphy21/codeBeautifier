//
// Created by conor on 2019-05-11.
//

#include <iostream>
#include "TextObj.h"

TextObj* TextObj::create(string& filename){
    //open file
    ifstream in(filename);
    if(!in){
        cout << filename << " could not be opened" << endl;
        return nullptr;
    }
    auto arr = new vector<string>();
    string line;

    while(std::getline(in,line)){
        int length = line.length();
        string word;
        for(int i = 0; i < length; i++){
            char c = line[i];
            //basically checks if the character can be a valid identifier
            //commands are in likely order, so although this statement looks long, chances are
            //it will never have to check if it is a number and is not the start of the word
            if((isalpha(c) || c == '_') || (i != 0 && line[i] != ' ' && isdigit(c))){
                //if is proper identifier char add to word
                word += c;
            }else if(c == ' '){
                //if is space, push word and start over
                if(!word.empty())arr->push_back(word);
                word.clear();
            }
        }

        //wierd but not uncommon edge case where sentence ends with space needs to be covered
        if(word.empty()){
            arr->at(arr->size()-1) += '\n';
        }else {
            word += '\n';
            if (!word.empty())arr->push_back(word);
        }
    }

    return new TextObj(arr);
}

//check if it's ok to tie index and index + 1 together;
bool TextObj::isOkTie(int index){
    if(index < 0) {
        return false;
    }else if(index >= list->size()-1){
        return false;
    }else{
        int last = list->at(index).length()-1;
        return (list->at(index)[last] != '\n');
    }
}

//desc: chooses whether to tie the index passed in to the word before or after it
//if both of them have \n characters then it returns -1
//this is because we want to avoid disrupting the given format of the text file
//so we do not want to have to remove a new line character but we cannot have an identifier
//with a new line character in it
int TextObj::pickIndex(int index){
    if(isOkTie(index-1))return index-1;
    else if(isOkTie(index))return index;
    else return -1;
}

//desc: find first index of the key past in (this is not generic because we say
//that the two strings are equal even if there is a \n character at the end
// ie "foo" == "foo\n" is true
//pre: none
//post: none of the parameters are changed
int TextObj::findInd(string& key){
    int size = list->size();
    if(key[key.size()-1] == '\n')key.pop_back();
    for(int i = 0; i < size; i++){
        string word = list->at(i);
        if(word == key)return i;
        if(word[word.length()-1] == '\n'){
            if(key == word.substr(0,word.length()-1))return i;
        }
    }
    return -1;
}

void TextObj::uniquify() {

    int len = list->size();
    bool toggle = true; //we want to spread out the underscores so they aren't all in one place
    //for aesthetic reasons. so we are going to toggle where we put the underscore,
    //on the first one, or on the end one. Obviously not a perfect solution,
    //but it's an improvement from just all at the end or start
    for(int i = 0; i < len; i++){
        string word = list->at(i);

        int pos = findInd(word);

        if(pos != i){
            int index;
            //we need to do some tomfoolery to make them different but still aesthetic

            int one = pos, two = pos;
            if(toggle) two = i;
            else one = i;

            //todo: ok this whole part right here needs to be redone
            //we check too much for the problems with one and too
            //instead we need to just rank each of the 4 possible index's and choose the best one
            //and then have special cases if the best one ranks too low (because either
            // it is still not unique or it is alone with enters)
            if((index = pickIndex(one))!= -1){
                joinWords(index,'_');
                toggle = !toggle;
            }else if((index = pickIndex(two))!= -1){
                joinWords(index,'_');
            }else{
                if(one != 0){
                    list->at(one-1).pop_back();
                    joinWords(one-1,'_');
                    toggle = !toggle;
                }else if(one != list->size()-1){
                    list->at(one).pop_back();
                    joinWords(one,'_');
                    toggle = !toggle;
                }else if(two != 0){
                    list->at(two-1).pop_back();
                    joinWords(two-1,'_');
                }else{
                    list->at(two).pop_back();
                    joinWords(two,'_');
                }
            }
            i--;
            len--;
        }
    }
}

bool TextObj::condense(int expectedSize) {

    return false;
}
