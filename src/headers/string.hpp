#ifndef STRING_CLASS_HPP
#define STRING_CLASS_HPP

#include "array.hpp"

/*
 * Class for string representation
 */
class String : public Array<char>{
public:
    static int getLength(const char *str);

    String(const char *str);
    String() : Array<char>(64) {}

    bool operator==(const char *str) const;
    bool operator!=(const char *str) const { return !(*this == str); }
    bool operator==(char ch) const
    {
        return pos == 1 && storage[0] == ch;
    }
    bool operator!=(char ch) const { return !(*this == ch); }

    /* returns string as const char[] */
    const char *getCharArray() const
    {
        if(storage[pos]){
            storage[pos] = 0;
        }

        return storage;
    }

    /* resets string */
    void clean(){ pos = 0; }
};

#endif
