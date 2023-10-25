#include "dynamic_string_array.hpp"
#include <iostream>
#include <cstring>

// Implementation of the DynamicStringArray class methods

// Default constructor: Initializes an empty array with initial capacity of 2
DynamicStringArray::DynamicStringArray() : size(0), capacity(2) {
    array = new char*[capacity];
    std::cout << "Constructor called" << std::endl;
}

// Copy constructor: Creates a deep copy of another DynamicStringArray
DynamicStringArray::DynamicStringArray(const DynamicStringArray& other) {
    size = other.size;
    capacity = other.capacity;
    array = new char*[capacity];
    for (int i = 0; i < size; i++) {
        array[i] = new char[strlen(other.array[i]) + 1];
        strcpy(array[i], other.array[i]);
    }
    std::cout << "Copy Constructor called" << std::endl;
}

// Move constructor: Takes ownership of the internal array of another DynamicStringArray
DynamicStringArray::DynamicStringArray(DynamicStringArray&& other)
    : size(other.size), capacity(other.capacity), array(other.array) {
    other.array = nullptr;
    other.size = 0;
    other.capacity = 0;
    std::cout << "Move Constructor called" << std::endl;
}

// Destructor: Frees up dynamically allocated memory for the array and its strings
DynamicStringArray::~DynamicStringArray() {
    for (int i = 0; i < size; i++) {
        delete[] array[i];
    }
    delete[] array;
    std::cout << "Destructor called" << std::endl;
}

// Adds a new string to the array. If the array is full, it resizes first.
void DynamicStringArray::add(const char* str) {
    if (size == capacity) {
        resize();
    }
    array[size] = new char[strlen(str) + 1];
    strcpy(array[size], str);
    size++;
}

// Prints all the strings stored in the array
void DynamicStringArray::print() const {
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

// Resizes the array by doubling its capacity
void DynamicStringArray::resize() {
    capacity *= 2;
    char** newArray = new char*[capacity];
    for (int i = 0; i < size; i++) {
        newArray[i] = array[i];
    }
    delete[] array;
    array = newArray;
}
