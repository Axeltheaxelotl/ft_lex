#include "ft_lex.h"

/*
fonction principale du generateur
elle fait le fichier c lex.yy.c
elle appelle successivement les fonctions qui vont ecrire les difs
partie du fichier final : headers, tables d etats, actions, etc ...
*/
int generate_c_file(t_lex_file *lf, t_dfa **dfas, const char *filename)
{
    FILE *out;

    //j ouvre le fichier de sortie en mode ecriture
    out = fopen(filename, "w");
    if (!out)
        return 0;

    generate_headers(out); 
    
    if (lf->header)
        fprintf(out, "%s\n", lf->header);

    //ecrit les tableau a 2 dimentions pour chaque automate dfa
    generate_tables(out, dfas, lf->rule_count);

    //ecrit la fonction contenant le switch pour les actions C de chaque regle
    generate_actions(out, lf);

    //inject le code template (buffer, fonctions de lecture de caracters)
    write_template(out);

    //ecrit la fonction  principale generee : int yylex()
    generate_yylex(out);

    //ecrit la section utilisateur final apres le dernier %% (le footer)
    if (lf->footer)
        fprintf(out, "%s\n", lf->footer);

    //fermeture propre du fichier
    fclose(out);
    return 1;
    
}