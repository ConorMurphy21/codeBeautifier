//
// Created by conor on 2019-05-22.
//
#include "ArrObjBasicTest.h"


TEST_F(ArrObjBasicTest, joinWordsOutOfBounds){
    bool r = arr->joinWords(6,'_');
    EXPECT_ARRAY_EQ(testData,6, arr);
    EXPECT_EQ(false,r);
    r = arr->joinWords(7,'_');
    EXPECT_ARRAY_EQ(testData,6, arr);
    EXPECT_EQ(false,r);
}
TEST_F(ArrObjBasicTest, joinWordsProperly1){
    bool r = arr->joinWords(4,'_');
    EXPECT_ARRAY_EQ(testResult1,5, arr);
    EXPECT_EQ(r,true);
}
TEST_F(ArrObjBasicTest, joinWordsProperly2){
    bool r = arr->joinWords(0,' ');
    EXPECT_ARRAY_EQ(testResult2,5, arr);
    EXPECT_EQ(r,true);
}

TEST_F(ArrObjBasicTest, breakWordsAtIndexOutOfBounds){
    bool r = arr->breakWordAtIndex(6,1); //check out of bounds on the array
    EXPECT_ARRAY_EQ(testData,6, arr);
    EXPECT_EQ(r,false);
    r = arr->breakWordAtIndex(0,0); //check break at first char
    EXPECT_ARRAY_EQ(testData,6, arr);
    EXPECT_EQ(r,false);
    r = arr->breakWordAtIndex(0,5); //check break at last char
    EXPECT_ARRAY_EQ(testData,6,arr);
    EXPECT_EQ(r,false);
}
TEST_F(ArrObjBasicTest, breakWordsAtIndex1){

    //overwrite arr with testResult1
    auto vec = arr->getVector();
    vec.pop_back();
    for(int i = 0; i < 5; i++)vec[i] = testResult1[i];
    bool r = arr->breakWordAtIndex(2,4); //check out of bounds on the array
    EXPECT_ARRAY_EQ(testData,6, arr);
    EXPECT_EQ(r,false);
}

TEST_F(ArrObjBasicTest, breakWordsAtIndex2){
    //overwrite arr with testResult1
    auto vec = arr->getVector();
    vec.pop_back();
    for(int i = 0; i < 5; i++)vec[i] = testResult2[i];
    bool r = arr->breakWordAtIndex(0,5); //check out of bounds on the array
    EXPECT_ARRAY_EQ(testData,6,arr);
    EXPECT_EQ(r,false);
}



