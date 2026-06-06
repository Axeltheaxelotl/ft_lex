//lire le premier nfa au debut du deuxieme :


#include "ft_lex.h"

t_nfa *thompson_concat(t_ast *ast, int *id_counter)
{
    t_nfa *left;
    t_nfa *right;
    t_nfa *result;

    left = thompson_build(ast->left, id_counter);
    right = thompson_build(ast->right, id_counter);
    if (!left || !right)
        return NULL;
    //relie la fin de gauche au debut de droite par un lien epsilon gratuit
    nfa_add_epsilon(left->end, right->start);
    
    result = nfa_new();
    if (!result)
        return NULL;
    result->start = left->start;
    result->end = right->end;

    free(left);
    free(right);
    return result;
}