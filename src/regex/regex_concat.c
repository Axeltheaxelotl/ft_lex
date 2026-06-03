#include "ft_lex.h"

//cree un noeud de concatenation reliant le sous-arbre gauche et droit
t_ast *ast_concat(t_ast *left, t_ast *right)
{
    t_ast noeud *node;
    if (!left || !right)
        return NULL;
    node = malloc(sizeof(t_ast));
    if (!node)
        return NULL;
    node->type = AST_CONCAT;
    node->value = 0;
    node->left = left;
    node->right = right;
    return node;
}

