//
// Created by conor on 2019-05-04.
//

#pragma once

#include "Arguments.h"
#include <string>

#define COUNT_FLAG "-count"
#define HEADER_DESTINATION_FLAG 'h'
#define SOURCE_DESTINATION_FLAG 's'
#define DESTINATION_FLAG 'd'
#define SINGLE_FILE_FLAG 'f'
#define OVERWRITE_FLAG 'o'

#define NUM_SOURCE_EXTENSIONS 12
#define NUM_HEADER_EXTENSIONS 6
#define NUM_TEXT_EXTENSIONS 2


using namespace std;
class ArgumentFactory {

private:

    const static string SOURCE_EXTENSIONS[];
    const static string HEADER_EXTENSIONS[];
    const static string TEXT_EXTENSIONS[];

    //desc: returns whether the filename has an extension that is contained in extensions
    static bool checkExtension(const string& filename, const string extensions[], unsigned len);

    //desc: returns whether the filename has a C/C++ source file extension
    //source not to be confused with implementation files, headers are also included as source files
    static bool checkSourceExtension(string& filename);

    //desc: returns whether the filename has a C/C++ header extension
    static bool checkHeaderExtension(string& filename);

    //desc: returns whether the filename has a text file extension
    static bool checkTextExtension(string& filename);

public:

    //returns an arguments object from the file arguments
    static Arguments* getArguments(int argc, const char* argv[]);

};


