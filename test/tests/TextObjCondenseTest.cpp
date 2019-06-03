//
// Created by conor on 2019-06-02.
//

#include "gtest/gtest.h"
#include "TextObj.h"
#include "TextObjParamTest.h"

#define TEST_DIRECTORY "textTestFiles\\"

class TextObjCondenseTest : public::TextObjParamTest{

public:

    TextObjCondenseTest() : TextObjParamTest(TEST_DIRECTORY){}

    void condenseToPercent(double percent){
        int num = (int)(percent * text->size());
        if(num != 0)text->condense(num);
        EXPECT_UNIQUE();
        EXPECT_UNCHANGED();

        EXPECT_LE(text->size(),num);

    }
};

TEST_P(TextObjCondenseTest,condense80){
    condenseToPercent(.8);
}

TEST_P(TextObjCondenseTest,condense50){
    condenseToPercent(.8);
}
TEST_P(TextObjCondenseTest,condense30){
    condenseToPercent(.8);
}
TEST_P(TextObjCondenseTest,condense1){
    text->condense(1);
    EXPECT_UNCHANGED();
    EXPECT_EQ(1,text->size());
}

INSTANTIATE_TEST_SUITE_P(basic,TextObjCondenseTest,
                         ::testing::Range(1,8));
