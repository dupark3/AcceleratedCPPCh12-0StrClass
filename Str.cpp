
#include <iostream>
#include "Str.h"

// OUTPUT NONMEMBER FUNCTION
std::ostream& operator<<(std::ostream& os, const Str& s){
    for(Str::size_type i = 0; i != s.size(); ++i)
        os << s[i];
    return os;
}


// INPUT FRIEND FUNCTION (gains access to private member data for writing)
std::istream& operator>>(std::istream& is, Str& s){
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


// CONCATENATE NONMEMBER FUNCTION
Str& operator+ (const Str& first, const Str& second){
    Str ret = first;
    ret += second;
    return ret;
}
