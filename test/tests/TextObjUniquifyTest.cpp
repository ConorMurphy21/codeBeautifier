//
// Created by conor on 2019-06-01.
//

#include "gtest/gtest.h"
#include "TextObj.h"

#define TEST_DIRECTORY "uniquifyTestFiles\\"

class TextObjUniquifyTest : public::testing::TestWithParam <int>{

protected:
    TextObj *text;
    string filename;
    vector<string> vec;

    TextObjUniquifyTest(){
        filename = TEST_DIRECTORY;
        filename += "test" + to_string(GetParam()) + ".txt";
        text = TextObj::create(filename);
        text->uniquify();
        vec = text->getVector();

        //we will test on small scale if new lines are
        for(auto & i : vec) {
            if(i[i.length()-1] == '\n') i.pop_back();
        }
    }
};

TEST_P(TextObjUniquifyTest,isUnchanged){
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

TEST_P(TextObjUniquifyTest,isUnique){
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

INSTANTIATE_TEST_SUITE_P(basic,TextObjUniquifyTest,
        ::testing::Range(1,8));

