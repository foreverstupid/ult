#include <stdio.h>

#include "headers/list.hpp"
#include "headers/lexer.hpp"



int main(int argc, const char **argv)
{
    FileTextGetter tg(argv[1]);
    List<Lexeme> lexemes;
    const ListItem<Lexeme> *curr;

    if(makeLexemeList(tg, lexemes)){
        curr = lexemes.getFirstItem();
        while(curr){
            printf("%s\n", curr->obj->word.getCharArray());
            curr = curr->next;
        }
    }else{
        printf("### ERROR:\n");
    }

    return 0;
}
