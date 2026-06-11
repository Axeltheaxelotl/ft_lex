#include "ft_lex.h"


/*
fonction pour move le calcul de transitions nfa physiques
*/


/*
calcule l ensemble des etats nfa atteignables depuis un ensemble donne
en consommant obligatoirement le caractere "symbole"
cette fonction filtre et ne suit qui les transitions de type TRANS_CHAR
*/
t_nfa_state_set move(t_nfa_state_set *set, char symbol)
{
    t_nfa_state_set result;

    set_init(&result);
    if (!set)
        return result;

        //parcourir chaque etat nfa contenu dans le set
        for(int i = 0; i < set->count; i++)
        {
            t_nfa_state *state = set->states[i];
            t_nfa_transition *trans = state->transition;

            //examiner toutes les transitions sortantes
            while(trans)
            {
                //si c est une transition sur caractere correspondant au symbole recherche
                if (trans->type == TRANS_CHAR && trans->symbol == symbol)
                {
                    //j ajoute l etat destination dans le set resultat
                    set_add(&result, trans->to);
                }
                trans = trans->next;
            }
        }
        //trie pour rendre l essemble canonique
        set_sort(&result);
        return result;
}