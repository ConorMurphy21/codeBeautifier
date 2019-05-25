//
// Created by conor on 2019-05-11.
//

#include <iostream>
#include "TextObj.h"

TextObj* TextObj::create(string& filename){
    //open file
    ifstream in(filename);
    if(!in){
        cout << filename << " could not be opened" << endl;
        return nullptr;
    }
    vector<string> arr;
    string line;

    while(std::getline(in,line)){
        int length = line.length();
        string word;
        for(int i = 0; i < length; i++){
            char c = line[i];
            //basically checks if the character can be a valid identifier
            //commands are in likely order, so although this statement looks long, chances are
            //it will never have to check if it is a number and is not the start of the word
            if((isalpha(c) || c == '_') || (i != 0 && line[i] != ' ' && isdigit(c))){
                //if is proper identifier char add to word
                word += c;
            }else if(c == ' '){
                //if is space, push word and start over
                if(!word.empty())arr.push_back(word);
                word.clear();
            }
        }

        //wierd but not uncommon edge case where sentence ends with space needs to be covered
        if(word.empty()){
            arr[arr.size()-1] += '\n';
        }else {
            word += '\n';
            if (!word.empty())arr.push_back(word);
        }
    }

    return new TextObj(arr);
}

//desc: find first index of the key past in (this is not generic because we say
//that the two strings are equal even if there is a \n character at the end
// ie "foo" == "foo\n" is true
//pre: none
//post: none of the parameters are changed
int TextObj::findInd(string& key){
    int size = list.size();
    if(key[key.size()-1] == '\n')key.pop_back();
    for(int i = 0; i < size; i++){
        string word = list[i];
        if(word == key)return i;
        if(word[word.length()-1] == '\n'){
            if(key == word.substr(0,word.length()-1))return i;
        }
    }
    return -1;
}

//ranks how well tying together the strings at index and index+1 will fair

//not possible at all = -1
//Connecting \n and already exists = 0
//connecting \n only = 1
//already exists = 2
//nothing wrong = 3
int TextObj::rankConnectionIndex(int index){

    string main = list[index];

    if(index < 0 || index >= list.size()-1) return -1;

    if(main[main.length()-1] == '\n'){
        main.pop_back();
        if(findInd(main.append("_").append(list[index+1])) != -1)return 0;
        return 1;
    }else if(findInd(main.append("_").append(list[index+1])) != -1){
        return 2;
    }
    return 3;

}

void TextObj::uniquify() {

    int len = list.size();
    bool toggle = true; //we want to spread out the underscores so they aren't all in one place
    //for aesthetic reasons. so we are going to toggle where we put the underscore,
    //on the first one, or on the end one. Obviously not a perfect solution,
    //but it's an improvement from just all at the end or start
    for(unsigned i = 0; i < len; i++){
        string word = list[i];

        unsigned pos = findInd(word);

        if(pos != i){

            /* so at this point we have 4 possible solutions to solve the problem in an ideal scenario
             * let's look at our ideal scenario "This is ideal Hello World Hello Earth"
             * we can solve the problem by joining any of the following: ideal_Hello, Hello_World, World_Hello,
             * or Hello_Earth. ie we can combine both pos and i with the word before or after each of them.
             * But these circumstances are not always ideal:
             * "Hello_World\nHello World\nHello Earth\n"
             * Then our choices are "Hello_World_Hello" which ruins the new line
             * "Hello_World\n" which already exists meaning we would need to join together one of the words again
             * "World_Hello" which again ruins the new line
             * "Hello Earth" which is the ideal choice.
             * So what we need to do is choose the ideal choice, but still deal with the unideal scenarios
            */

            unsigned indexArr[] = {pos,pos-1,i-1,i};
            unsigned rankArr[4];
            for(unsigned j = 0; j < 4; j++)
                rankArr[j] = rankConnectionIndex(indexArr[j]);

            unsigned max = 0;
            if(toggle){
                for(unsigned j = 1; j < 4; j++)
                    if(rankArr[j] > rankArr[max])max = j;
            }else{
                for(unsigned j = 1; j < 4; j++)
                    if(rankArr[j] >= rankArr[max])max = j;
            }

            switch(rankArr[max]){
                case 2:
                    i--;
                case 3:
                    joinWords(max,'_');
                    break;
                case 0:
                    i--;
                case 1:
                    list[max].pop_back();
                    joinWords(max,'_');
                    break;
            }

            len--;
            toggle = !toggle;
        }
    }
}


//this algorithm should work for literally 99% of cases, but it may create ununique identifiers
//to counter this I call uniquify at the end, but this may make the algorithm overshoot and condense too much
//so for now Ill just make if it fails call code.expand(), since this is a last resort method anyways,
//and its called after the code is condensed, this should work
//so returns false basically only if it overshoots
bool TextObj::condense(unsigned expectedSize) {

    if(expectedSize == 0)return false;

    while(list.size() > expectedSize){

        int size = list.size();
        unsigned index = 0;
        int rank = rankConnectionIndex(index);

        for(int i = 1; i < size; i++) {
            int r = rankConnectionIndex(i);
            if(r > rank){
                rank = r;
                index = i;
            }else if(r == rank){
                if(list[i].length() < list[index].length()){
                    rank = r;
                    index = i;
                }
            }
        }

        joinWords(index,'_');

    }
    uniquify();
    return size() == expectedSize;
}

