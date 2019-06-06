//
// Created by conor on 2019-06-06.
//

#include "gtest/gtest.h"
#include "CodeObj.h"

using namespace std;
class CodeObjExpandTest : public ::testing::Test{
protected:
    const string test1 = "std::cout!=var!(var==var2)=var+var+=var&&hello";

    const string test1_r[19] = {
            "std",
            "::",
            "cout",
            "!=",
            "var",
            "!",
            "(",
            "var",
            "==",
            "var2",
            ")",
            "=",
            "var",
            "+",
            "var",
            "+=",
            "var",
            "&&",
            "hello"
    };

    CodeObj* obj;
    vector<string> vec;

    explicit CodeObjExpandTest(){
        vec.push_back(test1);
        obj = new CodeObj(vec,"");
        vec = obj->getVector();
    }

};

TEST_F(CodeObjExpandTest,operatorExpandTest){
    obj->expand(19);
    vec = obj->getVector();
    ASSERT_EQ(obj->size(),19);
    for(int i = 0; i < 19; i++){
        string actual = vec[i];
        string expected = test1_r[i];
        EXPECT_EQ(actual,expected);
    }
}