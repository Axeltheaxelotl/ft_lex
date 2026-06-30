#include "ft_lex.h"

/*
affiche l automate dfa pour le debogage
*/
void print_dfa(t_dfa *dfa)
{
    if (!dfa)
    {
        printf("DFA: NULL\n");
        return;
    }

    printf("=== DFA DEBUG ===\n");
    printf("Nombre d'etats : %d\n", dfa->count);
    printf("Etat initial : %d\n", dfa->start);

    for (int i = 0; i < dfa->count; i++)
    {
        printf("Etat %d %s :\n", dfa->states[i].id, dfa->states[i].accepting ? "(ACCEPTANT)" : "");
        for (int c = 0; c < DFA_ALPHABET; c++)
        {
            int next = dfa->states[i].transition[c];
            if (next != -1)
            {
                if (c >= 32 && c <= 126)
                {
                    printf("  -- '%c' --> Etat %d\n", (char)c, next);
                }
                else
                {
                    printf("  -- \\x%02X --> Etat %d\n", c, next);
                }
            }
        }
    }
    printf("=================\n");
}
