#ifndef DFA_H
#define DFA_H

#include "ft_lex.h"

//definition des constantes de l automate DFA
//DFA_ALPHABE represente la taille de l alpabet supporte (256 caractere ASCII)
#define DFA_ALPHABET 256
//represente le nb maximnal d etats autorises dans le dfa
#define DFA_MAX_STATES 1024



//struct pour representer un essemble d etats NFA
typedef struct s_nfa_state_set
{
    t_nfa_state *states[1000];
    int count;
}t_nfa_state_set;


//structure representant un etat DFA7
typedef struct s_dfa_state
{
    int id;
    bool accepting;
    int accepting_rule; //index de la regle dans t_lex_file.rules[]
    int transition[DFA_ALPHABET];
}t_dfa_state;


//structure representant l automate DFA complet
typedef struct s_dfa
{
    t_dfa_state states[DFA_MAX_STATES];
    int count;
    int start;
}t_dfa;


//prototypes pour la manipulation des ensembles d etats NFA
void set_init(t_nfa_state_set *set);
bool set_contains(t_nfa_state_set *set, t_nfa_state *state);
bool set_add(t_nfa_state_set *set, t_nfa_state *state);
void set_sort(t_nfa_state_set *set);
bool set_equals(t_nfa_state_set *set1, t_nfa_state_set *set2);



//pour l epsilon-fermeture
t_nfa_state_set epsilon_closure(t_nfa_state *state);
t_nfa_state_set epsilon_closure_set(t_nfa_state_set *set);


//prototypes pour la fonction move
t_nfa_state_set move(t_nfa_state_set *set, char symbol);

//prototypes pour la subset construction
t_dfa *subset_construction(t_nfa *nfa);

//prototype pour la minimilatisation   
t_dfa *dfa_minize(t_dfa *dfa);

//prototype pour la table de transition
void dfa_set_transition(t_dfa *dfa, int state_id, char symbol, int next_state_id);
int dfa_get_transition(t_dfa *dfa, int state_id, char symbol);

//prototype pour le debug
t_dfa *nfa_to_dfa(t_nfa *nfa);
void print_dfa(t_dfa *dfa);

#endif