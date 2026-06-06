#ifndef DFA_H
#define DFA_H

#include "ft_lex.h"

typedef struct s_dfa_state
{
    int id;
    bool accepting;
    int transition[DFA_ALPAHBET];
} t_dfa_state;


//automate dfa

typedef struct s_dfa
{
    t_dfa_state states[DFA_MAX_STATES];
    int count;
    int start;
} t_dfa;


t_dfa *nfa_to_dfa(t_nfa *nfa);
void print_dfa(t_dfa *dfa);

#enfif