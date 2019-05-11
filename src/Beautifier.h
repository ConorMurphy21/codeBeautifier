//
// Created by conor on 2019-05-06.
//


#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include "Arguments.h"

using namespace std;
class Beautifier {
public:

    Beautifier() = default;

    void create(Arguments* args);


private:


    static int breakWordAtIndex(vector<string> &list, unsigned int wordIndex, unsigned int index);

    static void uniquify(vector<string>& wordList);

    static int findInd(vector<string>& list, string key);

    static int pickIndex(vector<string>& list, int index);

    static int joinWords(vector<string> &list, int index, char join);
};



