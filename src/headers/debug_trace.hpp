#ifndef DEBUG_TRACE_HPP
#define DEBUG_TRACE_HPP

#ifdef DEBUG

#include <stdio.h>

using namespace trace{
    void writeLine(const char *str)
    {
        printf("%s\n", str);
    }

    void write(const char *str)
    {
        printf("%s", str);
    }
}

#endif

#endif
