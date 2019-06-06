//
// Created by conor on 2019-06-05.
//

#ifndef CODEBEAUTIFIER_KEYWORDTRIES_H
#define CODEBEAUTIFIER_KEYWORDTRIES_H

#include <string>
#include "TernaryTrie.h"
#include <vector>

class KeyWordTries {
private:
    static const std::string keyWords[103];

    static const std::string operators[11];

public:

    static void fillWithAllKeyWords(TernaryTrie& trie);
    static void fillWithOperators(TernaryTrie& trie);

};


#endif //CODEBEAUTIFIER_KEYWORDTRIES_H
