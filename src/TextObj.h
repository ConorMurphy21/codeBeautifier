//
// Created by conor on 2019-05-11.
//

#pragma once

#include <vector>
#include <fstream>
#include <string>
#include "ArrObj.h"

using namespace std;
class TextObj : public ArrObj {

private:
    bool isOkTie(int index);

    int pickIndex(int index);

    int findInd(string& key);

    int rankConnectionIndex(int index);


public:

    bool condense(unsigned expectedSize);

    static TextObj* create(string& filename);

    explicit TextObj(vector<string>& list):ArrObj(list){}

    void uniquify();
};


