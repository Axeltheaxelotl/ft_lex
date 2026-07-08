#include "ft_lex.h"

int main(int argc, char **argv)
{
    t_lex_file lf;
    t_dfa *dfas[MAX_RULES];
    int id_counter;

    //1. ije verifie que j ai bien recu le fichier en argument
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <file.l>\n", argv[0]);
        return 1;
    }

    //2 initialistion et lecture (parsing) du fichier .l
    lex_file_init(&lf);
    if (!lex_file_parse(&lf, argv[1]))
    {
        fatal_error("Echec lors du parsing du fichier lex (.l)");
    }

    //3 transformation des regex en automates (AST -> NFA -> DFA -> Min DFA)
    id_counter = 0; // pour donner un id unique aux etats nfa
    for (int i = 0; i < lf.rule_count; i++)
    {
        //a) AST
        t_ast *ast = regex_parse(lf.rules[i].regex);
        if (!ast)
           fatal_error("Echec lors de la construction de l ast de la regex");
        
        //b) NFA thompson
        t_nfa *nfa = thompson_build(ast, &id_counter);
        if(!nfa)
        {
                fatal_error("Echec lors de la construction du nfa");
        }
        if (nfa->end)
            nfa->end->accepting = true;

        //c) dfa (subset construction)
        t_dfa *dfa = subset_construction(nfa);
        if(!dfa)
            fatal_error("Echec lors de la construction du dfa");

        //d) dfa minimise (moore) pour optimiser les performances
        dfa = dfa_minize(dfa);

        //je sauvegarde le dfa final de cette regle pour le generateur
        dfas[i] = dfa;
    } 

    //4 generation du code C final lex.yy.c par le module generator
    if (!generate_c_file(&lf, dfas, "lex.yy.c"))
    {
        fatal_error("Echec lors de la generation du fichier");
    }

    lex_file_free(&lf);
    return 0;
}