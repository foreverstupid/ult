#include "headers/syntaxer.hpp"

const ListItem *Syntaxer::analyze(List<Lexeme> &lexemes)
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
}



bool Syntaxer::program()
{
    while(curr){
        if(!statement){
            return false;
        }

        if(curr->obj->word != ';'){
            setErrorCode(column_expected_error);
            return false;
        }

        step();
    }

    return true;
}



bool Syntaxer::statement()
{
    if(assinging()){
        return true;
    }

    if(ifStatement()){
        return true;
    }

    if(gotoStatement()){
        return true;
    }

    if(expression()){
        return true;
    }

    if(curr->obj->type == Lexeme::label){
        step();
        if(!statement()){
            return false;
        }

        return true;
    }

    return false;
}
