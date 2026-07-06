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


//ast_create.c
t_ast *ast_char(char c);
t_ast *ast_concat(t_ast *left, t_ast *right);
t_ast *ast_or(t_ast *left, t_ast *right);
t_ast *ast_star(t_ast *child);
t_ast *ast_plus(t_ast *child);
t_ast *ast_question(t_ast *child);

//ast_destroy.c
void ast_free(t_ast *node);

//ast_print.c
vois ast_print(t_ast *node, int depth);

//ast_utils.c
int ast_count_nodes(t_ast *node);
int ast_depth(t_ast *node);
t_ast *ast_dup(t_ast *node);
int ast_is_leaf(t_ast *node);

#endif
