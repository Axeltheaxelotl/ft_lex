//gere l operateur | (embranchement double) :

#include "ft_lex.h"

t_nfa *thompson_or(t_ast *ast, int *id_counter)
{
    t_nfa *left;
    t_nfa *right;
    t_nfa_state *start;
    t_nfa_state *end;
    t_nfa *result;

    left = thompson_build(ast->left, id_counter);
    right = thompson_build(ast->right, id_counter);
    if (!left || !right)
        return NULL;
    start = nfa_create_state(id_counter);
    end  = nfa_create_state(id_counter);
    if (!start || !end)
        return NULL;

    //relie le nouveau depart aux deux sous-autmates
    nfa_add_epsilon(start, left->start);
    nfa_add_epsilon(start, right->start);

    //relie les sorties des deux sous-automates a la nouvelle fin
    nfa_add_epsilon(left->end, end);
    nfa_add_epsilon(right->end, end);

    result = nfa_new();
    if (!result)
        return NULL;
    result->start = start;
    result->end = end;

    free(left);
    free(right);
    return result;
}