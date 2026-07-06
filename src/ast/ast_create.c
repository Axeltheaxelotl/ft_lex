#include "ft_lex.h"

//cree un noeud ast generique
static t_ast *ast_new(t_ast_type type, char value, t_ast *left, t_ast *right)
{
    t_ast *node;

    node = malloc(sizeof(t_ast));
    if (!node)
        return NULL;
    node->type = type;
    node->value = value;
    node->left = left;
    node->right = right;
    return node;
}


//CHAR 'c; -> feuille, pas d enfants
t_ast *ast_char(char c)
{
    return (ast_new(AST_CHAR, c, NULL, NULL)); // feuille = pas d enfants
}

//cree un noeud CONCAT : left puis right (ex: ab)
t_ast *ast_concat(t_ast *left, t_ast *right)
{
    return (ast_new(AST_CONCAT, 0, left , right)); //0 cas pas de caractere
}

//cree un noeud OR : left ou right (ex: a|b)
t_ast *ast_or(t_ast *left, t_ast *right)
{
    return (ast_new(AST_OR, 0, left, right)); //alternance entre deux branches
}

//cree un noeud STAR : zero ou plusieurs (ex: a*)
t_ast *ast_star(t_ast *child)
{
    return (ast_new(AST_STAR, 0, child, NULL)); //operateur unaire = un seul enfant
}

//cree un noued PLUS: un ou plusieurs (ex: a+)
t_ast *ast_plus(t_ast *child)
{
    return (ast_new(AST_PLUS, 0, child, NULL)); //comme star mais au moins 1
}

//cree un noeud OPTINAL : zero ou un (ex: a?)
t_ast *ast_question(t_ast *child)
{
    return (ast_new(AST_OPTIONAL, 0, child, NULL)); //rend l enfant optionnel
}