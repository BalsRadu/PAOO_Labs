#include "upper_case_string_array.hpp"
#include "lower_case_string_array.hpp"
#include <iostream>

using namespace stringarray;

int main() {
    UpperCaseStringArray upperArr;
    upperArr.add("Hello");
    upperArr.add("world");

    LowerCaseStringArray lowerArr;
    lowerArr.add("HELLO");
    lowerArr.add("WORLD");

    std::cout << "UpperCase Array: ";
    upperArr.print();

    std::cout << "LowerCase Array: ";
    lowerArr.print();

    return 0;
}
