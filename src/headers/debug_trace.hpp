#ifndef DEBUG_TRACE
#define DEBUG_TRACE

#ifdef DEBUG

#include <stdio.h>
#include "list.hpp"
#include "string.hpp"

/*
 * Info about name and shifting
 */
struct TraceInfo{
    String word;
    int shift;
    bool isWritten;
};



/*
 * Class for debug tracing syntaxer
 */
class SyntaxTreeTracer{
    enum { shiftInc = 4 };  /* a value of shift incrementing */
    int shift;              /* output shifting */
    List<TraceInfo> names;  /* stack of grammar func names */

public:
    SyntaxTreeTracer(){ shift = 0; }

    void enter(const char *name);   /* called when entering grammar func */
    void exit(bool success);        /* called when exeting grammar func */

    void write(const char *str){ printf("%s ", str); }

private:
    /* writes one term with given shift */
    void writeTerm(const char *str, int shift)
    {
        printf("%*s%s\n", shift, "", str);
    }

    /* writes all missing terms */
    void writeMissing();
};

#endif

#endif
