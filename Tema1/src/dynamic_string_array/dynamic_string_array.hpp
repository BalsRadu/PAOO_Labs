#pragma once  // Prevents multiple inclusions of this header file

// The DynamicStringArray class represents a dynamic array of strings
// which can grow in size as new strings are added.
class DynamicStringArray {
private:
    char** array;  // Pointer to an array of char pointers (each representing a string)
    int size;      // Current number of strings in the array
    int capacity;  // Maximum number of strings the array can hold before resizing

    // Private method to resize the array
    // Doubles the capacity when called
    void resize();

public:
    // Default constructor: Initializes an empty array with initial capacity of 2
    DynamicStringArray();

    // Copy constructor: Creates a deep copy of another DynamicStringArray
    DynamicStringArray(const DynamicStringArray&);

    // Move constructor: Takes ownership of the internal array of another DynamicStringArray
    DynamicStringArray(DynamicStringArray&&);

    // Destructor: Frees up dynamically allocated memory for the array and its strings
    ~DynamicStringArray();

    // Copy assignment operator
    DynamicStringArray& operator=(const DynamicStringArray&);

    // Move assignment operator
    DynamicStringArray& operator=(DynamicStringArray&&);

    // Adds a new string to the array
    // If the array is full, it resizes first
    virtual void add(const char* str);

    // Prints all the strings stored in the array
    virtual void print() const;
};
