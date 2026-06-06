//petite fonction utilitaire pour verifier si une transition es epsilon
#include "ft_lex.h"

//renvoie true si la transition est de type epsilon
bool nfa_is_epsilon_transition(t_nfa_transition *transition)
{
    return (transition && transition->type == TRANS_EPSILON);
}