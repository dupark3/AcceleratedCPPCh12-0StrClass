#ifndef GUARD_Str_h
#define GUARD_Str_h

#include <iostream>

#include "Vec.h"

class Str{
public:
typedef size_t size_type;

// CONSTRUCTORS
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

// OPERATOR OVERLOAD
    char& operator[](size_t i) { return data[i]; }
    const char& operator[](size_t i) const { return data[i]; }

// MEMBER FUNCTIONS
    size_t size() { return data.size() }

private:
    Vec<char> data;
};

// INPUT AND OUTPUT NONMEMBER FUNCTIONS 
std::ostream& operator<<(std::ostream& os, const Str& s){
    for(Str::size_type i = 0; i < s.size(); ++i)
        os << s[i];
    return os;
}

std::istream& operator>>(std::istream& is, const Str& s){
    // obliterate existing values
    s.data.clear();

    // read nad discard leading whitespace
    char c;
    while (is.get(c) && isspace(c))
        ; // nothing to do, just test the condition

    // if something still to read, do so until next whitespace character
    if (is){
        do s.data.push_back(c);
        while(is.get(c) && !isspace(c));

        // if we read whitspace, then put it back on the stream
        if (is)
            is.unget();
    }

    return is;
}

#endif // GUARD_Str_h
