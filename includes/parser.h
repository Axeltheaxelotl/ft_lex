#ifndef PARSER_H
#define PARSER_H

#include "ft_lex.h"

/*
le parser transforme
token -> AST
*/

typedef struct s_parser
{
    t_regex_lexer lexer;
    t_token current;
} t_parser;

t_ast *parse_regex(t_parser *parser);

#endif