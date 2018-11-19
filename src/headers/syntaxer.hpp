#ifndef SYNTAXER_CLASS_HPP
#define SYNTAXER_CLASS_HPP

#include "list.hpp"

/*
 * Syntax analyzer
 */
class Syntaxer{
    ListItem *curr;         /* current observable lexeme */
    ListItem *prev;         /* previous observable lexeme (for valid error
                               description) */
public:
    /* error codes */
    enum{
        column_expected_error
    };

    Syntaxer() {}

    /* main anilyzing logic. Returns 0 if analyzing was successful
       and ListItem with invalid lexeme otherwise */
    const ListItem *analyze(List<Lexeme> &lexemes);

private:
    Syntaxer(const Syntaxer &sntxr);
    void operator=(const Syntaxer &sntxr);

    /* sets error code */
    void setErrorCode(int err){ prev->obj->type = err; }

    /* makes one step */
    void step();

    /* grammar states */
    bool program();
    bool statement();
    bool assigning();
    bool expression();
    bool variable();
    bool literal();
    bool codeBlock();
    bool argList();
    bool gotoStatement();
    bool ifStatement();
};

#endif
