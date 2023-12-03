#include "dynamic_string_array.hpp"
#include <algorithm>
#include <cctype>

namespace stringarray {

class UpperCaseStringArray : public DynamicStringArray {
public:
    // Constructorul implicit
    UpperCaseStringArray() = default;

    // Folosind constructorul din clasa de bază
    using DynamicStringArray::DynamicStringArray;

    // Supraîncărcarea metodei 'add' pentru a adăuga stringuri în majuscule
    void add(const char* str) override;
};

} // namespace stringarray

