#include "ft_lex.h"
#include "bonus/bonus_polyglotism.h"

int main(int argc, char **argv)
{
    t_lex_file lf;
    t_dfa *dfas[MAX_RULES];
    int id_counter;

    bool use_python = false;
    char *input_file = NULL;

    //1. ije verifie que j ai bien recu le fichier en argument
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "--python") == 0)
            use_python = true;
        else
            input_file = argv[i];
    }

    if (!input_file)
    {
        fprintf(stderr, "Usage: %s [--python] <file.l>\n", argv[0]);
        return 1;
    }

    //2 initialistion et lecture (parsing) du fichier .l
    lex_file_init(&lf);
    if (!lex_file_parse(&lf, input_file))
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
    if (use_python)
    {
#ifdef BONUS
        if (!generate_python_file(&lf, dfas, "lex.yy.py"))
        {
            fatal_error("Echec lors de la generation du fichier Python");
        }
#else
        fatal_error("Le support Python necessite de compiler avec 'make bonus'");
#endif
    }
    else
    {
        if (!generate_c_file(&lf, dfas, "lex.yy.c"))
        {
            fatal_error("Echec lors de la generation du fichier");
        }
    }

    lex_file_free(&lf);
    return 0;
}