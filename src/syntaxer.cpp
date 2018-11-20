#include "headers/syntaxer.hpp"

const char *Syntaxer::unarOperations = "-!+";
const char *Syntaxer::binarOperations = "+-*/&|><~%^";

const ListItem<Lexeme> *Syntaxer::analyze(List<Lexeme> &lexemes)
{
    prev = curr = lexemes.getFirstItem();

    if(program()){
        return 0;
    }else{
        return prev;
    }
}



void Syntaxer::step()
{
    if(prev != curr){
        prev = curr;
    }

    curr = curr->next;

#   ifdef DEBUG
    printf("%*s%s ", shift, "", prev->obj->word.getCharArray());
#   endif
}



bool Syntaxer::program()
{
#   ifdef DEBUG
    printf("\n%*s%s\n", shift, "", "<PROGRAM>");
    shift += shiftInc;
#   endif

    while(curr){
        if(!statement()){
            return false;
        }

        if(curr->obj->word != ';'){
            setErrorCode(column_expected_error);
            return false;
        }

        step();
    }

#   ifdef DEBUG
    shift -= shiftInc;
    printf("\n%*s%s\n", shift, "", "</PROGRAM>");
#   endif

    return true;
}



bool Syntaxer::statement()
{
#   ifdef DEBUG
    printf("\n%*s%s\n", shift, "", "<STATEMENT>");
    shift += shiftInc;
#   endif

    if(curr->obj->type == Lexeme::label){
        step();
        if(curr->obj->word != ':'){
            setErrorCode(semicolon_after_label_expected_error);
            return false;
        }

        step();
        if(!statement()){
            return false;
        }

#       ifdef DEBUG
        shift -= shiftInc;
        printf("\n%*s%s\n", shift, "", "</STATEMENT>");
#       endif
        return true;
    }


    if(asigning()){

#       ifdef DEBUG
        shift -= shiftInc;
        printf("\n%*s%s\n", shift, "", "</STATEMENT>");
#       endif
        return true;
    }

    if(ifStatement()){

#       ifdef DEBUG
        shift -= shiftInc;
        printf("\n%*s%s\n", shift, "", "</STATEMENT>");
#       endif
        return true;
    }

    if(gotoStatement()){

#       ifdef DEBUG
        shift -= shiftInc;
        printf("\n%*s%s\n", shift, "", "</STATEMENT>");
#       endif
        return true;
    }

    if(expression()){

#       ifdef DEBUG
        shift -= shiftInc;
        printf("\n%*s%s\n", shift, "", "</STATEMENT>");
#       endif
        return true;
    }

    return false;
}



bool Syntaxer::asigning()
{
#   ifdef DEBUG
    printf("\n%*s%s\n", shift, "", "<ASIGNING>");
    shift += shiftInc;
#   endif

    if(!variable()){
        return false;
    }

    if(curr->obj->word != '='){
        setErrorCode(asignment_expected_error);
        return false;
    }

    step();
    if(!expression()){
        return false;
    }

#   ifdef DEBUG
    shift -= shiftInc;
    printf("\n%*s%s\n", shift, "", "</ASIGNING>");
#   endif
    return true;
}



bool Syntaxer::expression()
{
#   ifdef DEBUG
    printf("\n%*s%s\n", shift, "", "<EXPRESSION>");
    shift += shiftInc;
#   endif

    if(isOperation(curr->obj, unarOperations)){
        step();

        if(!expression()){
            return false;
        }

#       ifdef DEBUG
        shift -= shiftInc;
        printf("\n%*s%s\n", shift, "", "</EXPRESSION>");
#       endif

        return true;
    }

    if(curr->obj->word == '('){
        step();

        if(!expression()){
            return false;
        }

        if(curr->obj->word != ')'){
            setErrorCode(closing_bracket_expected_error);
            return false;
        }

        step();

#       ifdef DEBUG
        shift -= shiftInc;
        printf("\n%*s%s\n", shift, "", "</EXPRESSION>");
#       endif
        return true;
    }

    if(literal()){

#       ifdef DEBUG
        shift -= shiftInc;
        printf("\n%*s%s\n", shift, "", "</EXPRESSION>");
#       endif
        return true;
    }

    if(curr->obj->word == '$'){
        step();

        if(!variable()){
            return false;
        }

#       ifdef DEBUG
        shift -= shiftInc;
        printf("\n%*s%s\n", shift, "", "</EXPRESSION>");
#       endif

        return true;
    }

    if(expression()){
        if(isOperation(curr->obj, binarOperations)){
            step();

            if(!expression()){
                return false;
            }

#           ifdef DEBUG
            shift -= shiftInc;
            printf("\n%*s%s\n", shift, "", "</EXPRESSION>");
#           endif

            return true;
        }

        if(argList()){

#           ifdef DEBUG
            shift -= shiftInc;
            printf("\n%*s%s\n", shift, "", "</EXPRESSION>");
#           endif
            return true;
        }

        return false;
    }

    return false;
}



