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
#define BLACKLIST_FLAG 'b'

#define NUM_SOURCE_EXTENSIONS 12
#define NUM_HEADER_EXTENSIONS 6
#define NUM_TEXT_EXTENSIONS 2


using namespace std;
class ArgumentFactory {

private:

    const static string SOURCE_EXTENSIONS[];
    const static string HEADER_EXTENSIONS[];
    const static string TEXT_EXTENSIONS[];

    static bool checkExtension(const string& filename, const string extensions[], unsigned len);
    static bool checkSourceExtension(string& filename);
    static bool checkHeaderExtension(string& filename);
    static bool checkTextExtension(string& filename);

public:
    static Arguments* getArguments(int argc, const char* argv[]);

};


