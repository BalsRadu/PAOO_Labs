#include "upper_case_string_array.hpp"
#include <cstring>

namespace stringarray {

void UpperCaseStringArray::add(const char* str) {
    // Creăm o copie a șirului primit ca parametru
    char* upperStr = new char[strlen(str) + 1];
    strcpy(upperStr, str);

    // Convertim fiecare caracter în majusculă
    std::transform(upperStr, upperStr + strlen(upperStr), upperStr, ::toupper);

    // Apelăm metoda 'add' din clasa de bază
    DynamicStringArray::add(upperStr);

    // Eliberăm memoria alocată pentru șirul temporar
    delete[] upperStr;
}

} // namespace stringarray

