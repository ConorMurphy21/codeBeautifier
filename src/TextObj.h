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

    int findInd(string& key);

    int rankConnectionIndex(int index);


public:

    static TextObj* create(string& filename);

    //This should be protected or private but for testing it isn't worth only using files
    explicit TextObj(vector<string>& list):ArrObj(list){}

    bool condense(unsigned expectedSize);

    void uniquify();
};


