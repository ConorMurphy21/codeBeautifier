//
// Created by thooks on 2019-05-15.
//

#include "gtest/gtest.h"
#include "CodeObj.h"



TEST(basic_test, test){
    string fileName = "helloWorld.cpp";
    auto obj = CodeObj::create(fileName);

}
