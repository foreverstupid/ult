#include <stdio.h>

#include "headers/list.hpp"
#include "headers/lexer.hpp"
#include "headers/syntaxer.hpp"



int main(int argc, const char **argv)
{
    FileTextGetter tg(argv[1]);
    List<Lexeme> lexemes;
    const ListItem<Lexeme> *curr;
    Syntaxer syntaxer;

    if(makeLexemeList(tg, lexemes)){
        printf("============ LEXICAL ANALYZING ============\n");
        curr = lexemes.getFirstItem();
        while(curr){
            printf("%s\n", curr->obj->word.getCharArray());
            curr = curr->next;
        }

        printf("\n=============== SYNTAX ANALYZING ================\n");
        curr = syntaxer.analyze(lexemes);

        if(curr){
            printf("### ERROR:\n");
        }
    }else{
        printf("### ERROR:\n");
    }

    return 0;
}
