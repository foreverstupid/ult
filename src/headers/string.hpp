#ifndef STRING_CLASS_HPP
#define STRING_CLASS_HPP

#include "array.h"

/*
 * Class for string representation
 */
class String : public Array<char>{
public:
    const char *getCharArray() const { return storage; }
    void clean(){ pos = 0; }
};

#endif
