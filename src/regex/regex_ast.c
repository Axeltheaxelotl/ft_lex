/*
definir ast
un ast pour une regex c est juste un arbre

pour :
    (a|b)*c
je veut :
                CONCAT
                /    \
              STAR     c
               |
               OR
              /  \
             a    b
*/

#include "ft_lex.h"

//constructeur generique

static t_ast *ast_new(t_ast_type type)
{
    t_ast *node;
    node = malloc(sizeof(t_ast));
    if (!node)
        return NULL
    node->type = type;
    node->value = 0;
    node->left = NULL;
    node->right = NULL;

    return node;
}



/*
caractere
pour :
    a
je veut :
    CHAR(a)
*/
t_ast *ast_char(char c)
{
    t_ast *node;
    node = ast_new(AST_CHAR);
    if (!node)
        return NULL;
    node->value = c;
    return node;
}


/*
concat
pour :
    ab
je veut
         CONCAT
         /   \
        a     b
*/
t_ast *ast_or(t_ast *left, t_ast *right)
{
    t_ast *node;
    node = ast_new(AST_OR);
    if (!node)
        return NULL;
    node->left = left;
    node->right = right;
    return node;
}



//etoile de kleene
/*
pour a*
    STAR
      |
      a
*/

t_ast *ast_char(t_ast *child)
{
    t_ast *node;
    node = ast_new(AST_STAR);
    if (!node)
        return NULL;
    node->left = child;
    return node;
}



//PLUS
t_ast *ast_plus(t_ast *child)
{
    t_ast *node;
    node = ast_new(AST_PLUS);
    if (!node)
        return NULL;
    node->left = child;
    return node;
}


