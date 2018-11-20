#ifndef SYNTAXER_CLASS_HPP
#define SYNTAXER_CLASS_HPP

#ifdef DEBUG
#include <stdio.h>
#endif

#include "list.hpp"
#include "lexer.hpp"

/*
 * Syntax analyzer
 */
class Syntaxer{
#   ifdef DEBUG
    int shift;
    int shiftInc;
#   endif

    static const char *unarOperations;
    static const char *binarOperations;

    const ListItem<Lexeme> *curr; /* current observable lexeme */
    const ListItem<Lexeme> *prev; /* previous observable lexeme */

public:
    /* error codes */
    enum{
        column_expected_error,
        statement_expected_error,
        asignment_expected_error,
        expression_in_asignment_expected_error,
        closing_bracket_expected_error,
        variable_identifier_expected_error,
        closing_index_bracket_expected_error,
        open_bracket_in_arg_list_expected_error,
        comma_in_arg_list_expected_error,
        closing_bracket_in_arg_list_expected_error,
        goto_key_word_expected_error,
        label_expected_error,
        if_key_word_expected_error,
        semicolon_after_label_expected_error,
        open_curve_bracket_in_code_block_expected_error,
        closing_curve_bracket_in_code_block_expected_error
    };

    Syntaxer()
    {
#       ifdef DEBUG
        shift = 0;
        shiftInc = 2;
#       endif
    }

    /* main anilyzing logic. Returns 0 if analyzing was successful
       and ListItem with invalid lexeme otherwise */
    const ListItem<Lexeme> *analyze(List<Lexeme> &lexemes);

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
    bool asigning();
    bool expression();
    bool variable();
    bool literal();
    bool codeBlock();
    bool argList();
    bool gotoStatement();
    bool ifStatement();

    /* checks if a lexeme is an operation.
       Second argument is unarOperations or binarOperations */
    bool isOperation(const Lexeme *lexeme, const char *operationType);
};

#endif
