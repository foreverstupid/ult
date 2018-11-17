#ifndef LEXER_CLASS_HPP
#define LEXER_CLASS_HPP

#include "text_operations.hpp"
#include "text_getter.hpp"
#include "string.hpp"

/*
 * Class that implements automat for lexical analyzing
 */
class Lexer{
    /* states of the lexing analysis */
    enum{
        none, integer, float_point_number, string, identifier, error
    };

    AbstractTextGetter *textGetter; /* getter for program text */
    int state;                      /* current state of the lexer */
    String buf;                     /* buffer for current word */

public:
    Lexer(AbstractTextGetter *tg) : textGetter(tg)
    {
        state = none;
    }

    /* takes next character. Returns true if lexeme has been created,
       and false otherwise */
    bool takeCharacter(int ch);

    /* returns the next word of a program code */
    String nextWord();
};

#endif
