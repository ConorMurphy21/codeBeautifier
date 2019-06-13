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
            "switch1",
            "t_throw",
            "words that shouldnt be in here and }volatile{ also",
            "also atomic_cancel"
    };

    string arr2[15] = {
            "REDEF_if",
            "REDEF_explicit",
            "}REDEF_else",
            "}REDEF_class{",
            "REDEF_int ",
            " REDEF_short ",
            "&REDEF_const{REDEF_long",
            " REDEF_enum REDEF_struct",
            "forIdentifier",
            "while_",
            "_unsigned",
            "switch1",
            "t_throw",
            "words that shouldn't be in here REDEF_and }REDEF_volatile{ also",
            "also REDEF_atomic_cancel"
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
TEST_F(CodeObjBasicTest, KeyWordsNotFound){
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

//this test is no longer needed as this is not used
/*TEST_F(CodeObjBasicTest, redefinitionTest){
    TernaryTrie keyWords;
    code->fillTrie(keyWords);
    code->replaceWithRedefs(keyWords,"REDEF_");
    auto vec = code->getVector();
    unsigned actualSize = vec.size();
    ASSERT_EQ(actualSize,15);
    for(int i = 0; i < actualSize; i++){
        string actual = vec[i];
        string expected = arr2[i];
        EXPECT_EQ(actual,expected);
    }
}*/
