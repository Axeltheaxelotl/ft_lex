//gere l operteur plus 1 ou plusieur fois

#include "ft_lex.h"

t_nfa *thompson_plus(t_ast *ast, int *id_counter)
{
    t_nfa *left;
    t_nfa_state *start;
    t_nfa_state *end;
    t_nfa *result;

    left = thompson_build(ast->left, id_counter);
    if(!left)
        return NULL;
    //transition du nouveau debut vers le debut du sous-automate (force au moin 1 match)
    nfa_add_epsilon(start, left->start);
    //boucle de retour de la fin du sous automate vers son debut (repetiton)
    nfa_add_epsilon(left->end, left->start);
    //transition de la fin du sous automate vers la nouvelle fin (sortie)
    nfa_add_epsilon(left->end, end);

    result = nfa_new();
    if (!result)
        return NULL;
    result->start = start;
    result->end= end;

    free(left);
    return result;
}