#ifndef LEXER_FILE_H
#define LEXER_FILE_H

#include "ft_lex.h"

#define MAX_RULES 256

typedef struct s_lex_rule
{
    char *regex;
    char *action;
} t_lex_rule;

//represente une regle: regex brute ex: [0-9]+ son action C return NUM;
typedef struct s_lex_file
{
    char *header; //section 1: code C entre %{ et %}
    t_lex_rule rules[MAX_RULES]; //section 2: tableau de regles
    int rule_count; //nombre de regle extraites
    char *footer; //section 3: code utilisateur apres le second %%
}t_lex_file;

//initialisation et liberation de la struct
void lex_file_init(t_lex_file *lf);
void lex_file_free(t_lex_file *lf);

//ajout de code aux sections textuelle (Header / Footer)
void lex_file_append_header(t_lex_file *lf, const char *line);
void lex_file_append_footer(t_lex_file *lf, const char *line);

//gestion des regles
bool lex_file_add_rule(t_lex_file *lf, const char *regex, const char *action);

//decoupage d une regle et gestion des accolades
bool split_rule_line(const char *line, char **regex_out, char **action_out);
int count_braces(const char *str, int current_depth);

//parsing d un fichier .l
bool lex_file_parse(t_lex_file *lf, const char *filepath);

#endif

