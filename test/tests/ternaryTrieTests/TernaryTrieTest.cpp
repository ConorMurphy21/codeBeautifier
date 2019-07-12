//
// Created by conor on 2019-05-30.
//

#include <TernaryTrie.h>
#include "gtest/gtest.h"

class TernaryTrieTest : public::testing::Test{
protected:
    TernaryTrie trie;

    const std::string arr[7] = {
            "Hello",
            "Healthy",
            "World",
            "Word",
            "Health",
            "Heart",
            "Whack"
    };

    const std::string arr2[7] = {
            "Help",
            "Hell",
            "Worm",
            "Words",
            "HealthY",
            "Hearts",
            "Wrap"
    };

    bool containsUsingSearch(const std::string& str){
        int len = str.length();
        trie.resetState();
        for(int i = 0; i < len-1; i++){
            const char &c = str[i];
            const int search = trie.search(c);
            if(!search)return false;
        }
        const int search1 = trie.search(str[len - 1]);

        return search1 == 2;
    }
};


TEST_F(TernaryTrieTest, SingleWord){
    trie.putWord("Hello");
    bool actual = trie.containsWord("Hello");
    EXPECT_EQ(true, actual);
}

TEST_F(TernaryTrieTest, SubWordIsNotFound){
    trie.putWord("Hello");
    bool actual = trie.containsWord("Hell");
    EXPECT_EQ(false, actual);
    actual = trie.containsWord("Hel");
    EXPECT_EQ(false, actual);
    actual = trie.containsWord("He");
    EXPECT_EQ(false, actual);
    actual = trie.containsWord("H");
    EXPECT_EQ(false, actual);
}

TEST_F(TernaryTrieTest, SubWordsAreFound){
    trie.putWord("Hello");
    trie.putWord("Hell");
    bool actual = trie.containsWord("Hell");
    EXPECT_EQ(true, actual);
    bool actual2 = trie.containsWord("Hello");
    EXPECT_EQ(true, actual2);
}

TEST_F(TernaryTrieTest, SubWordLeftBranch){
    trie.putWord("Hello");
    trie.putWord("Healthy");
    bool actual = trie.containsWord("Healthy");
    EXPECT_EQ(true, actual);
    bool actual2 = trie.containsWord("Hello");
    EXPECT_EQ(true, actual2);
}
TEST_F(TernaryTrieTest, complicatedTest){
    for(const auto & i : arr) trie.putWord(i);
    for(const auto & i : arr){
        bool actual = trie.containsWord(i);
        EXPECT_EQ(true,actual);
    }
    for(const auto & i : arr2){
        bool actual = trie.containsWord(i);
        EXPECT_EQ(false, actual);
    }
}

/*** TRY ALL OF THE ABOVE TESTS USING SEARCH ***/
TEST_F(TernaryTrieTest, SingleWordSearch){
    trie.putWord("Hello");
    bool actual = containsUsingSearch("Hello");
    EXPECT_EQ(true, actual);
}

TEST_F(TernaryTrieTest, SubWordIsNotFoundSearch){
    trie.putWord("Hello");
    bool actual = containsUsingSearch("Hell");
    EXPECT_EQ(false, actual);
    actual = containsUsingSearch("Hel");
    EXPECT_EQ(false, actual);
    actual = containsUsingSearch("He");
    EXPECT_EQ(false, actual);
    actual = containsUsingSearch("H");
    EXPECT_EQ(false, actual);
}

TEST_F(TernaryTrieTest, SubWordsAreFoundSearch){
    trie.putWord("Hello");
    trie.putWord("Hell");
    bool actual = containsUsingSearch("Hell");
    EXPECT_EQ(true, actual);
    bool actual2 = containsUsingSearch("Hello");
    EXPECT_EQ(true, actual2);
}

TEST_F(TernaryTrieTest, SubWordLeftBranchSearch){
    trie.putWord("Hello");
    trie.putWord("Healthy");
    bool actual = containsUsingSearch("Healthy");
    EXPECT_EQ(true, actual);
    bool actual2 = containsUsingSearch("Hello");
    EXPECT_EQ(true, actual2);
}
TEST_F(TernaryTrieTest, complicatedTestSearch){
    for(const auto & i : arr) trie.putWord(i);
    for(const auto & i : arr){
        bool actual = containsUsingSearch(i);
        EXPECT_EQ(true,actual);
    }
    for(const auto & i : arr2){
        bool actual = containsUsingSearch(i);
        EXPECT_EQ(false, actual);
    }
}
