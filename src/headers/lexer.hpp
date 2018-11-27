#ifndef LEXER_CLASS_HPP
#define LEXER_CLASS_HPP

#include "text_operations.hpp"
#include "text_getter.hpp"
#include "string.hpp"
#include "list.hpp"

/*
 * Struct that describes a lexeme
 */
struct Lexeme{
    /* lexeme types */
    enum{
        int_number, float_number, string, identifier, label, operation
    };

    String word;        /* lexeme word */
    int type;           /* lexeme type */

    int line;           /* line of the source code that holds a lexeme */
    int position;       /* position of the lexeme beginning in line */
};



/*
 * Class that implements automat for lexical analyzing
 */
class Lexer{
    static const char *operations;

    /* states of the lexing analysis */
    enum{
        none, integer, float_point_number, string, identifier, error,
        one_line_comment, multi_line_comment, escape_character, extra
    };

    int state;                      /* current state of the lexer */
    Lexeme *lexeme;                 /* current lexeme */

    int lineNumber;                 /* current line number */
    int position;                   /* current position */

    char extraLexeme;               /* extra lexeme that can be created
                                       if lexeme separator is an
                                       operation */
    int extraLexemePos;             /* position of extra lexeme */
    int extraLexemeLine;            /* line number of extra lexeme */

    bool hasLexemeCreated;          /* has lexer a new lexeme */

public:
    enum TakeCharacterStatus{
        /* return values of takeCharacter */
        empty, full, lexical_error,

        /* lexical errors */
        unexpected_char_error, no_closing_quote_error, identifier_error,
        number_error
    };

    Lexer();
    ~Lexer(){ delete lexeme; }

    /* takes next character */
    void takeCharacter(int ch);

    /* returns lexer status */
    int getLexerStatus() const;

    /* returns the next word of a program code.
       In case of error returns error lexeme */
    Lexeme *getLexeme();

private:
    Lexer(const Lexer &lexer);
    void operator=(const Lexer &lexer);

    /* choses automate state if given character is the first character
       of a lexeme */
    int getState(int ch);

    /* main logic switcher */
    void switcher(int ch);

    /* state handlers */
    void noneHandler(int ch);
    void intNumberHandler(int ch);
    void floatNumberHandler(int ch);
    void stringHandler(int ch);
    void identifierHandler(int ch);
    void oneLineCommentHandler(int ch);
    void multiLineCommentHandler(int ch);
    void escapeCharacterHandler(int ch);
    void extraHandler(int ch);

    /* checks if current character is a separator and initiate a new
       lexeme if it's true. Returns true - if ch is a separator,
       and false atherwise */
    bool checkSeparator(int ch);

    /* check if lexeme is created but haven't been taken */
    void checkExistingLexeme();

    /* does a character define a comment */
    bool isComment(char ch){ return ch == '#' || ch == '?'; }

    /* is character an operation */
    bool isOperation(char ch);
};



/*
 * Converts source code to the lexeme list.
 * Returns true in case of success, and false otherwise.
 * Error description holding in the last lexeme of the list.
 */
bool makeLexemeList(AbstractTextGetter &tg, List<Lexeme> &list);

#endif
