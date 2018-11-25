#ifdef DEBUG
#include "headers/debug_trace.hpp"

void SyntaxTreeTracer::enter(const char *name)
{
    TraceInfo *enterName = new TraceInfo;

    enterName->word = String(name);
    enterName->shift = shift;
    enterName->isWritten = false;
    names.push(enterName);

    shift += shiftInc;
}



void SyntaxTreeTracer::exit(bool success)
{
    delete names.pop();
    shift -= shiftInc;

    if(success){
        writeMissing();
    }
}



void SyntaxTreeTracer::writeMissing()
{
    const ListItem<TraceInfo> *tmp;
    TraceInfo *hlp;

    tmp = names.getLastItem();
    while(tmp->prev && !tmp->obj->isWritten){
        tmp = tmp->prev;
    }

    while(tmp){
        hlp = tmp->obj;
        writeTerm(hlp->word.getCharArray(), shift);
        hlp->isWritten = true;

        tmp = tmp->next;
    }
}
#endif
