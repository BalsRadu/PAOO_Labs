# include "myclass.hpp"
# include <cstring>
# include <iostream>

// Constructor
Class1::Class1(int a, int b, char* c) : a(a), b(b) {
    this->c = c;
    std::cout << "Constructor called" << std::endl;
};

// Copy Constructor
Class1::Class1(const Class1& other) {
    this->a = other.a;
    this->b = other.b;
    int n = strlen(other.c) + 1;
    this->c = new char[n];
    memcpy(this->c, other.c, n);
    std::cout << "Copy Constructor called" << std::endl;
};

// Move Constructor
Class1::Class1(Class1&& other) {
    this->a = other.a;
    this->b = other.b;
    this->c = other.c;
    other.c = NULL;
    std::cout << "Move Constructor called" << std::endl;
};

// Destructor
Class1::~Class1() {
    if(c)
        delete[] c;
    std::cout << "Destructor called" << std::endl;
};