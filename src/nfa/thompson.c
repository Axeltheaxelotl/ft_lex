//contient le routeur principal de conversion de l ast en nfa, la gestion des caracteres de base ainsi que la fonction de debug print_nfa
#include "ft_lex.h"

//construit le nfa de base pour un seul caracters
t_nfa  *thompson_char(char c, int *id_counter)
{
    t_nfa *nfa;
    nfa = nfa_new();
    if (!nfa)
        return NULL;
    nfa->start = nfa_create_state(id_counter);
    nfa->end = nfa_create_state(id_counter);
    if (!nfa->start || !nfa->end)
    {
        free(nfa->start);
        free(nfa->end);
        free(nfa);
        return NULL;
    }
    nfa_add_char_transition(nfa->start, nfa->end, c);
    return nfa;
}

//convertit recursivement un ast en fragements de nfa
t_nfa *thompson_build(t_ast *ast, int *id_counter)
{
    if (!ast)
        return NULL;
    switch (ast->type)
    {
        case AST_CHAR:
            return thompson_char(ast->value, id_counter);
        case AST_CONCAT:
            return thompson_concat(ast, id_counter);
        case AST_OR:
            return thompson_or(ast, id_counter);
        case AST_STAR:
            return thompson_star(ast, id_counter);
        case AST_PLUS:
            return thompson_plus(ast, id_counter);
        case AST_OPTIONAL :
            return thompson_optional(ast, id_counter);
        default:
            return NULL;
    }
}

//point d entree principale nfa
t_nfa *nfa_from_ast(t_ast *ast)
{
    int id_counter;
    t_nfa *nfa
    id_counter = 0;
    nfa = thompson_build(ast, &id_counter);
    if (nfa && nfa->end)
        nfa->end->accepting = true;
    return nfa;
}

//fonction utilitaire de debug pour affichier le nfa dans le terminal
static void print_state_transition(t_nfa_state *state, bool *visited)
{
    t_nfa_transition *t;
    if (!state || visited[state->id])
        return;
    visited[state->id] = true;
    t = state->transition;
    while(t)
    {
        if (t->type == TRANS_EPSILON)
            printf("Etat %d -- epsilon --> Etat %d\n", state->id, t->to->id);
        else
            printf("Etat %d -- '%c' --> Etat %d\n", state->id, t->symbol, t->to->id);
        print_state_transition(t->to, visited);
        t = t->next;
    }
}

void print_nfa(t_nfa *nfa)
{
    bool visited[10000] = [fasle];
    if (!nfa)
    {
        printf ("NFA est NULL\n");
        return;
    }
    printf ("--- NFA info (start: %d, end: %d) ---\n", nfa->start->id, nfa->end->id);
    print_state_transition(nfa->start, visited);
    printf("------------------------------------\n");
}


