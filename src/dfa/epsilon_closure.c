#include "ft_lex.h"

//le fichier c pour implemente le calcul de la fermeture epsilon d un etat ou d un ensemble
//d etats. elle permet de trouver tous les etats nfa accesibles dans consommer aucun caractere


/*
calcul de la fermeture epsilon pour un seul etat nfa donne
la fermeture epsilon represente l ensemble  de tous les etats nfa accesibles
a partir de l etat de depart uniquement en traversant des transitions epsilon
un etat fait toujours partie de sa propre fermeture epsilon

utilise la struct t_nfa_state_set comme une worklist dynamique
*/
t_nfa_state_set epsilon_closure(t_nfa_state *state)
{
    t_nfa_state_set closure;

    set_init(&closure);
    if (!state)
        return closure;

    //un etat est toujours dans sa propre fermeture epsilon
    set_add(&closure, state);

    //on parcourt dynamiquement la liste. Si set_add ajoute de nouveaux etats
    //nfa, closure.count augemente et uls seront traites aux iterations suivantes
    for (int i = 0; i < closure.count; i++)
    {
        t_nfa_state *current = closure.states[i];
        t_nfa_transition *trans = current->transitions;
        while (trans)
        {
            //si la transition est de type epsilon
            if (trans->type == TRANS_EPSILON)
            {
                //je tenete de rajouter l etat cible a la fermeture
                set_add(&closure, trans->to);
            }
            trans = trans->next;
        }
    }
    //trie final pour rendre l ensemble canonique
    set_sort(&closure);
    return closure;
}




/*
calcule la fermeture apsilon pour un esemble complet d etats nfa
il s agit de l union des fermetures epsilon individuelles de chacun des etats de l ensemble
*/
t_nfa_state_set epsilon_closure_set(t_nfa_state_set *set)
{
    t_nfa_state_set closure;
    set_init(&closure);
    if (!set)
        return closure;
    //initialise l ensemble final avec tous les etats de l ensemble fourni
    for (int i = 0; i < set->count; i++)
    {
        set_add(&closure, set_>states[i]);
    }

    //parcours iteratif et propagation des transitions epsilon pour tout nouvel etat decouvert
    for (int i = 0; i < closure.count; i++)
    {
        t_nfa_state *current  = closure.states[i];
        t_nfa_transition *trans = current->transition;

        while(trans)
        {
            if (trans->type == TRANS_EPSILON)
            {
                set_add(&closure, trans->to);
            }
            trans = trans->next;
        }
    }
    //trie pour uniformiser
    set_sort(&closure);
    return closure;
}