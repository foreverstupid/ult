#include <stdio.h>

#include "headers/list.hpp"
#include "headers/lexer.hpp"
#include "headers/syntaxer.hpp"

const char *err_msgs[] = {
    "Expected statement",
    "Expected ')' in expression",
    "Expected ']'",
    "Expected '('",
    "Expected ','",
    "Expected ')' in arg list",
    "Expected 'goto' keyword",
    "Expected label name",
    "Expected 'if' keyword",
    "Expected ':'",
    "Expected '{'",
    "Expected ';'",
    "Expected '='",
    "Expected indentifier in lvalue expression",
    "Expected '['"
};



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
            int t = curr->obj->type;
            const char *type =
                t == Lexeme::int_number ? "int" :
                t == Lexeme::float_number ? "float":
                t == Lexeme::string ? "string":
                t == Lexeme::identifier ? "identifier":
                t == Lexeme::label ? "label":
                t == Lexeme::operation ? "operation" : "";
            printf("%20s:%s\n", curr->obj->word.getCharArray(), type);
            curr = curr->next;
        }

        printf("\n=============== SYNTAX ANALYZING ================\n");
        curr = syntaxer.analyze(lexemes);

        if(curr){
            printf("### ERROR: %s\n", err_msgs[curr->obj->type]);
        }
    }else{
        printf("### ERROR:\n");
    }

    return 0;
}
