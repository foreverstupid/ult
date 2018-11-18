#ifndef STRING_CLASS_HPP
#define STRING_CLASS_HPP

#include "array.hpp"

/*
 * Class for string representation
 */
class String : public Array<char>{
public:
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
