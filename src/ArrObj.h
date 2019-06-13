//
// Created by conor on 2019-05-11.
//

#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;
class ArrObj{

public:

    unsigned size() const{
        return list.size();
    }

    vector<string> getVector() const{
        return list;
    }

    // desc: connects the word at the index, and at the index+1 together with an underscore
    // and places it in the relative spot
    // returns if the function is successful
    bool joinWords(unsigned int index, char join){
        if(index + 1 >= list.size()) return false;
        list[index] = list[index] + join + list[index+1]; //put the tied words together in list[index]
        list.erase(list.begin()+index+1,list.begin()+index+2); //remove list[index+1]
        return true;
    }

    //desc: break word, at index of character into two words
    //returns if the function successfully split a word
    bool breakWordAtIndex(unsigned wordIndex, unsigned index){
        //out of bounds
        if(wordIndex >= list.size())return false;
        if(index == 0)return false;
        string word = list[wordIndex];
        //the last index is useless as there's nothing
        if(index >= word.length())return false;

        string first = word.substr(0,index);
        string second = word.substr(index);

        list.at(wordIndex) = second;
        list.insert(list.begin()+wordIndex,first);
        return true;
    }

    //this should be protected, but I need it for testing
    explicit ArrObj(vector<string>& list){
        this->list = list;
    }

protected:
    vector<string> list;

    /*
    explicit ArrObj(vector<string>& list){
        this->list = list;
    }*/
};
