//
// Created by conor on 2019-05-11.
//

#pragma once

#include "ArrObj.h"
#include <fstream>

class CodeObj : public ArrObj{

private:
    //all prePros functions will be stored in here
    string prePros;
public:

    static CodeObj* create(string& filename);

    explicit CodeObj(vector<string>* list, string& prePros):ArrObj(list){
        this->prePros = prePros;
    }

};


