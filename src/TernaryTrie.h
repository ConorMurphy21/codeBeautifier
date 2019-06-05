//
// Created by conor on 2019-05-30.
//


#pragma once

#include <string>

class TernaryTrie {

private:
    struct TrieNode{
        TrieNode *leftNode, *rightNode, *middleNode;
        bool isWord;
        char c;
        explicit TrieNode(char c) : c(c){
            leftNode = rightNode = middleNode = nullptr;
            isWord = false;
        }

    };
    TrieNode *root, *state;


    TrieNode * putWordRec(TrieNode *node, const std::string& key, int d);

    void deConstruct(TrieNode *node);

    bool containsWordRec(TrieNode *node, const std::string &key, int d);

    int searchRec(TrieNode *node, char c);

public:

    TernaryTrie(){
        //define an empty starting place
        root = state = nullptr;
    }

    ~TernaryTrie();


    void putWord(const std::string& word);

    bool containsWord(const std::string& word);


    //-1 if it is not there
    // 1 if it could be but is not a full word
    // 2 if it is a full word
    int search(char c);


    void resetState();
};


