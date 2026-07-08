//creation d une etat NFA avec un identifiant unique auto incremente

#include "ft_lex.h"


//cree un nouvel etat avec un ID unique
t_nfa_state *nfa_create_state(int *id_counter)
{
    t_nfa_state *state;
    state = malloc(sizeof(t_nfa_state));
    if (!state)
        return NULL;
    state->id = (*id_counter)++;
    state->accepting = false;
    state->transition = NULL;
    return state;
}