//
// Created by conor on 2019-05-06.
//


#pragma once

#include <string>
#include <vector>
#include "Arguments.h"

using namespace std;
class Beautifier {
public:

    Beautifier() = default;

    void create(Arguments* args);


private:

    static vector<string>* fileToWordArray(char* filename, bool incldNL);

    static void removePunctuation(vector<string>& wordList);

    static void uniquify(vector<string>& wordList);

    static void removePreProsIns(vector<string>& list, string* str);

    static int findInd(vector<string>& list, string key);

    static int pickIndex(vector<string>& list, int index);

    static void connectWords(vector<string>& list, int index);
};


