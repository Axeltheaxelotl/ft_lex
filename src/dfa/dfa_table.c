#include "ft_lex.h"

/*
gestion des transition de la table dfa
*/


/*
definit une transition  dans la table de transition dfa
*/
void dfa_set_transition(t_dfa *dfa, int state_id, char symbol, int next_state_id)
{
    if(!dfa || state_id < 0 || state_id >= DFA_MAX_STATES)
        return;
    unsigned char idx = (unsigned char)symbol;
    dfa->states[state_id].transition[idx] = next_state_id;
}

/*
recupere une transition depuis la table de transition du dfa
retourn -1 si aucune transition n est definie
*/
int dfa_get_transition(t_dfa *dfa, int state_id, char symbol)
{
    if (!dfa || state_id < 0 || state_id >= DFA_MAX_STATES)
        return -1;
    unsigned char idx = (unsigned char)symbol;
    return dfa->states[state_id].transition[idx];
}