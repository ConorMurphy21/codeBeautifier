#include <iostream>

int main() {

    std::cout << "What is love, and what is life?" << std::endl;
    std::string in;
    std::cin >> in;

    if(in != "shrek")std::cout << "No! ";
    std::cout << "shrek is love, shrek is life!" << std::endl;

}
