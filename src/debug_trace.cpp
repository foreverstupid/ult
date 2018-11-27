#include "headers/debug_trace.hpp"

void SyntaxTreeTracer::enter(const char *name)
{
#   ifdef DEBUG
    TraceInfo *enterName = new TraceInfo;

    enterName->word = String(name);
    enterName->shift = shift;
    enterName->isWritten = false;
    names.push(enterName);

    shift += shiftInc;
#   endif
}



void SyntaxTreeTracer::exit(bool success)
{
#   ifdef DEBUG
    const TraceInfo *hlp;

    if(success){
        if(isShifted){
            putchar('\n');
            isShifted = false;
        }

        writeMissing();
        hlp = names.getFirst();
        writeTerm(hlp->word.getCharArray(), hlp->shift, false);
    }

    delete names.pop();
    shift -= shiftInc;
#   endif
}



void SyntaxTreeTracer::write(const char *str)
{
#   ifdef DEBUG
    writeMissing();

    if(!isShifted){
        printf("%*s", shift, "");
        isShifted = true;
    }

    printf("%s ", str);
#   endif
}



void SyntaxTreeTracer::writeTerm(const char *str, int shift,
    bool isOpening)
{
#   ifdef DEBUG
    printf("%*s", shift, "");

    putchar('<');
    if(!isOpening){
        putchar('/');
    }

    printf("%s>\n", str);
#   endif
}



void SyntaxTreeTracer::writeMissing()
{
#   ifdef DEBUG
    const ListItem<TraceInfo> *tmp;
    TraceInfo *hlp;

    tmp = names.getFirstItem();
    if(!tmp || tmp->obj->isWritten){
        return;
    }

    while(tmp->next && !tmp->next->obj->isWritten){
        tmp = tmp->next;
    }

    while(tmp){
        if(isShifted){
            putchar('\n');
            isShifted = false;
        }

        hlp = tmp->obj;
        writeTerm(hlp->word.getCharArray(), hlp->shift, true);
        hlp->isWritten = true;

        tmp = tmp->prev;
    }

#   endif
}
