//
// Created by conor on 2019-05-24.
//

#ifndef CODEBEAUTIFIER_ARROBJBASICTEST_H
#define CODEBEAUTIFIER_ARROBJBASICTEST_H


#include <gtest/gtest.h>
#include "ArrObj.h"

using namespace std;
class ArrObjBasicTest : public testing::Test{
    protected:
    ArrObj* arr;
    vector<string> vec;

    string testData[6] = {
            "Hello",
            "World",
            "This",
            "Is",
            "A",
            "Test"
    };

    string testResult1[5] = {
            "Hello",
            "World",
            "This",
            "Is",
            "A_Test"
    };

    string testResult2[5] = {
            "Hello World",
            "This",
            "Is",
            "A",
            "Test"
    };

    ArrObjBasicTest(){
        for(const auto & i : testData)vec.push_back(i);
        arr = new ArrObj(vec);
    }
    ~ArrObjBasicTest() override{
        delete arr;
    }

    void EXPECT_ARRAY_EQ(const string* array,const int length, const ArrObj* arrObj) const{
        ASSERT_EQ(arrObj->size(), length);
        vector<string> v = arrObj->getVector();
        for(int i = 0; i < length; i++){
            string a = v[i];
            string b = array[i];
            EXPECT_EQ(a,b);
        }
    }
};
#endif //CODEBEAUTIFIER_ARROBJBASICTEST_H
