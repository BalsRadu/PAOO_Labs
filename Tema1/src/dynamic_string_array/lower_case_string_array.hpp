#include "dynamic_string_array.hpp"
#include <algorithm>
#include <cctype>

namespace stringarray {

class LowerCaseStringArray : public DynamicStringArray {
public:
    // Constructorul implicit
    LowerCaseStringArray() = default;

    // Folosind constructorul din clasa de bază
    using DynamicStringArray::DynamicStringArray;

    // Supraîncărcarea metodei 'add' pentru a adăuga stringuri în minuscule
    void add(const char* str) override;
};

} // namespace stringarray
