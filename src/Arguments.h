
#pragma once

class Arguments{

private:

    //are the parameters passed in valid
    bool valid = true;

    //create and count are the two functions
    bool create = true;         //either bfy create or bfy count

    //should the program overwrite the files given
    bool overWrite = false;    // flag: -o                                                                                                          ;

    //keep the definitions in the .cpp file and not a .h
    bool singleFile = false; // flag: -s

    //the txt file to read in
    char* txt;
    //the code file to read in
    char* code;
    //the code file to put it in
    char* out;
    //the h file that either exists or doesn't exist
    char* hout;

public:

    Arguments() = default;

    void setValid(bool valid) {
        this->valid = valid;
    }

    void setTxt(char *txt) {
        this->txt = txt;
    }

    void setCode(char *code) {
        this->code = code;
    }

    void setOut(char *out) {
        this->out = out;
    }

    bool isValid() const {
        return valid;
    }

    char* getTxt() const {
        return txt;
    }

    char *getCode() const {
        return code;
    }

    char *getOut() const {
        return out;
    }

};