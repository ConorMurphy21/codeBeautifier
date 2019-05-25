//
// Created by conor on 2019-05-24.
//

#include <ArrObj.h>
#include <TextObj.h>
#include "gtest/gtest.h"
#include "ArrObjBasicTest.h"


using namespace std;
class TextObjBasicTest:public ArrObjBasicTest{
    protected:

    TextObj* text;

    TextObjBasicTest():ArrObjBasicTest(){
        text = new TextObj(vec);
    }
    ~TextObjBasicTest(){
        delete text;
    }
};

TEST_F(TextObjBasicTest, uniquifyBasicTest){
    text->uniquify();
    EXPECT_ARRAY_EQ(testData,6,text);
}

TEST_F(TextObjBasicTest, condenseBasicTest){
    text->condense(5);
    EXPECT_ARRAY_EQ(testResult1,5,text);
}



