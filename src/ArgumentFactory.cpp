//
// Created by conor on 2019-05-04.
//

#include "ArgumentFactory.h"
#include <iostream>
#include <cstring>
#include <algorithm>

const string ArgumentFactory::SOURCE_EXTENSIONS[NUM_SOURCE_EXTENSIONS] =
        {"c","cc","C","cpp","cxx","c++","h","hh","H","hpp","hxx","h++"};
//these are just header extensions
const string ArgumentFactory::HEADER_EXTENSIONS[NUM_HEADER_EXTENSIONS] = {"h","hh","H","hpp","hxx","h++"};
//these are just txt extensions
const string ArgumentFactory::TEXT_EXTENSIONS[NUM_TEXT_EXTENSIONS] = {"txt","TXT"};

bool ArgumentFactory::checkExtension(const string& filename, const string extensions[], unsigned len){
    unsigned index = filename.find('.');
    if(index == string::npos)return true;
    string extension = filename.substr(index+1);
    for(int i = 0; i < len; i++){
        if(extension == extensions[i])return true;
    }
    return false;
}

bool ArgumentFactory::checkSourceExtension(string& filename){
    return checkExtension(filename,SOURCE_EXTENSIONS,NUM_SOURCE_EXTENSIONS);
}

bool ArgumentFactory::checkHeaderExtension(string& filename){
    return checkExtension(filename,HEADER_EXTENSIONS,NUM_HEADER_EXTENSIONS);
}
bool ArgumentFactory::checkTextExtension(string& filename){
    return checkExtension(filename,TEXT_EXTENSIONS,NUM_TEXT_EXTENSIONS);
}

Arguments* ArgumentFactory::getArguments(int argc, const char *argv[]) {

    // command [options] [codeFile] [textFile]

    auto args = new Arguments();

    //not enough arguments check
    if(argc < 3){
        cout << "Not enough arguments were provided." << endl;
        return nullptr;
    }

    //special -count case
    if(strcmp(argv[1], COUNT_FLAG) == 0){

        args->setCreate(false);
        //with the -count flag, there is only one valid syntax
        // ./bfy -count code.x text.txt
        if(argc != 4){
            cout << "There are an invalid number of arguments with the count flag." << endl;
            return nullptr;
        }
        string code = argv[2];
        if(checkSourceExtension(code)){
            args->setCode(code);
        }else{
            cout << code << " is not recognized as a C/C++ source file." << endl;
            cout << "Make sure you C/C++ code file first and text file second." << endl;
            return nullptr;
        }

        string text = argv[3];
        if(checkTextExtension(text)){
            args->setTxt(text);
        } else {
            cout << text << " is not recognized as a text file." << endl;
            return nullptr;
        }
        return args;
    }

    /*** OPTIONS LOOP ***/
    int i;
        //overwrite flag   //destination set, but does not have the valid extension
    bool overwrite = false, addExtension = false;
    char last = 0;
    for(i = 1; i < argc; i++){
        string str = argv[i];

        if(last){
            switch(last){
                case HEADER_DESTINATION_FLAG:
                    if(checkHeaderExtension(str)){
                        if(str.find('.') == string::npos) str += ".h";
                        args->setHout(str);
                    }else{
                        cout << str << " is not recognized as a header file." << endl;
                        return nullptr;
                    }
                    break;
                case SOURCE_DESTINATION_FLAG:
                    if(checkSourceExtension(str)){
                        if(str.find('.') == string::npos)addExtension = true;
                        args->setOut(str);
                    }else{
                        cout << str << " is not recognized as a source file." << endl;
                        return nullptr;
                    }
                    break;
                case DESTINATION_FLAG:
                    if(str.find('.') == string::npos){
                        addExtension = true;
                        args->setOut(str);
                         str += ".h";
                        args->setHout(str);
                    }else{
                        cout << "Destination must not have a file extension." << endl;
                        return nullptr;
                    }
                case BLACKLIST_FLAG:
                    transform(str.begin(), str.end(), str.begin(), ::tolower);
                    if(str == "all"){
                        args->setBlacklist(Arguments::ALL);
                    }else if(str == "none"){
                        args->setBlacklist(Arguments::NONE);
                    }else if(str != "ops"){
                        args->setBlacklist(Arguments::OPERATORS);
                    }else{
                        cout << str << " is not a recognized blacklist option." << endl;
                        return nullptr;
                    }

                    break;
            }
            last = 0;
        }else{
            if (str.length() != 2)break;
            if (str[0] != '-')break;
            char c = str[1];
            switch (c) {

                case SINGLE_FILE_FLAG:
                    args->setSingleFile(true);
                    break;

                case OVERWRITE_FLAG:
                    overwrite = true;
                    break;

                case HEADER_DESTINATION_FLAG:
                case SOURCE_DESTINATION_FLAG:
                case DESTINATION_FLAG:
                case BLACKLIST_FLAG:
                    last = c;
                    break;

                default:
                    cout << str << " is not recognized." << endl;
                    return nullptr;
            }
        }
    }

    ///make sure there are only 2 remaining arguments for code file and text file
    if(argc < i+2){
        cout << "Both your codeFile and textFile must be specified." << endl;
        return nullptr;
    }else if(argc > i+2){

        cout << "All options must go before the filenames." << endl;
        return nullptr;
    }

    ///check and set the code file
    string code = argv[i];
    if(checkSourceExtension(code)){
        args->setCode(code);
    }else{
        cout << code << " is not recognized as a C/C++ source file." << endl;
        cout << "Make sure your C/C++ code file first and text file second." << endl;
        return nullptr;
    }

    ///check and set the text file
    string text = argv[i+1];
    if(checkTextExtension(text)){
        args->setTxt(text);
    } else {
        cout << text << " is not recognized as a text file." << endl;
        return nullptr;
    }

    ///if Overwrite flag is set, set the output accordingly
    if(overwrite){
        if(!args->getOut().empty() && args->getOut() != args->getCode()){
            cout << "Conflicting arguments. Overwrite flag was set, "
                    "but output file is defined as " << args->getOut() << "." << endl;
            return nullptr;
        }
        args->setOut(args->getCode());
    }

    //add the same extension as the extension given on the input to the output
    if(addExtension){
        int index = code.find('.');
        if(index == string::npos){
            args->setOut(args->getOut()+".cpp");
        }else{
            string extension = code.substr(index);
            args->setOut(args->getOut()+extension);
        }
    }

    //if the output is not set yet, set it to the default value
    if(args->getOut().empty()){
        args->setOut("beautiful_"+args->getCode());
    }


    return args;

}
