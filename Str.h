#ifndef GUARD_Str_h
#define GUARD_Str_h

#include "Vec.h"


class Str{
public:
    // default constructor
    Str() { }

    // create a Str containing n copies of c
    Str(size_t n, char c) : data(n, c) { }

    // create a Str from a null-terminated array of char
    Str(const char* cp) { 
        std::copy(cp, cp+ std::strlen(cp), std::back_inserter(data)); 
    } 

    // create a Str from a range denoted by iterators b and e
    template <class In> Str(In b, In e) { 
        std::copy(b, e, std::back_inserter(data)); 
    }

    char& operator[](size_t i) { return data[i]; }
    const char& operator[](size_t i) const { return data[i]; }

private:
    Vec<char> data;
};

#endif // GUARD_Str_h
