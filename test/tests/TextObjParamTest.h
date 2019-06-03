//
// Created by conor on 2019-06-02.
//

#ifndef CODEBEAUTIFIER_TEXTOBJPARAMTEST_H
#define CODEBEAUTIFIER_TEXTOBJPARAMTEST_H


#include <gtest/gtest.h>
#include <TextObj.h>

class TextObjParamTest: public::testing::TestWithParam <int>{

protected:
    TextObj *text;
    string filename;
    vector<string> vec;

    explicit TextObjParamTest(const string& test_dir){
        filename = test_dir;
        filename += "test" + to_string(GetParam()) + ".txt";
        text = TextObj::create(filename);
        text->uniquify();
        vec = text->getVector();

        //we will test on small scale if new lines are
        for(auto & i : vec) {
            while(!i.empty() && i[i.length()-1] == '\n'){
                i.pop_back();
            }
        }
    }

    void EXPECT_UNCHANGED(){
        //vec = text->getVector();
        ifstream in(filename);
        string actual, expected;
        int i = 0,j = 0;
        while(in >> expected){
            actual = vec[i].substr(j);
            //its right skip to next word

            if(actual == expected){
                j = 0;
                i++;
                continue;
            }

            int tempJ = j;
            if((j = actual.find('_')) != string::npos){
                actual = actual.substr(0,j);
                j += tempJ;
                j++;
            }

            //at this point we know they aren't equal, just want to see it printed
            EXPECT_EQ(actual,expected);
        }
    }
    void EXPECT_UNIQUE(){
        //vec = text->getVector();//make sure boi is up to date
        int len = vec.size();
        for(int i = 0; i < len; i++){
            auto actual = find(vec.begin(),vec.end(),vec[i]);
            auto expected = vec.begin() + i;
            //if these aren't equal it means something is not unique

            EXPECT_EQ(actual,expected);
            if(actual != expected){
                cout << vec[i] << endl;
            }
        }
    }
};

#endif //CODEBEAUTIFIER_TEXTOBJPARAMTEST_H
