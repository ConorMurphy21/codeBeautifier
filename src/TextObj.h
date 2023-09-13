//
// Created by conor on 2019-05-11.
//

#pragma once

#include "ArrObj.h"
#include "TernaryTrie.h"

using namespace std;

class TextObj : public ArrObj {

private:

   //desc: finds the index of a string in a string in the string array
   //copying string because it needs to be altered without af
   int findInd(string key);

   //desc: ranks how good a connection is between the word at index and the word at index + 1
   int rankConnectionIndex(int index);

   //the english word for each of the digits
   const static string digits[10];

public:

   //desc: creates a text object from a text file
   //separates the file into a list of words, separated by spaces
   //also does small functions, such as underscore numbers, and remove punctuaction
   static TextObj *create(string &filename);

   //This should be protected or private but for testing it isn't worth only using files
   explicit TextObj(vector <string> &list) : ArrObj(list) {}

   //desc: combines words, to reduce the number of words to the expectedSize
   bool condense(unsigned expectedSize);

   //desc: makes sure every word is unique
   void uniquify();

   //desc: joins any words found in the blacklist trie with the word before or after it so that it is no longer
   //a keyword
   bool underscoreBlackList(TernaryTrie &trie);

};


