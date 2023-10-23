# include <cstring>
# include "myclass.hpp"
# include <iostream>

# define MAX_LEN 5

int main() {
    char * s = new char[MAX_LEN];
    memcpy(s, "Sal", MAX_LEN);
    Class1 c1(1, 2.0, s);
    {
        Class1 y = c1;
    }
    Class1 c2 = std::move(Class1(2, 2.0, s));
    return 0;
}