#ifndef LEXER_CLASS_HPP
#define LEXER_CLASS_HPP

#include "text_operations.hpp"
#include "text_getter.hpp"
#include "string.hpp"

/*
 * Struct that describes a lexeme
 */
struct Lexeme{
    /* lexeme types */
    enum{
        int_number, float_number, string, identifier
    };

    String string;      /* lexeme word */
    int type;           /* lexeme type */

    int line;           /* line of the source code that holds a lexeme */
    int position;       /* position of the lexeme beginning in line */
};



/*
 * Class that implements automat for lexical analyzing
 */
class Lexer{
    /* states of the lexing analysis */
    enum{
        none, integer, float_point_number, string, identifier, error,
        comment
    };

    AbstractTextGetter *textGetter; /* getter for program text */
    int state;                      /* current state of the lexer */
    Lexeme *lexeme;                 /* current lexeme */

    int errorStatus;                /* error status of the automat */

public:
    /* error stati */
    enum{
        no_error, wrong_identifier, no_closing_quote
    };

    Lexer(AbstractTextGetter *tg) : textGetter(tg)
    {
        state = none;
        lexeme = new Lexeme();
    }
    ~Lexer(){ delete lexeme; }

    /* takes next character. Returns error status of the automat */
    int takeCharacter(int ch);

    /* returns the next word of a program code.
       In case of error returns error lexeme */
    Lexeme *getLexeme();

private:
    Lexer(const Lexer &lexer);
    void operator=(const Lexer &lexer);

    /* main logic switcher */
    void switcher(int ch);

    /* state handlers */
    void noneHandler(int ch);
    void intNumberHandler(int ch);
    void floatNumberHandler(int ch);
    void stringHandler(int ch);
    void identifierHandler(int ch);
    void commentHandler(int ch);
    int errorHandler(int ch);
};

#endif
