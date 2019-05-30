//
// Created by conor on 2019-05-29.
//
#include "gtest/gtest.h"
#include "Arguments.h"
#include "ArgumentFactory.h"
#include <vector>

struct ArgumentFactoryTestObject{
    int argc;
    char const** argv;
    Arguments* args;

    ArgumentFactoryTestObject() = default;

    ArgumentFactoryTestObject(int argc, char const** argv ,bool create, bool singleFile, const string &code,
                              const string &txt, const string &out, const string &hout):argc(argc),argv(argv) {
        args = new Arguments(create,singleFile,code,txt,out,hout);
    }
    ArgumentFactoryTestObject(int argc, char const** argv):argc(argc),argv(argv),args(nullptr) {}
};

class ArgumentFactoryTest : public::testing::TestWithParam<ArgumentFactoryTestObject>{
};



TEST_P(ArgumentFactoryTest,test){
    auto args = ArgumentFactory::getArguments(GetParam().argc,GetParam().argv);
    if(!GetParam().args){
        EXPECT_EQ(args,GetParam().args);
    }else{
        ASSERT_NE(args, nullptr);
        Arguments actual = *args;
        Arguments expected = *(GetParam().args);
        EXPECT_EQ(actual,expected);
    }
}

//not enough arguments
char const* argv1[] = {"./1","-count"};
ArgumentFactoryTestObject test1(2, argv1);

//too many arguments for -count
char const* argv2[] = {"./2","-count","filename.cpp","filename.txt","-c"};
ArgumentFactoryTestObject test2(5, argv2);

//no text file
char const* argv3[] = {"./3","-count", "filename.cpp"};
ArgumentFactoryTestObject test3(3, argv3);

//filename.zip is not a txt file
char const* argv4[] = {"./4","-count","filename.cpp","filename.zip"};
ArgumentFactoryTestObject test4(4, argv4);

//normal count arguments
char const* argv5[] = {"./5","-count","filename.h","filename"};
ArgumentFactoryTestObject test5(4, argv5, false, false, "filename.h", "filename", "", "Definitions.h");

INSTANTIATE_TEST_SUITE_P(ArgumentFactoryCountTest, ArgumentFactoryTest,
                         ::testing::Values(test1,test2,test3,test4,test5));


//-r is not a known flag
char const* argv6[] = {"./6","-r","filename.h++","filename.TXT"};
ArgumentFactoryTestObject test6(4, argv6);

//filename.txt should not be recognized as a source file
char const* argv7[] = {"./7","-o","filename.txt","filename.cpp"};
ArgumentFactoryTestObject test7(4, argv7);

//text file does not exist
char const* argv8[] = {"./8","-o","filename.cpp"};
ArgumentFactoryTestObject test8(3, argv8);

//-s requires a file after it, meaning there will not be enough files
char const* argv9[] = {"./9","-s","filename.cpp","filename.txt"};
ArgumentFactoryTestObject test9(4, argv9);

//-h requires a header extension not a cpp file
char const* argv10[] = {"./10","-h","filename.cpp","filename1.cpp","filename.txt"};
ArgumentFactoryTestObject test10(4, argv10);

//destination cannot have a file extension
char const* argv11[] = {"./11","-d","filename.cpp","filename1.cpp","filename.txt"};
ArgumentFactoryTestObject test11(4, argv11);

//overwrite flag and set source file
char const* argv18[] = {"./18","-o","-s","filename.cpp","filename1.cpp","filename.txt"};
ArgumentFactoryTestObject test18(6, argv18);

INSTANTIATE_TEST_SUITE_P(BadArgumentTests, ArgumentFactoryTest,
                         ::testing::Values(test6,test7,test8,test9,test10,test11,test18));

//default arguments
char const* argv12[] = {"./12","filename.cpp","filename.txt"};
ArgumentFactoryTestObject test12(3, argv12, true, false, "filename.cpp",
                                 "filename.txt", "beautiful_filename.cpp", "Definitions.h");

char const* argv13[] = {"./13","-f","filename.cpp","filename.txt"};
ArgumentFactoryTestObject test13(4, argv13, true, true, "filename.cpp",
                                 "filename.txt", "beautiful_filename.cpp", "Definitions.h");

//check overwrite, and two options
char const* argv14[] = {"./14","-o","-f","filename.cpp","filename.txt"};
ArgumentFactoryTestObject test14(5, argv14, true, true, "filename.cpp",
                                 "filename.txt", "filename.cpp", "Definitions.h");

//set source file
char const* argv15[] = {"./15","-s","new_filename.cpp","filename.cpp","filename.txt"};
ArgumentFactoryTestObject test15(5, argv15, true, false, "filename.cpp",
                                 "filename.txt", "new_filename.cpp", "Definitions.h");

//set header file
char const* argv16[] = {"./16","-h","new_filename.hpp","filename.cpp","filename"};
ArgumentFactoryTestObject test16(5, argv16, true, false, "filename.cpp",
                                 "filename", "beautiful_filename.cpp", "new_filename.hpp");

//basic destination
char const* argv17[] = {"./17","-d","new_filename","filename.cpp","filename.txt"};
ArgumentFactoryTestObject test17(5, argv17, true, false, "filename.cpp",
                                 "filename.txt", "new_filename.cpp", "new_filename.h");

//new_filename should have correct extension
char const* argv19[] = {"./19","-d","new_filename","filename.c","filename.txt"};
ArgumentFactoryTestObject test19(5, argv19, true, false, "filename.c",
                                 "filename.txt", "new_filename.c", "new_filename.h");

INSTANTIATE_TEST_SUITE_P(GoodArgumentTests, ArgumentFactoryTest,
                         ::testing::Values(test12,test13,test14,test15,test16,test17,test19));

//should work
//char const* argv8[] = {"./","filename.cc","filename.txt"};
//ArgumentFactoryTestObject test8(4, argv8, false, false, "filename.h", "filename", "", "Definitions.h");



