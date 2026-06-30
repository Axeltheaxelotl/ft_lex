#include "ft_lex.h"

/*
Algorithme de minimisation d'un DFA (méthode des partitions de Moore).
Réduit le nombre d'états en fusionnant les états équivalents.
*/
t_dfa *dfa_minize(t_dfa *dfa)
{
    if (!dfa)
        return NULL;
    if (dfa->count <= 1)
    {
        t_dfa *copy = malloc(sizeof(t_dfa));
        if (copy)
            memcpy(copy, dfa, sizeof(t_dfa));
        return copy;
    }

    int num_states = dfa->count;
    int partition[DFA_MAX_STATES];
    int num_partitions = 0;

    // Étape 1 : Partition initiale en 2 groupes (acceptants vs non-acceptants)
    bool has_non_accepting = false;
    bool has_accepting = false;

    for (int i = 0; i < num_states; i++)
    {
        if (dfa->states[i].accepting)
            has_accepting = true;
        else
            has_non_accepting = true;
    }

    int non_accepting_part = -1;
    int accepting_part = -1;

    if (has_non_accepting)
        non_accepting_part = num_partitions++;
    if (has_accepting)
        accepting_part = num_partitions++;

    for (int i = 0; i < num_states; i++)
    {
        if (dfa->states[i].accepting)
            partition[i] = accepting_part;
        else
            partition[i] = non_accepting_part;
    }

    // Étape 2 : Raffinement itératif (Moore)
    bool changed = true;
    while (changed)
    {
        changed = false;
        int new_partition[DFA_MAX_STATES];
        int next_part_id = 0;

        for (int i = 0; i < num_states; i++)
            new_partition[i] = -1;

        for (int i = 0; i < num_states; i++)
        {
            if (new_partition[i] != -1)
                continue;

            int current_part = next_part_id++;
            new_partition[i] = current_part;

            for (int j = i + 1; j < num_states; j++)
            {
                if (partition[j] == partition[i] && new_partition[j] == -1)
                {
                    bool equivalent = true;
                    for (int c = 0; c < DFA_ALPHABET; c++)
                    {
                        int next_i = dfa->states[i].transition[c];
                        int next_j = dfa->states[j].transition[c];

                        if (next_i == -1 && next_j == -1)
                            continue;
                        else if (next_i != -1 && next_j != -1)
                        {
                            if (partition[next_i] != partition[next_j])
                            {
                                equivalent = false;
                                break;
                            }
                        }
                        else
                        {
                            equivalent = false;
                            break;
                        }
                    }

                    if (equivalent)
                    {
                        new_partition[j] = current_part;
                    }
                }
            }
        }

        if (next_part_id > num_partitions)
        {
            num_partitions = next_part_id;
            memcpy(partition, new_partition, sizeof(int) * num_states);
            changed = true;
        }
    }

    // Étape 3 : Reconstruction du DFA minimisé
    t_dfa *min_dfa = malloc(sizeof(t_dfa));
    if (!min_dfa)
        return NULL;

    min_dfa->count = num_partitions;
    min_dfa->start = partition[dfa->start];

    // Initialiser les nouveaux états et leurs transitions
    for (int i = 0; i < num_partitions; i++)
    {
        min_dfa->states[i].id = i;
        min_dfa->states[i].accepting = false;
        for (int c = 0; c < DFA_ALPHABET; c++)
        {
            min_dfa->states[i].transition[c] = -1;
        }
    }

    // Associer les états acceptants et mettre à jour les transitions vers les nouvelles partitions
    for (int i = 0; i < num_states; i++)
    {
        int part_id = partition[i];
        if (dfa->states[i].accepting)
        {
            min_dfa->states[part_id].accepting = true;
        }

        for (int c = 0; c < DFA_ALPHABET; c++)
        {
            int next_state = dfa->states[i].transition[c];
            if (next_state != -1)
            {
                min_dfa->states[part_id].transition[c] = partition[next_state];
            }
        }
    }

    return min_dfa;
}
