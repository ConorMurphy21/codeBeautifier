//
// Created by conor on 2019-06-05.
//

#pragma once
#include <string>
#include "TernaryTrie.h"

class KeyWordTries {
private:
    static const std::string keyWords[103];

public:

    static void fillWithAllKeyWords(TernaryTrie& trie);

};

