//gere l operateur *

#include "ft_lex.h"

t_nfa *thompson_star(t_ast *ast, int *id_counter)
{
    t_nfa *left;
    t_nfa_state *start;
    t_nfa_state *end;
    t_nfa *result;

    left = thompson_build(ast->left, id_counter);
    if (!left)
        return NULL;
    start = nfa_create_state(id_counter);
    end = nfa_create_state(id_counter);
    if (!start || !end)
        return NULL;

    //transition du nouveau debut vers le debut du sous-automate (match >= 1)
    nfa_add_epsilon(start, left->start);
    //transition du nouveau debut vers la nouvelle fin (bypass, match 0)
    nfa_add_epsilon(start, end);
    //boucle de retour de la fin du sous-automate vers le debut (repetition)
    nfa_add_epsilon(left->end, left->start);
    //transition de la fin du sous-automate vers la nouvelle fin (sortie)
    nfa_add_epsilon(left->end, end);

    result = nfa_new();
    if (!result)
        return NULL;
    result->start = start;
    result->end = end;

    free(left);
    return result;
}