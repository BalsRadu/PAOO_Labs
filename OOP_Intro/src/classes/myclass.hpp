#pragma once

class Class1 {
    private:
        int a;
        float b;
        char* c;
    public:
        Class1(int, int, char*);
        Class1(const Class1&);
        Class1(Class1&&);
        ~Class1();
};