bool Syntaxer::variable()
{
#   ifdef DEBUG
    printf("\n%*s%s\n", shift, "", "<VARIABLE>");
    shift += shiftInc;
#   endif

    if(curr->obj->type != Lexeme::identifier){
        setErrorCode(variable_identifier_expected_error);
        return false;
    }

    step();
    while(curr->obj->word == '['){
        step();

        if(!expression()){
            return false;
        }

        if(curr->obj->word != ']'){
            setErrorCode(closing_index_bracket_expected_error);
            return false;
        }

        step();
    }

#   ifdef DEBUG
    shift -= shiftInc;
    printf("\n%*s%s\n", shift, "", "</VARIABLE>");
#   endif
    return true;
}



bool Syntaxer::literal()
{
#   ifdef DEBUG
    printf("\n%*s%s\n", shift, "", "<LITERAL>");
    shift += shiftInc;
#   endif

    int type = curr->obj->type;

    if(type == Lexeme::string || type == Lexeme::int_number ||
        type == Lexeme::float_number)
    {
        step();

#       ifdef DEBUG
        shift -= shiftInc;
        printf("\n%*s%s\n", shift, "", "</LITERAL>");
#       endif
        return true;
    }

    if(codeBlock()){
#       ifdef DEBUG
        shift -= shiftInc;
        printf("\n%*s%s\n", shift, "", "</LITERAL>");
#       endif
        return true;
    }

    return false;
}



bool Syntaxer::argList()
{
#   ifdef DEBUG
    printf("\n%*s%s\n", shift, "", "<ARGLIST>");
    shift += shiftInc;
#   endif

    if(curr->obj->word != '('){
        setErrorCode(open_bracket_in_arg_list_expected_error);
        return false;
    }

    step();
    if(expression()){
        while(curr->obj->word != ')'){
            if(curr->obj->word != ','){
                setErrorCode(comma_in_arg_list_expected_error);
                return false;
            }

            step();
            if(!expression()){
                return false;
            }
        }
    }else{
        if(curr->obj->word != ')'){
            setErrorCode(closing_bracket_in_arg_list_expected_error);
            return false;
        }
    }

    step();

#   ifdef DEBUG
    shift -= shiftInc;
    printf("\n%*s%s\n", shift, "", "</ARGLIST>");
#   endif
    return true;
}



bool Syntaxer::gotoStatement()
{
#   ifdef DEBUG
    printf("\n%*s%s\n", shift, "", "<GOTO>");
    shift += shiftInc;
#   endif

    if(curr->obj->word != "goto"){
        setErrorCode(goto_key_word_expected_error);
        return false;
    }

    step();
    if(curr->obj->type != Lexeme::label){
        setErrorCode(label_expected_error);
        return false;
    }

    step();

#   ifdef DEBUG
    shift -= shiftInc;
    printf("\n%*s%s\n", shift, "", "</GOTO>");
#   endif
    return true;
}



bool Syntaxer::codeBlock()
{
#   ifdef DEBUG
    printf("\n%*s%s\n", shift, "", "<CODE_BLOCK>");
    shift += shiftInc;
#   endif

    if(curr->obj->word != '{'){
        setErrorCode(open_curve_bracket_in_code_block_expected_error);
        return false;
    }

    step();
    if(!program()){
        return false;
    }

    if(curr->obj->word != '}'){
        setErrorCode(closing_curve_bracket_in_code_block_expected_error);
        return false;
    }

    step();

#   ifdef DEBUG
    shift -= shiftInc;
    printf("\n%*s%s\n", shift, "", "</CODE_BLOCK>");
#   endif
    return true;
}



bool Syntaxer::ifStatement()
{
#   ifdef DEBUG
    printf("\n%*s%s\n", shift, "", "<IF>");
    shift += shiftInc;
#   endif

    if(curr->obj->word != "if"){
        setErrorCode(if_key_word_expected_error);
        return false;
    }

    step();
    if(!expression()){
        return false;
    }

    if(!codeBlock()){
        return false;
    }

#   ifdef DEBUG
    shift -= shiftInc;
    printf("\n%*s%s\n", shift, "", "</IF>");
#   endif

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
