//
// Created by conor on 2019-05-06.
//

#include <algorithm>
#include <fstream>
#include <iostream>
#include "Beautifier.h"



void Beautifier::create(Arguments* args){
    auto txtWords = fileToWordArray(args->getTxt(), true);
    auto codeWords = fileToWordArray(args->getCode(), false);
    removePunctuation(*txtWords);
    uniquify(*txtWords);
    string preProsIns = "hello";
    removePreProsIns(*codeWords, &preProsIns);

    //ok at this point we just need to make the arrays the same size
}


//this could be improved a lot, but I'm for now just going to
//save all of the imports and put them in the .h file along with the definitions
//or above the txt in the new c file

//note: all of the white space was removed from the c, so we need to re add it in
//post: there will be no more includes in the word array, because preprossessor instructions
//can not be overwritten; all pres will be thrown into a string which can be written to whichever
//file we choose to throw it in

//also note: assumes the code compiles. This boi does not double as a compiler lol
void Beautifier::removePreProsIns(vector<string>& list, string* pres){
    pres->clear();
    for(int i = 0; i < list.size(); i++){
        if(list.at(i) == "#include"){
            //add the include statement to the string
            pres->append("#include ");
            pres->append(list.at(i+1));
            pres->append("\n");

            //erase the #include lines from the array
            list.erase(list.begin()+i, list.begin()+i+2);
            i-=2;
        }
    }
}


//desc: connects the word at the index, and at the index+1 together with an underscore
//and places it in the relative spot
void Beautifier::connectWords(vector<string>& list, int index){
    list[index] = list[index] + "_" + list[index+1]; //put the tied words together in list[index]
    list.erase(list.begin()+index+1,list.begin()+index+2); //remove list[index+1]
}

//check if it's ok to tie index and index + 1 together;
bool isOkTie(vector<string>& list, int index){
    if(index < 0) {
        return false;
    }else if(index >= list.size()-1){
        return false;
    }else{
        int last = list[index].length()-1;
        return (list[index][last] != '\n');
    }
}

//desc: chooses whether to tie the index passed in to the word before or after it
//if both of them have \n characters then it returns -1
//this is because we want to avoid disrupting the given format of the text file
//so we do not want to have to remove a new line character but we cannot have an identifier
//with a new line character in it
int Beautifier::pickIndex(vector<string>& list, int index){
    if(isOkTie(list,index-1))return index-1;
    else if(isOkTie(list,index))return index;
    else return -1;
}

//desc: find first index of the key past in (this is not generic because we say
//that the two strings are equal even if there is a \n character at the end
// ie "foo" == "foo\n" is true
//pre: none
//post: none of the parameters are changed
int Beautifier::findInd(vector<string>& list, string key){
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

//TODO: this function desperately needs to be tested (for edge cases)
//less importantly to-do: we could make un unique words match up with repeating code
//like ; or ) but this would require a lot more finessing
//desc: creates a unique list of words while maintaining the meaning
//any already unique words will not be altered
//postcondition: words that appear twice will be tied together with other
//words before or after it with an underscore
void Beautifier::uniquify(vector<string>& list){
    int len = list.size();
    bool toggle = true; //we want to spread out the underscores so they aren't all in one place
    //for aesthetic reasons. so we are going to toggle where we put the underscore,
    //on the first one, or on the end one. Obviously not a perfect solution,
    //but it's an improvement from just all at the end or start
    for(int i = 0; i < len; i++){
        string word = list[i];

        int pos = findInd(list,word);
        if(pos != i){
            int index;
            //we need to do some tomfoolery to make them different but still aesthetic

            int one = pos, two = pos;
            if(toggle) two = i;
            else one = i;

            if((index = pickIndex(list,one))!= -1){
                connectWords(list,index);
                toggle = !toggle;
            }else if((index = pickIndex(list,two))!= -1){
                connectWords(list,index);
            }else{
                if(one != 0){
                    list[one-1].pop_back();
                    connectWords(list,one-1);
                    toggle = !toggle;
                }else if(one != list.size()-1){
                    list[one].pop_back();
                    connectWords(list,one);
                    toggle = !toggle;
                }else if(two != 0){
                    list[two-1].pop_back();
                    connectWords(list,two-1);
                }else{
                    list[two].pop_back();
                    connectWords(list,two);
                }
            }
            i--;
            len--;
        }
    }
}

//desc: for now removes the punctuation from the words (only letters are allowed as identifiers)
//technically numbers in the middle of words could be allowed (but that won't be beautiful lol)
//TODO: edge case of word of just punctuation needs to be fixed
//precondition: none
//postcondition: all none alpha or \n characters will be removed from words
void Beautifier::removePunctuation(vector<string>& wordList){
    for(string &word : wordList){
        for(char c : word) {
            if(!isalpha(c) && c != '\n'){
                word.erase(std::remove(word.begin(), word.end(), c), word.end());
            }
        }
    }
}

//desc: take the given file and seperate into a vector of words (seperated by spaces)
// if incldNL is true it will include \n in the words
// this is important because when remaking the file we may want to maintain the simple whitespace
vector<string>* Beautifier::fileToWordArray(char* filename, bool incldNL){
    //open file
    ifstream in(filename);
    if(!in){
        cout << filename << " could not be opened" << endl;
        return nullptr;
    }
    auto arr = new vector<string>();
    string line;
    while(std::getline(in,line)){
        int length = line.length();
        int start = 0, len = 0;
        string word;
        for(int i = 0; i < length; i++){
            char c = line.at(i);
            if(c == ' '){
                word = line.substr(start,len);
                start = i+1;
                len = -1;
                if(!word.empty())arr->push_back(word);
            }
            len++;
        }
        word = line.substr(start,len);
        if(incldNL)word.append("\n");
        if(!word.empty())arr->push_back(word);
    }
    return arr;
}
