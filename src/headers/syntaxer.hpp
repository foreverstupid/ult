#ifndef SYNTAXER_CLASS_HPP
#define SYNTAXER_CLASS_HPP

#include "list.hpp"
#include "lexer.hpp"
#include "debug_trace.hpp"

/*
 * Syntax analyzer
 */
class Syntaxer{
    SyntaxTreeTracer tracer;        /* for debug */

    static const char *unarOperations;
    static const char *binarOperations;

    const ListItem<Lexeme> *curr;   /* current observable lexeme */
    const ListItem<Lexeme> *prev;   /* previous observable lexeme */

    int errorCode;                  /* code of syntax error */

public:
    /* error codes */
    enum{
        statement_expected_error,
        closing_bracket_expected_error,
        closing_index_bracket_expected_error,
        open_bracket_in_arg_list_expected_error,
        comma_in_arg_list_expected_error,
        closing_bracket_in_arg_list_expected_error,
        goto_key_word_expected_error,
        label_expected_error,
        if_key_word_expected_error,
        semicolon_after_label_expected_error,
        open_curve_bracket_in_code_block_expected_error,
        statement_delimiter_expected_error,
        assignment_expected_error,
        identifier_in_lvalue_expected_error,
        open_braket_in_indexator_expected_error
    };

    Syntaxer() {}

    /* main anilyzing logic. Returns 0 if analyzing was successful
       and ListItem with invalid lexeme otherwise */
    const ListItem<Lexeme> *analyze(List<Lexeme> &lexemes);

private:
    Syntaxer(const Syntaxer &sntxr);
    void operator=(const Syntaxer &sntxr);

    /* sets error code */
    void setErrorCode(int err){ errorCode = err; }

    /* makes one step */
    void step();

    /* grammar states */
    bool program();
    bool statement();
    bool assignment();
    bool lvalue();
    bool tail();
    bool indexator();
    bool args();
    bool expression();
    bool operand();
    bool deref();
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
