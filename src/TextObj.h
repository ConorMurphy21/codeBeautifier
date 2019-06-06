//
// Created by conor on 2019-05-11.
//

#pragma once

#include "ArrObj.h"
#include "TernaryTrie.h"

using namespace std;
class TextObj : public ArrObj {

private:

    int findInd(string& key);

    int rankConnectionIndex(int index);

    const static string digits[10];

public:

    static TextObj* create(string& filename);

    //This should be protected or private but for testing it isn't worth only using files
    explicit TextObj(vector<string>& list):ArrObj(list){}

    bool condense(unsigned expectedSize);

    void uniquify();

    void underscoreBlackList(TernaryTrie& trie);

    void createKeyWordList(TernaryTrie &keyWords, TernaryTrie &trie, vector<string> &list);
};


