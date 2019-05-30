//
// Created by conor on 2019-05-25.
//

#include <CodeObj.h>
#include "gtest/gtest.h"
#include "TextObj.h"
using namespace std;

#define TEST_DIRECTORY "createTestFiles\\"

struct CodeObjCreateTest: public testing::TestWithParam<string>{};

struct TextObjCreateTest: public testing::TestWithParam<string>{};

TEST_P(TextObjCreateTest, dataDrivenTextCreate){
    string filename = TEST_DIRECTORY + GetParam();
    string intrum = filename + ".txt";
    auto txt = TextObj::create(intrum);
    ASSERT_NE(txt, nullptr);
    auto vec = txt->getVector();
    ifstream in(filename+"_r.txt");
    string actual,expected;
    unsigned size = vec.size();
    int i;
    for(i = 0; in >> expected && i < size; i++){
        actual = vec[i];
        if(expected[expected.length()-1] == '!')expected[expected.length()-1] = '\n';
        EXPECT_EQ(actual,expected);
    }
    EXPECT_EQ(size,i);

}

TEST_P(CodeObjCreateTest, dataDrivenCodeCreate){
    string filename = TEST_DIRECTORY + GetParam();
    string intrum = filename + ".cpp";
    auto code = CodeObj::create(intrum);
    ASSERT_NE(code, nullptr);
    auto vec = code->getVector();
    intrum = filename + "_r.cpp";
    ifstream in(intrum);
    string actual, expected;
    unsigned size = vec.size();
    int i;
    for(i = 0; in >> expected && i < size; i++){
        //the quotes should be exactly one word
        if(expected == "\"\"")continue;
        actual = vec[i];
        EXPECT_EQ(actual,expected);
    }
    EXPECT_EQ(size,i);
}

INSTANTIATE_TEST_SUITE_P(ddct, CodeObjCreateTest,::testing::Values("code1","code2","code3"));

INSTANTIATE_TEST_SUITE_P(ddtt, TextObjCreateTest,::testing::Values("text1","text2"));

