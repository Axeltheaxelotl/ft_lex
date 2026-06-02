#ifndef REGEX_H
#define REGEX_H

#include "ft_lex.h"

/* 
contient le lexer regex.
transforme :
    (a|b)*c+
en liste de tokens
*/

typedef struct s_parser
{
    char    *input;
    size_t  pos;
} t_parser;

t_token regex_next_token(t_regex_lexer *lexer);
t_ast *regex_parse(char *regex);

#endif
