#ifndef GUARD_Str_h
#define GUARD_Str_h

#include <algorithm> // copy
#include <cstring> // strlen
#include <iostream>
#include <iterator> // back_inserter

#include "Vec.h"

class Str{
public:
typedef size_t size_type;

    // CONSTRUCTORS
    Str() { }
    Str(size_t n, char c) : data(n, c) { }
    Str(const char* cp) {
        std::copy(cp, cp+ std::strlen(cp), std::back_inserter(data));
    }
    template <class In> Str(In b, In e) {
        std::copy(b, e, std::back_inserter(data));
    }

    // OPERATOR OVERLOADS
    char& operator[](size_t i) { return data[i]; }
    const char& operator[](size_t i) const { return data[i]; }
    friend std::istream& operator>>(std::istream&, Str&);
    Str& operator+=(const Str& rvalue) {
        std::copy(rvalue.data.begin(), rvalue.data.end(), std::back_inserter(data));
        return *this;
        /*for (size_t i = 0; i != rvalue.size(); ++i)
            data.push_back(rvalue(i));*/
    }

    // MEMBER FUNCTIONS
    size_t size() { return data.size(); }
    const size_t size() const { return data.size(); }
    char* begin() { return data.begin(); }
    const char* begin() const { return data.begin(); }
    char* end() { return data.end(); }
    const char* end() const { return data.end(); }

private:
    Vec<char> data;
};

// OUTPUT NONMEMBER FUNCTION
std::ostream& operator<<(std::ostream&, const Str&);

// CONCATENATE NONMEMBER FUNCTION
Str& operator+ (const Str&, const Str& );

#endif // GUARD_Str_h
