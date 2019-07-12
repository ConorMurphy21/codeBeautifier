//
// Created by conor on 2019-06-03.
//

#include "gtest/gtest.h"
#include "CodeObj.h"

#define TEST_DIRECTORY "codeTestFiles\\"

class CodeObjExpandCondenseTest: public::testing::TestWithParam<int>{

protected:
    CodeObj *code, *reference;
    string filename;
    vector<string> codeVec, refVec;

    explicit CodeObjExpandCondenseTest(){
        filename = TEST_DIRECTORY;
        filename += "test" + to_string(GetParam()) + ".cpp";
        code = CodeObj::create(filename);
        reference = CodeObj::create(filename);
        codeVec = code->getVector();
        refVec = code->getVector();
    }

    ~CodeObjExpandCondenseTest() override{
        delete code;
        delete reference;
    }

    char getNextChar(const vector<string>& vec, unsigned *i, unsigned *j) const{
        unsigned iVal = *i, jVal = *j, size = vec.size();
        if(iVal >= size) return 0;
        string word = vec[iVal];
        if(jVal >= word.length()){
            *i = iVal+1;
            *j = 0;
            return getNextChar(vec,i,j);
        }
        char c = word[jVal];
        *j = jVal + 1;

        if(isspace(c)) return getNextChar(vec,i,j);
        return c;
    }

    void EXPECT_UNCHANGED() const{
        unsigned i,j,k,l;
        i = j = k = l = 0;
        for(;;){
            char actual = getNextChar(refVec,&k,&l);
            char expected = getNextChar(codeVec,&i,&j);
            EXPECT_EQ(actual,expected);
            if(actual == 0 || expected == 0)break;
        }
    }

    void expandToPercent(double percent){
        int num = (int)(percent * code->size());
        bool success = false;
        if(num != 0) success = code->expand(num);
        EXPECT_UNCHANGED();
        if(success) EXPECT_EQ(code->size(),num);

    }
    void condenseToPercent(double percent){
        int num = (int)(percent * code->size());
        if(num != 0)code->condense(num);
        EXPECT_UNCHANGED();
        EXPECT_EQ(code->size(),num);
    }

};

TEST_P(CodeObjExpandCondenseTest, condenseTo80){
    condenseToPercent(0.8);
}
TEST_P(CodeObjExpandCondenseTest, condenseTo50){
    condenseToPercent(0.5);
}
TEST_P(CodeObjExpandCondenseTest, condenseTo20){
    condenseToPercent(0.2);
}
TEST_P(CodeObjExpandCondenseTest, condenseTo1){
    code->condense(1);
    EXPECT_UNCHANGED();
    EXPECT_EQ(1,code->size());
}
TEST_P(CodeObjExpandCondenseTest, expandTo110){
    expandToPercent(1.1);
}
TEST_P(CodeObjExpandCondenseTest, expandTo130){
    expandToPercent(1.3);
}
TEST_P(CodeObjExpandCondenseTest, expandTo150){
    expandToPercent(1.5);
}
TEST_P(CodeObjExpandCondenseTest, expandTo200){
    expandToPercent(2.0);
}




TEST_P(CodeObjExpandCondenseTest,testIftestWorks){
    EXPECT_UNCHANGED();
}

INSTANTIATE_TEST_SUITE_P(basic,CodeObjExpandCondenseTest,::testing::Range(1,4));