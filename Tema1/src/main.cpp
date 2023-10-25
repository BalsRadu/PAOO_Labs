#include "dynamic_string_array.hpp"
#include <iostream>

int main() {
    // Create a new instance of DynamicStringArray
    DynamicStringArray arr;

    // Add two strings to the array
    arr.add("Hello");
    arr.add("World");

    // Use the copy constructor to create a deep copy of 'arr' named 'arr2'
    DynamicStringArray arr2 = arr;

    // Use the move constructor to move the content of 'arr2' to 'arr3'
    // After this operation, 'arr2' will be in an empty and valid state
    DynamicStringArray arr3 = std::move(arr2);

    // Print the contents of 'arr3'
    arr3.print();

    return 0;  // End the program
}
