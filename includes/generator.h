#ifndef GENERATOR_H
#define GENERATOR_H

#include "ft_lex.h"

/*
le generator prend :
	- le t_lex_file (header, regles, footer du fichier  .l)
	- un tableau de t_dfa (un dfa par regle regex)
et genere le fichier lex.yy.c
*/

//fonction principale: genere le fichier lex.yy.c complet
int generate_c_file(t_lex_file *lf, t_dfa **dfas, const char *filename, bool use_compression);

//sous-fonctions d'ecriture (chacun ecrit une partie du lex.yy.c)
void generate_headers(FILE *out);
void generate_tables(FILE *out, t_dfa **dfas, int count, bool use_compression);
void generate_actions(FILE *out, t_lex_file *lf);
void write_template(FILE *out);
void generate_yylex(FILE *out, bool use_compression);

#endif