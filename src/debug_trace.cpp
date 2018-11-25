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
    delete names.pop();
    shift -= shiftInc;

    if(success){
        if(isShifted){
            putchar('\n');
            isShifted = false;
        }

        writeMissing();
    }
#   endif
}



void SyntaxTreeTracer::writeMissing()
{
#   ifdef DEBUG
    const ListItem<TraceInfo> *tmp;
    TraceInfo *hlp;

    tmp = names.getFirstItem();
    while(tmp && tmp->next && !tmp->obj->isWritten){
        tmp = tmp->next;
    }

    while(tmp && !tmp->obj->isWritten){
        hlp = tmp->obj;
        writeTerm(hlp->word.getCharArray(), hlp->shift);
        hlp->isWritten = true;

        tmp = tmp->prev;
    }
#   endif
}
