#include "headers/syntaxer.hpp"

const char *Syntaxer::unarOperations = "-!+";
const char *Syntaxer::binarOperations = "+-*/&|><~%^";

const ListItem<Lexeme> *Syntaxer::analyze(List<Lexeme> &lexemes)
{
    prev = curr = lexemes.getFirstItem();

    if(program()){
        return 0;
    }else{
        prev->obj->type = errorCode;
        return prev;
    }
}



void Syntaxer::step()
{
    if(prev != curr){
        prev = curr;
    }

    curr = curr->next;
    tracer.write(prev->obj->word.getCharArray());
}



bool Syntaxer::program()
{
    tracer.enter("__PROGRAM__");

    while(curr){
        if(!statement()){
            tracer.exit(false);
            return false;
        }

        step();
    }

    tracer.exit(true);
    return true;
}



bool Syntaxer::statement()
{
    bool hlp;

    tracer.enter("__STATEMENT__");

    if(curr->obj->type == Lexeme::label){
        step();
        if(curr->obj->word != ':'){
            setErrorCode(semicolon_after_label_expected_error);
            tracer.exit(false);
            return false;
        }

        step();

        hlp = statement();
        tracer.exit(hlp);
        return hlp;
    }

    if(ifStatement()){
        tracer.exit(true);
        return true;
    }

    if(expression() || gotoStatement() || assignment()){
        tracer.exit(true);
        return true;
    }

    tracer.exit(false);
    return false;
}



bool Syntaxer::assignment()
{
    bool hlp;

    tracer.enter("__ASSIGNMENT__");

    if(!lvalue()){
        tracer.exit(false);
        return false;
    }

    if(curr->obj->word != '='){
        setErrorCode(assignment_expected_error);
        tracer.exit(false);
        return false;
    }

    step();

    hlp = expression();
    tracer.exit(hlp);
    return hlp;
}



bool Syntaxer::lvalue()
{
    bool hlp;

    tracer.enter("__LVALUE__");

    if(curr->obj->type != Lexeme::identifier){
        setErrorCode(identifier_in_lvalue_expected_error);
        tracer.exit(false);
        return false;
    }

    step();

    hlp = tail();
    tracer.exit(hlp);
    return hlp;
}



bool Syntaxer::tail()
{
    bool hlp;

    tracer.enter("__TAIL__");

    if(indexator() || args()){
        hlp = tail();
        tracer.exit(hlp);
        return hlp;
    }

    tracer.exit(true);
    return true;
}



bool Syntaxer::indexator()
{
    tracer.enter("__INDEXATOR__");

    if(curr->obj->word != '['){
        setErrorCode(open_braket_in_indexator_expected_error);
        tracer.exit(false);
        return false;
    }

    step();

    if(!expression()){
        tracer.exit(false);
        return false;
    }

    if(curr->obj->word != ']'){
        setErrorCode(closing_index_bracket_expected_error);
        tracer.exit(false);
        return false;
    }

    step();

    tracer.exit(true);
    return true;
}



bool Syntaxer::args()
{
    tracer.enter("__ARGS__");

    if(curr->obj->word != ')'){
        setErrorCode(open_bracket_in_arg_list_expected_error);
        tracer.exit(false);
        return false;
    }

    step();

    if(curr->obj->word == ')'){
        step();
        tracer.exit(true);
        return true;
    }

    if(!expression()){
        tracer.exit(false);
        return false;
    }

    while(curr->obj->word != ')'){
        if(curr->obj->word != ','){
            setErrorCode(comma_in_arg_list_expected_error);
            tracer.exit(false);
            return false;
        }

        step();

        if(!expression()){
            tracer.exit(false);
            return false;
        }
    }

    step();

    tracer.exit(true);
    return true;
}



bool Syntaxer::expression()
{
    bool hlp;

    tracer.enter("__EXPRESSION__");

    if(isOperation(curr->obj, unarOperations)){
        step();
    }

    if(!operand()){
        tracer.exit(false);
        return false;
    }

    while(isOperation(curr->obj, binarOperations)){
        step();

        if(!expression()){
            tracer.exit(false);
            return false;
        }
    }

    hlp = tail();
    tracer.exit(hlp);
    return hlp;
}



bool Syntaxer::operand()
{
    bool hlp;

    tracer.enter("__ENTER__");

    if(curr->obj->word == '('){
        step();

        if(!expression()){
            tracer.exit(false);
            return false;
        }

        if(curr->obj->word != ')'){
            setErrorCode(closing_bracket_expected_error);
            tracer.exit(false);
            return false;
        }

        step();

        tracer.exit(true);
        return true;
    }

    if(curr->obj->word == '$'){
        step();

        hlp = lvalue();
        tracer.exit(hlp);
        return hlp;
    }

    hlp = literal();
    tracer.exit(hlp);
    return hlp;
}



bool Syntaxer::literal()
{
    bool hlp;
    int type = curr->obj->type;

    tracer.enter("__LITERAL__");

    hlp = type == Lexeme::int_number || type == Lexeme::float_number ||
        type == Lexeme::string || codeBlock();

    tracer.exit(hlp);
    return hlp;
}



bool Syntaxer::gotoStatement()
{
    tracer.enter("__GOTO__");

    if(curr->obj->word != "goto"){
        setErrorCode(goto_key_word_expected_error);
        tracer.exit(false);
        return false;
    }

    step();

    if(curr->obj->type != Lexeme::label){
        setErrorCode(label_expected_error);
        tracer.exit(false);
        return false;
    }

    step();

    tracer.exit(true);
    return true;
}



bool Syntaxer::codeBlock()
{
    tracer.enter("__CODE_BLOCK__");

    if(curr->obj->word != '{'){
        setErrorCode(open_curve_bracket_in_code_block_expected_error);
        tracer.exit(false);
        return false;
    }

    step();

    if(!program()){
        tracer.exit(false);
        return false;
    }

    if(curr->obj->word != '}'){
        setErrorCode(closing_curve_bracket_in_code_block_expected_error);
        tracer.exit(false);
        return false;
    }

    step();

    tracer.exit(true);
    return true;
}



bool Syntaxer::ifStatement()
{
    tracer.enter("__IF__");

    if(curr->obj->word != "if"){
        setErrorCode(if_key_word_expected_error);
        tracer.exit(false);
        return false;
    }

    step();

    /* CHECK: do we need brackets */

    if(!expression()){
        tracer.exit(false);
        return false;
    }

    if(!codeBlock()){
        tracer.exit(false);
        return false;
    }

    tracer.exit(true);
    return true;
}



bool Syntaxer::isOperation(const Lexeme *lexeme,
    const char *operationType)
{
    if(lexeme->type != Lexeme::operation){
        return false;
    }

    for(int i = 0; operationType[i]; i++){
        if(lexeme->word == operationType[i]){
            return true;
        }
    }

    return false;
}
