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

private:
    struct byLength {
        bool operator()(const string &a, const string &b) const {
            return a.length() > b.length();
        }
    };

public:


    unsigned size() {
        return list.size();
    }

    bool condense(int expectedSize){

        //make deep copy of list
        vector<string> heap = list;
        make_heap(heap.begin(),heap.end(),byLength());



        //ok we made a heap, now just combine all of

    }

// todo: move these to another object because they are basic utilities
// desc: connects the word at the index, and at the index+1 together with an underscore
// and places it in the relative spot
// returns if the function is successful
    int joinWords(int index, char join){
        if(index + 1 >= list.size()) return 0;
        list[index] = list[index] + join + list[index+1]; //put the tied words together in list[index]
        list.erase(list.begin()+index+1,list.begin()+index+2); //remove list[index+1]
        return 1;
    }

//desc: does not break at index of character but after the index of the character
// h|e|l|l|o| if asked to split at 2 will give "hel" and "lo" so in other words
// returns if the function was successful
    int breakWordAtIndex(unsigned wordIndex, unsigned index){
        if(index == 0)return 0;
        string word = list.at(wordIndex);
        //the last index is useless as there's nothing
        if(index >= word.length())return 0;

        string first = word.substr(0,index);
        string second = word.substr(index);

        list.at(wordIndex) = second;
        list.insert(list.begin()+wordIndex,first);
        return 1;
    }

protected:
    vector<string> list;

    explicit ArrObj(vector<string>& list){
        this->list = list;
    }

};
