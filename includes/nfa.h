#ifndef NFA_H
#define NFA_H

#include "ft_lex.h"

//automate de thompson

//transition
typedef enum e_transition_type
{
    TRANS_CHAR,
    TRANS_EPSILON,
} t_transition_type;


//transition nfa

typedef struct s_nfa_state t_nfa_state;

typedef struct s_nfa_transition
{
    t_transition_type type;
    char symbol;
    t_nfa_state *to;
    struct s_nfa_transition *next;
} t_nfa_transition;

//etat nfa

typedef struct s_nfa_state
{
    int id;
    bool accepting;
    t_nfa_transition *transition;
} t_nfa_state;

//fragment thompson

/*
tres important
chaque operateur renvoie
    start
    end
*/

typedef struct s_nfa
{
    t_nfa_state *start;
    t_nfa_state *end;
}t_nfa;


t_nfa *nfa_from_ast(t_ast *ast);
void print_nfa(t_nfa *nfa);

#endif