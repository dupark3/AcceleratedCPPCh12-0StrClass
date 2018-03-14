#ifndef GUARD_Str_h
#define GUARD_Str_h

#include "Vec.h"


class Str{
public:
    // default constructor
    Str() { }

    // create a Str containing n copies of c
    Str(size_type n, char c) : data(n, c) { }

    // create a Str from a null-terminated array of char
    Str(const char* cp) { 
        std::copy(cp, cp+ std::strlen(cp), std::back_inserter(data)); 
    } 

    // create a Str from a range denoted by iterators b and e
    template <class In> Str(In b, In e) { 
        std::copy(b, e, std::back_inserter(data)); 
    }

private:
    Vec<char> data;
};

#endif // GUARD_Str_h
