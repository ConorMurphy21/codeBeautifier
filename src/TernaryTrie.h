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

    //constructor
    TernaryTrie(){
        //define an empty starting place
        root = state = nullptr;
    }

    //deconstructor
    ~TernaryTrie();

    //desc: puts the word into the trie
    //post: word is now in trie
    void putWord(const std::string& word);

    //desc: checks if the word is contained in the trie
    //returns if the word is contained
    bool containsWord(const std::string& word);


    bool isEmpty();

    // desc: checks if a word is there one character at a time.
    // post: returns:
    //-1 if it is not there
    // 1 if it could be but is not a full word
    // 2 if it is a full word
    int search(char c);

    //desc: resets the state object for searches.
    void resetState();
};


