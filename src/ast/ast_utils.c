#include "ft_lex.h"

//compte le nombre total de noeuds dans l arbre
int ast_count_nodes(t_ast *node)
{
    if (!node)
        return 0;
    return (1 + ast_count_nodes(node->left) + ast_count_nodes(node->right));
}

//retourne la profondeur maximale de l arbre
int ast_depth(t_ast *node)
{
    int left_d;
    int right_d;

    if (!node)
        return 0;
    left_d = ast_depth(node->left);
    right_d = ast_depth(node->right);
    if (left_d > right_d)
        return (1 + left_d);
    return (1 + right_d);
}


//duplique un arbre ast en profondeur
t_ast *ast_dup(t_ast *node)
{
    t_ast *copy;
    
    if (!node)
        return NULL;
    copy = malloc(sizeof(t_ast));
    if (!copy)
        return NULL;
    copy->type = node->type;
    copy->value = node->value;
    copy->left = ast_dup(node->left);
    copy->right = ast_dup(node->right);
    return copy;
}


//verifie si un noeud est une feuille pas d enfants
int ast_is_leaf(t_ast *node)
{
    if (!node)
        return 0;
    return (node->left == NULL && node->right == NULL);
}