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
t_nfa_state *nfa_create_state(int *id_counter);
void nfa_add_transition(t_nfa_state *from, t_nfa_state *to, t_transition_type type, char symbol);
void nfa_add_epsilon(t_nfa_state *from, t_nfa_state *to);
void nfa_add_char_transition(t_nfa_state *from, t_nfa_state *to, char symbol);
t_nfa *nfa_new(void);
bool nfa_is_epsilon_transition(t_nfa_transition *transition);

//moteur de thompson
t_nfa *nfa_from_ast(t_ast *ast);
t_nfa *thompson_build(t_ast *ast, int *id_counter);
t_nfa *thompson_char(char c,  int *id_counter);
t_nfa *thompson_concat(t_ast *ast, int *id_counter);
t_nfa *thompson_or(t_ast *ast, int *id_counter);
t_nfa *thompson_star(t_ast *ast, int *id_counter);
t_nfa *thompson_plus(t_ast *ast, int *id_counter);
t_nfa *thompson_optional(t_ast *ast, int *id_counter);

void print_nfa(t_nfa *nfa);

#endif