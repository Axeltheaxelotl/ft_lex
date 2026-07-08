//lier les etats entre eux avec des transitions normales ou epsilon

#include "ft_lex.h"

//cree et ajoute une transition generique de 'from' vers 'to'
void nfa_add_transition(t_nfa_state *from, t_nfa_state *to, t_transition_type type, char symbol)
{
    t_nfa_transition *new_trans;
    if (!from || !to)
    {
        return;
    }
    new_trans = malloc(sizeof(t_nfa_transition));
    if (!new_trans)
        return;
    new_trans->type = type;
    new_trans->symbol = symbol;
    new_trans->to = to;
    //ajoute en tete de la liste chainee des transitions sortantes de l etat from
    new_trans->next = from->transition;
    from->transition = new_trans;
}

//helper pour ajouter une transition epsilon (gratuite)
void nfa_add_epsilon(t_nfa_state *from, t_nfa_state *to)
{
    nfa_add_transition(from, to, TRANS_EPSILON, 0);
}

//helper pour ajouter une transition sur un caracetere precis
void nfa_add_char_transition(t_nfa_state *from, t_nfa_state *to, char symbol)
{
    nfa_add_transition(from, to, TRANS_CHAR, symbol);
}