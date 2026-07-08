//gere  l initialisation de l enveloppe de l automate t_nfa

#include "ft_lex.h"

//alloue et initialise une nouvelle enveloppe NFA
t_nfa *nfa_new(void)
{
    t_nfa *nfa;
    nfa = malloc(sizeof(t_nfa));
    if (!nfa)
        return NULL;
    nfa->start = NULL;
    nfa->end = NULL;
    return nfa;
}