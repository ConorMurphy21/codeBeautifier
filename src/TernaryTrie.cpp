//
// Created by conor on 2019-05-30.
//

#include "TernaryTrie.h"

TernaryTrie::~TernaryTrie() {
 deConstruct(root);
}

void TernaryTrie::deConstruct(TrieNode *node){
    if(!node)return;
    deConstruct(node->leftNode);
    delete node->leftNode;
    deConstruct(node->rightNode);
    delete node->rightNode;
    deConstruct(node->middleNode);
    delete node->middleNode;
}

void TernaryTrie::putWord(const std::string &word) {
    root = putWordRec(root,word,0);
}

TernaryTrie::TrieNode * TernaryTrie::putWordRec(TrieNode *node, const std::string& key, int d) {
    char c = key[d];
    if(!node) node = new TrieNode(c);

    if(c < node->c) node->leftNode = putWordRec(node->leftNode,key,d);
    else if(c > node->c) node->rightNode = putWordRec(node->rightNode,key,d);
    else if(d < key.length()-1) node->middleNode = putWordRec(node->middleNode,key,d+1);
    else node->isWord = true;

    return node;

}

bool TernaryTrie::containsWord(const std::string& key){
    return containsWordRec(root,key,0);
}
bool TernaryTrie::containsWordRec(TrieNode* node, const std::string &key, int d) {
    if(node == nullptr)return false;
    char c = key[d];
    if(c < node->c) return containsWordRec(node->leftNode, key, d);
    else if(c > node->c) return containsWordRec(node->rightNode, key, d);
    else if (d < key.length()-1) return containsWordRec(node->middleNode, key, d+1);
    else return node->isWord;
}

int TernaryTrie::search(char c) {
    return searchRec(state,c);
}

void TernaryTrie::resetState(){
    state = root;
}

/*
 * This function requires a little more knowledge on the users end
 * desc: looks for the next letter in the word, Once the user decides the word is over,
 * or they find the word they must resetState.
 * here are the return types:
 * returns -1 if there is no path with that letter at the current state
 */
int TernaryTrie::searchRec(TrieNode* node, char c){
    if(node == nullptr)return 0;
    if(c < node->c) return searchRec(node->leftNode,c);
    else if(c > node->c) return searchRec(node->rightNode,c);
    state = node->middleNode;
    return (node->isWord) ? 2 : 1;
}

bool TernaryTrie::isEmpty() {
    return root == nullptr;
}


