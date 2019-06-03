//
// Created by conor on 2019-06-01.
//

#include "gtest/gtest.h"
#include "TextObj.h"
#include "TextObjParamTest.h"

#define TEST_DIRECTORY "textTestFiles\\"

class TextObjUniquifyTest : public::TextObjParamTest{

public:

    TextObjUniquifyTest() : TextObjParamTest(TEST_DIRECTORY){}
};

TEST_P(TextObjUniquifyTest,isUnchanged){
    EXPECT_UNCHANGED();
}

TEST_P(TextObjUniquifyTest,isUnique){
    EXPECT_UNIQUE();
}

INSTANTIATE_TEST_SUITE_P(basic,TextObjUniquifyTest,
        ::testing::Range(1,8));

