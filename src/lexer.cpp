#include "headers/lexer.hpp"

const char *Lexer::operations = "&|!-+/%*()[]$<>~";

Lexer::Lexer()
{
    state = none;
    lexeme = new Lexeme();
    lineNumber = 1;
    position = 1;

    extraLexeme = 0;
}



void Lexer::takeCharacter(int ch)
{
    switcher(ch);

    if(state != error){
        if(isEndOfLine(ch)){
            position = 1;
            lineNumber++;
        }else{
            position++;
        }
    }
}



int Lexer::getLexerStatus() const
{
    if(state == error){
        return error_lexeme;
    }

    if(hasLexemeCreated){
        return full;
    }

    return empty;
}



Lexeme *Lexer::getLexeme()
{
    Lexeme *result = 0;

    if(hasLexemeCreated && state != error){
        result = lexeme;
        lexeme = new Lexeme();
        hasLexemeCreated = false;
    }else if (state == error){
        result = lexeme;
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
        case one_line_comment:
            oneLineCommentHandler(ch);
            break;
        case multi_line_comment:
            multiLineCommentHandler(ch);
            break;
        case escape_character:
            escapeCharacterHandler(ch);
            break;
        case extra:
            extraHandler(ch);
            break;
        case error:
            break;
    }
}



void Lexer::noneHandler(int ch)
{
    checkExistingLexeme();
    state = getState(ch);

    if(isSpace(ch) || isComment(ch)){
        return;
    }

    lexeme->string.add(ch);
    lexeme->position = position;
    lexeme->line = lineNumber;
}



void Lexer::intNumberHandler(int ch)
{
    if(checkSeparator(ch)){
        lexeme->type = Lexeme::int_number;
        return;
    }

    if(ch == '.'){
        state = float_point_number;
    }else if(!isDigit(ch)){
        state = error;
        lexeme->type = number_error;
    }

    lexeme->string.add(ch);
}



void Lexer::floatNumberHandler(int ch)
{
    if(checkSeparator(ch)){
        lexeme->type = Lexeme::float_number;
        return;
    }

    if(!isDigit(ch)){
        state = error;
        lexeme->type = number_error;
    }

    lexeme->string.add(ch);
}



void Lexer::stringHandler(int ch)
{
    if(ch == '\\'){
        state = escape_character;
        return;
    }

    if(ch == EOF){
        state = error;
        lexeme->type = no_closing_quote_error;
        return;
    }

    if((ch == '"' || ch == '\'') && lexeme->string[0] == ch){
        lexeme->type = Lexeme::string;
        hasLexemeCreated = true;
        state = none;
    }

    lexeme->string.add(ch);
}



void Lexer::identifierHandler(int ch)
{
    if(checkSeparator(ch)){
        if(lexeme->string[0] == '@'){
            lexeme->type = Lexeme::label;
        }else if(lexeme->string[0] == '_'){
            lexeme->type = Lexeme::built_in;
        }else{
            lexeme->type = Lexeme::identifier;
        }

        return;
    }

    if(!(isDigit(ch) || isLetter(ch) || ch == '_')){
        state = error;
        lexeme->type = identifier_error;
    }

    lexeme->string.add(ch);
}



void Lexer::oneLineCommentHandler(int ch)
{
    if(isEndOfLine(ch)){
        state = none;
    }
}



void Lexer::multiLineCommentHandler(int ch)
{
    if(ch == '?'){
        state = none;
    }
}



void Lexer::escapeCharacterHandler(int ch)
{
    state = string;
    lexeme->string.add(ch);
}



void Lexer::extraHandler(int ch)
{
    checkExisitngLexeme();

    lexeme->string.add(extraLexeme);
    if(isOperation(extraLexeme)){
        hasLexemeCreated = true;
        extraLexeme = ch;
    }else{
        state = getState(extraLexeme);
        switcher(ch);
    }
}



int Lexer::getState(int ch)
{
    int state;

    if(isSpace(ch)){
        state = none;
    }else if(ch == '#'){
        state = one_line_comment;
    }else if(ch == '?'){
        state = multi_line_comment;
    }else if(isDigit(ch)){
        state = integer;
    }else if(isLetter(ch) || ch == '@' || ch == '_'){
        state = identifier;
    }else if(ch == '"' || ch == '\''){
        state = string;
    }else if(isOperation(ch)){
        hasLexemeCreated = true;
        lexeme->type = Lexeme::operation;
        state = none;
    }else{
        state = error;
        lexeme->type = unexpected_char_error;
    }

    return state;
}



bool Lexer::checkSeparator(int ch)
{
    if(isOperation(ch) || isSpace(ch)){
        if(isOperation(ch)){
            extraLexeme = ch;
            extraLexemePos = position;
            extraLexemeLine = lineNumber;
        }

        state = extra;
        hasLexemeCreated = true;

        return true;
    }

    return false;
}



void Lexer::checkExistingLexeme()
{
    if(hasLexemeCreated){
        lexeme->string.clean();
        lexeme->position = position;
        lexeme->line = lineNumber;

        hasLexemeCreated = false;
    }
}
