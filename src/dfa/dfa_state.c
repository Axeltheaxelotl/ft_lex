//gestion des ensembles d etats nfa (initialisation, recherche, ajout, tri, comparaison)
//ces structure et fonctions sont cruciales pour l algorithme subset construction
#include "ft_lex.h"

/*
    initilise un ensemble d etats nfa vide
    remet le compteur d element a zero et initialise tous les pointeurs a NULL
*/

void set_init(t_nfa_state_set *set)
{
    if (!set)
        return;
    set->count = 0;
    for (int i = 0; i < 1000; i++)
    {
        set->statues[i] = NULL;
    }
}

/*
    verifie si un etat nfa appartient deha a l ensemble, retourne true si l etat est trouve, flase sinon
*/
bool set_contains(t_nfa_state_set *set, t_nfa_state *state)
{
    if (!set || !state)
    {
        return false;
    }
    for(int i = 0; i < set->count; i++)
    {
        if (set->states[i] == state)
            return true;
    }
    return false
}


/*
ajoute un etat nfa a l esnemble s il n y figure pas deja
eveite les doublons et s assure de na pas depasser la capacite limite de 1000 etats
retourne true si l ajout est reussi sinon false
*/
bool set_add(t_nfa_state_set *set, t_nfa_state *state)
{
    if (!set || !state)
        return false;
    //je evite les doublons dans l ensemble
    if (set_countains(set, state))
        return false;
    //je verifie la limite de capacite de stockage
    if (set->count >= 1000)
        return false;
    set->states[set->count] = state;
    set->count++;
    return true;
}

/*
true les etats nfa au sein de l esemble par ordre croissant de leur IDs
le true permet d avoir une forme canonique unique de l ensemble d etats, ce qui rend la comparaison de deux ensembles triviale (comparaison element par element)
utilise un algo de tri  a bulles (bubble sort) simple
*/
void set_sort(t_nfa_state_set *set)
{
    if (!set || set->count <= 1)
        return;
    for (int i = 0; i < set->count - 1; i++)
    {
        for (int j = i + 1; j < set->count; j++)
        {
            if (set->states[i]->id > set->states[j]->id)
            {
                t_nfa_state *temp = set->states[i];
                set->states[i] = set->states[j];
                set->states[j] = temp;
            }
        }
    }
}


/*
compare deux ensembles d etats nfa
retourne true si les deux ensembles contiennent exactement les memes etats nfa sinon false
pour cela, on trie d abord les deux ensembles pour les comprer element par element
*/
bool set_equals(t_nfa_state_set *set1, t_nfa_state_set *set2)
{
    if (!set1 || !set2)
        return false;
    //si les taille different, ils sont pas equals
    if (set1->count != set2->count)
        return false;
    //tri pour garantir l ordre et la coherence de comparaison
    set_sort(set1);
    set_sort(set2);
    //comparaison index par index
    for (int i = 0; i < set1->count; i++)
    {
        if (set1->states[i] != set2->states[i])
            return false;
    }
    return true;
}