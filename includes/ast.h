#ifndef AST_H
#define AST_H

#include "ft_lex.h"

/*
l ast c est la representation logique du regex
ex :
    (a|b)*c+
                  CONCAT
                  /      \
              STAR      PLUS
               |          |
               OR         c
              /   \
             a     b
*/

typedef enum  e_ast_type
{
    AST_CHAR,

    AST_CONCAT,
    AST_OR,

    AST_STAR,
    AST_PLUS,
    AST_OPTIONAL,
} t_ast_type;

typedef struct s_ast
{
    t_ast_type type;
    char  value;
    struct s_ast *left;
    struct s_ast *right;
} t_ast;

#endif
