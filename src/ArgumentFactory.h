//
// Created by conor on 2019-05-04.
//

#pragma once

#include "Arguments.h"

class ArgumentFactory {

public:
    static Arguments* getArguments(int argc, char** argv);
};


