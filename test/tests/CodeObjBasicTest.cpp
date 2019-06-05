//
// Created by conor on 2019-05-22.
//

#include <gtest/gtest.h>
#include "CodeObj.h"
#include "TernaryTrie.h"

class CodeObjBasicTest : public::testing::Test{
protected:
    CodeObj* code;

    string arr[15] = {
           "if",
           "explicit",
           "}else",
           "}class{",
           "int ",
           " short ",
           "&const{long",
           " enum struct",
           "forIdentifier",
           "while_",
           "_unsigned",
           "_switch_",
           "t_throw",
           "words that shouldn't be in here and }volatile{ also",
           "also atomic_cancel"
    };

    CodeObjBasicTest(){
        vector<string> vec;
        for(const auto &i : arr)vec.push_back(i);
        code = new CodeObj(vec,"");
    };

    ~CodeObjBasicTest() override{
        delete code;
    }

    void EXPECT_FOUND(const string& key){
        TernaryTrie keyWords;
        code->fillTrie(keyWords);
        bool actual = keyWords.containsWord(key);
        EXPECT_EQ(true,actual);
    }

    void EXPECT_NFOUND(const string& key){
        TernaryTrie keyWords;
        code->fillTrie(keyWords);
        bool actual = keyWords.containsWord(key);
        EXPECT_EQ(false,actual);
    }

};

TEST_F(CodeObjBasicTest,basicKeyWordsFound){
    EXPECT_FOUND("if");
    EXPECT_FOUND("explicit");
}
TEST_F(CodeObjBasicTest,ImperfectKeyWordsFound){
    EXPECT_FOUND("else");
    EXPECT_FOUND("class");
    EXPECT_FOUND("int");
    EXPECT_FOUND("short");
}
TEST_F(CodeObjBasicTest,DoubleKeyWordsFound){
    EXPECT_FOUND("const");
    EXPECT_FOUND("long");
    EXPECT_FOUND("enum");
    EXPECT_FOUND("struct");
}
TEST_F(CodeObjBasicTest, KeyWordsFound){
    EXPECT_NFOUND("for");
    EXPECT_NFOUND("unsigned");
    EXPECT_NFOUND("switch");
    EXPECT_NFOUND("throw");
}
TEST_F(CodeObjBasicTest, DoubleKeyEdgeCase){
    EXPECT_FOUND("volatile");
}
TEST_F(CodeObjBasicTest, underscoredKeyWord){
    EXPECT_FOUND("atomic_cancel");
}
