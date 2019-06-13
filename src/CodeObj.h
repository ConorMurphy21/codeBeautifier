//
// Created by conor on 2019-05-11.
//

#pragma once

#include "ArrObj.h"
#include "TernaryTrie.h"

class CodeObj : public ArrObj{

private:


    //all prePros functions will be stored in here
    string prePros;

    //todo: something to remember when writing this function, a quoted section needs to stay together
    //ok so I painstakingly went through every ascii characters to see if they were immediately seperable: 1
    //extrawork seperable: 2, quotes: 3, everything else 0
    //1's : ( ) ; ? [ ] { } ~ (as far as I know these never need to be grouped)
    //2's : ! % & * + - / : = ^ | (these sometimes need to be grouped)
    //3's : " ' (just skip words that start with these) they already as reduced as possible
    //4's : < > these unfortunately have  <<= and >>= which sucks
    const char specialChars[256] = {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //15
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //31
            0, 2, 3, 0, 0, 2, 2, 3, 1, 1, 2, 2, 0, 2, 0, 2, //47
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 4, 2, 4, 1, //63
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //79
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 2, 0, //95
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, //111
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 1, 0  //127

    };


public:

    //creates a code object from a file
    //this separates all the words into an array, removes comments, and keeps preprocessor functions in prePros
    static CodeObj* create(string& filename);

    //basic constructor
    explicit CodeObj(vector<string>& list, const string& prePros):ArrObj(list), prePros(prePros){}

    //simple getter
    const string &getPrePros() const;

    //desc: separates words until there are the same number of words as expected size
    //returns if successfully expanded to expected size
    //post: list->size == expectedSize
    bool expand(int expectedSize);

    //desc: reduces the file size by combining words until the size of the file has reached the expected size
    //returns if successfully condensed to expected size
    //pre expectedSize is not 0
    //post: list->size == expectedSize
    bool condense(unsigned int expectedSize);

    //desc: fills the given trie with all of the alphanum words found in it
    //ie all variable names, (and keywords but keeping them out makes no difference)
    //post: trie is filled with all words to avoid
    void fillTrie(TernaryTrie &trie);


    //this is no longer being used, but may be used in the future
    void replaceWithRedefs(TernaryTrie &redefTrie, const string& redefPrefix);

};


