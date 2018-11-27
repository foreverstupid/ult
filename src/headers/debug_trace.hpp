#ifndef DEBUG_TRACE
#define DEBUG_TRACE

#include <stdio.h>
#include "list.hpp"
#include "string.hpp"

/*
 * Info about name and shifting
 */
#ifdef DEBUG
struct TraceInfo{
    String word;
    int shift;
    bool isWritten;
};
#endif



/*
 * Class for debug tracing syntaxer
 */
class SyntaxTreeTracer{
#   ifdef DEBUG
    enum { shiftInc = 4 };  /* a value of shift incrementing */
    int shift;              /* output shifting */
    List<TraceInfo> names;  /* stack of grammar func names */
    bool isShifted;         /* is a line shifted */
#   endif

public:
    SyntaxTreeTracer(){ shift = 0; isShifted = false; }

    void enter(const char *name);   /* called when entering term */
    void exit(bool success);        /* called when exiting term */

    void write(const char *str);

private:
    /* writes one term with given shift. If isOpening == true, writes
       open tag, otherwise - close tag */
    void writeTerm(const char *str, int shift, bool isOpening);

    /* writes all missing terms */
    void writeMissing();
};

#endif
