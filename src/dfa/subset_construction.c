#include "ft_lex.h"

/*
algo de subset construction
convertit un automate NFA en un automate DFA
*/
t_dfa *subset_construction(t_nfa *nfa)
{
    if (!nfa || !nfa->start)
        return NULL;
    t_dfa *dfa = malloc(sizeof(t_dfa));
    if (!dfa)
        return NULL;
    dfa->count = 0;
    dfa->start = 0;
    //tableau pour stocker les ensembles d etats nfa correspondants a chaque etat dfa
    t_nfa_state_set *dfa_sets = malloc(sizeof(t_nfa_state_set) * DFA_MAX_STATES);
    if (!dfa_sets)
    {
        free(dfa);
        return NULL;
    }
    //initialisation des transitions de tous les etats dfa potentiels a -1
    for(int i = 0; i < DFA_MAX_STATES; i++)
    {
        dfa->states[i].id = -1;
        dfa->states[i].accepting = false;
        for (int c = 0; c < DFA_ALPHABET; c++)
        {
            dfa->states[i].transition[c] = -1;
        }
    }
    //etape 1: etat initial = epsilon-closure de l etat de depart du nfa
    t_nfa_state_set start_closure = epsilon_closure(nfa->start);
    dfa_sets[0] = start_closure;
    dfa->states[0].id = 0;
    dfa->states[0].accepting = false;
    for (int i = 0; i < start_closure.count; i++)
    {
        if (start_closure.states[i]->accepting)
        {
            dfa->states[0].accepting = true;
            break;
        }
    }
    dfa->count = 1;

    //utilisation d une file d attente (queue) simple basee sur l index de parcours
    int current = 0;
    while (current < dfa->count)
    {
        // Pour chaque symbole possible de l'alphabet ASCII (0 à 255)
        for (int c = 0; c < DFA_ALPHABET; c++)
        {
            // Calculer move(T, c)
            t_nfa_state_set move_res = move(&dfa_sets[current], (char)c);
            if (move_res.count == 0)
                continue;

            // Calculer l'epsilon-closure du résultat de move
            t_nfa_state_set closure = epsilon_closure_set(&move_res);

            // Vérifier si cet ensemble d'états NFA correspond déjà à un état DFA existant
            int found_state = -1;
            for (int i = 0; i < dfa->count; i++)
            {
                if (set_equals(&dfa_sets[i], &closure))
                {
                    found_state = i;
                    break;
                }
            }

            // Si cet ensemble n'existe pas encore, on crée un nouvel état DFA
            if (found_state == -1)
            {
                if (dfa->count >= DFA_MAX_STATES)
                {
                    continue; // Empêche le débordement du tableau d'états
                }
                found_state = dfa->count;
                dfa_sets[found_state] = closure;
                dfa->states[found_state].id = found_state;
                dfa->states[found_state].accepting = false;

                // Un état DFA est acceptant si au moins un des états NFA sous-jacents l'est
                for (int i = 0; i < closure.count; i++)
                {
                    if (closure.states[i]->accepting)
                    {
                        dfa->states[found_state].accepting = true;
                        break;
                    }
                }
                dfa->count++;
            }

            // Enregistrer la transition
            dfa->states[current].transition[c] = found_state;
        }
        current++;
    }

    free(dfa_sets);
    return dfa;
}