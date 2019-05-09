//
// Created by conor on 2019-05-06.
//


#include <string>
#include <vector>

using namespace std;

//if you're wondering, yes this is one of microsoft's approved identifiers for their naming convention
class EvenerOuter {


public:
    //well what as would an evenerOuter do?
    static bool evenEmOut(vector<string>& code, vector<string>& text);

private:


    //all of these return if it was successful or not
    static bool expandCode(vector < string > & code, int expectedSize);

    static bool condenseCode(vector<string>& code, int expectedSize);

    static bool condenseText(vector<string>& code, int expectedSize);

    //unfortunately I cannot expand the text so we will have to rely on the other three
    //to evener out
};

