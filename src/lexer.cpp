#include "headers/lexer.hpp"

int Lexer::takeCharacter(int ch)
{
    switcher(ch);
    return errorStatus;
}



Lexeme *Lexer::getLexeme()
{
    Lexeme *result = 0;

    if(hasLexemeCreated()){
        result = lexeme;
        lexeme = new Lexeme();
    }

    return result;
}



void Lexer::switcher(int ch)
{
    switch(state){
        case none:
            noneHandler(ch);
            break;
        case integer:
            intNumberHandler(ch);
            break;
        case float_point_number:
            floatNumberHandler(ch);
            break;
        case string:
            stringHandler(ch);
            break;
        case identifier:
            identifierHandler(ch);
            break;
        case comment:
            commentHandler(ch);
            break;
        case error:
            errorHandler(ch);
            break;
    }
}



void Lexer::noneHandler(int ch)
{
    if(isDigit(ch)){
        state = integer;
    }else if(isLetter(ch)){
        state = identifier;
    }else if(ch == '"' || ch == '\''){
        state = string;
    }
}
