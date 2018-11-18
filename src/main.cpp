#include <stdio.h>

#include "headers/lexer.hpp"



int main(int argc, const char **argv)
{
    Lexer lexer;
    FILE *in = fopen(argv[1], "r");

    int ch;

    while((ch = getc(in)) != EOF){
        lexer.takeCharacter(ch);
        if(lexer.getLexerStatus() == Lexer::full){
            Lexeme *lex = lexer.getLexeme();
            printf("%s\n", lex->word.getCharArray());
            delete lex;
        }else if(lexer.getLexerStatus() == Lexer::lexical_error){
            Lexeme *err = lexer.getLexeme();
            printf("### ERROR: %s\n", err->word.getCharArray());
            delete err;
            break;
        }
    }

    return 0;
}
