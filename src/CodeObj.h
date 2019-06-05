//
// Created by conor on 2019-05-11.
//

#pragma once

#include "ArrObj.h"
#include "TernaryTrie.h"

class CodeObj : public ArrObj{

private:

    //in perfect order for the trie
    const string keyWords[103] = {
            "int",
            "constexpr",
            "bitor",
            "atomic_commit",
            "and_eq",
            "alignof",
            "alignas",
            "and",
            "atomic_cancel",
            "asm",
            "auto",
            "audit",
            "atomic_noexcept",
            "bitand",
            "axiom",
            "char32_t",
            "catch",
            "break",
            "bool",
            "case",
            "char16_t",
            "char8_t",
            "concept",
            "compl",
            "class",
            "consteval",
            "const",
            "enum",
            "default",
            "co_return",
            "continue",
            "const_cast",
            "co_await",
            "decltype",
            "co_yield",
            "double",
            "do",
            "delete",
            "else",
            "dynamic_cast",
            "for",
            "false",
            "export",
            "explicit",
            "extern",
            "float",
            "final",
            "if",
            "goto",
            "friend",
            "inline",
            "import",
            "static_assert",
            "override",
            "not",
            "namespace",
            "module",
            "long",
            "mutable",
            "noexcept",
            "new",
            "operator",
            "nullptr",
            "not_eq",
            "or_eq",
            "or",
            "requires",
            "reflexpr",
            "protected",
            "private",
            "public",
            "reinterpret_cast",
            "register",
            "signed",
            "short",
            "return",
            "static",
            "sizeof",
            "typedef",
            "thread_local",
            "synchronized",
            "struct",
            "static_cast",
            "switch",
            "this",
            "template",
            "transaction_safe",
            "true",
            "throw",
            "try",
            "transaction_safe_dynamic",
            "void",
            "unsigned",
            "typename",
            "typeid",
            "union",
            "virtual",
            "using",
            "while",
            "wchar_t",
            "volatile",
            "xor_eq",
            "xor"
    };


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

    TernaryTrie trie;



public:

    static CodeObj* create(string& filename);

    explicit CodeObj(vector<string>& list, const string& prePros):ArrObj(list){
        this->prePros = prePros;
        //initialize trie
        for(const auto & keyWord : keyWords)trie.putWord(keyWord);

    }

    bool expand(unsigned int expectedSize);

    bool condense(unsigned expectedSize);

    //should update the og trie to only include the keywords in the file
    void fillTrie(TernaryTrie &newTrie);

    void replaceWithRedefs(TernaryTrie &redef, const string& redefPrefix);

};


