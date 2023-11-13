#include "lower_case_string_array.hpp"
#include <cstring>

namespace stringarray {

void LowerCaseStringArray::add(const char* str) {
    // Creăm o copie a șirului primit ca parametru
    char* lowerStr = new char[strlen(str) + 1];
    strcpy(lowerStr, str);

    // Convertim fiecare caracter în minusculă
    std::transform(lowerStr, lowerStr + strlen(lowerStr), lowerStr, ::tolower);

    // Apelăm metoda 'add' din clasa de bază
    DynamicStringArray::add(lowerStr);

    // Eliberăm memoria alocată pentru șirul temporar
    delete[] lowerStr;
}

} // namespace stringarray
