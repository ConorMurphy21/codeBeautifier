
#pragma once

#include <string>
#include <ostream>

using namespace std;
class Arguments {

    
private:

    //create and count are the two functions
    bool create = true;         //either bfy create or bfy count

    bool singleFile = false;


    //the code file to read in
    string code;
    //the txt file to read in
    string txt;
    //the code file to put it in
    string out;
    //the h file that either exists or doesn't exist
    string hout;


public:
    
    Arguments(){
            create = true;
            singleFile = false;
            txt = code = out = "";
            hout = "Definitions.h";
    }

    Arguments(bool create, bool singleFile, const string &code, const string &txt, const string &out,
              const string &hout) : create(create), singleFile(singleFile), code(code), txt(txt),
                                    out(out), hout(hout) {

    }


    bool operator==(const Arguments &rhs) const {
        return create == rhs.create &&
               singleFile == rhs.singleFile &&
               txt == rhs.txt &&
               code == rhs.code &&
               out == rhs.out &&
               hout == rhs.hout;
    }

    friend ostream &operator<<(ostream &os, const Arguments &arguments) {
        os << "create: " << arguments.create << " singleFile: " << arguments.singleFile <<" code: " << arguments.code
        << " txt: " << arguments.getTxt() << " out: " << arguments.out << " hout: " << arguments.hout;
        return os;
    }

    bool operator!=(const Arguments &rhs) const {
        return !(rhs == *this);
    }

    bool isCreate() const {
        return create;
    }

    void setCreate(bool create) {
        Arguments::create = create;
    }

    bool isSingleFile() const {
        return singleFile;
    }

    void setSingleFile(bool singleFile) {
        Arguments::singleFile = singleFile;
    }

    const string &getTxt() const {
        return txt;
    }

    void setTxt(const string &txt) {
        Arguments::txt = txt;
    }

    const string &getCode() const {
        return code;
    }

    void setCode(const string &code) {
        Arguments::code = code;
    }

    const string &getOut() const {
        return out;
    }

    void setOut(const string &out) {
        Arguments::out = out;
    }

    const string &getHout() const {
        return hout;
    }

    void setHout(const string &hout) {
        Arguments::hout = hout;
    }

};

