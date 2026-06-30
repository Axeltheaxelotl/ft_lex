#include "ft_lex.h"

/*
convertit un automate nfa en un automate dfa complet et minimise
*/
t_dfa *nfa_to_dfa(t_nfa *nfa)
{
    t_dfa *raw_dfa = subset_construction(nfa);
    if (!raw_dfa)
        return NULL;
    t_dfa *min_dfa = dfa_minize(raw_dfa);
    free(raw_dfa);
    return min_dfa;
}