#ifndef TEXT_GETTER_CLASS_HPP
#define TEXT_GETTER_CLASS_HPP

#include <stdio.h>

/*
 * Abstract class for getting text character by character
 */
class AbstractTextGetter{
public:
    /* returns next character */
    virtual int nextChar() = 0;

    /* is all text ends */
    virtual bool isEnded() = 0;

    AbstractTextGetter() {}
    virtual ~AbstractTextGetter() {}

private:
    AbstractTextGetter(const AbstractTextGetter &atg);
    void operator=(const AbstractTextGetter &atg);
};



/*
 * Text getter from a stream
 */
class StreamTextGetter : public AbstractTextGetter{
    FILE *in;

public:
    StreamTextGetter(FILE *in) : in(in) {}
    ~StreamTextGetter(){}

    int nextChar() { return fgetc(in); }
    bool isEnded() { return feof(in) != 0; }
};

#endif
