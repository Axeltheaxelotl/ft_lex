#include "lexer_file.h"

void lex_file_init(t_lex_file *lf)
{
    if (!lf)
        return;
    lf->header = NULL;
    lf->footer = NULL;
    lf->rule_count = 0;
    memset(lf->rules, 0, sizeof(lf->rules));
}

void lex_file_free(t_lex_file *lf)
{
    if (!lf)
        return;
    if (lf->header)
    {
        free(lf->header);
        lf->header = NULL;
    }
    if (lf->footer)
    {
        free(lf->footer);
        lf->footer = NULL;
    }
    for (int i = 0; i < lf->rule_count; i++)
    {
        if (lf->rules[i].regex)
        {
            free(lf->rules[i].regex);
            lf->rules[i].regex = NULL;
        }
        if (lf->rules[i].action)
        {
            free(lf->rules[i].action);
            lf->rules[i].action = NULL;
        }
    }
    lf->rule_count = 0;
}

void lex_file_append_header(t_lex_file *lf, const char *line)
{
    if (!lf || !line)
        return;
    size_t len_existing = lf->header ? strlen(lf->header) : 0;
    size_t len_line = strlen(line);
    char *new_header = malloc(len_existing + len_line + 2);
    if (!new_header)
        return;
    if (lf->header)
    {
        strcpy(new_header, lf->header);
        free(lf->header);
    }
    else
    {
        new_header[0] = '\0';
    }
    strcat(new_header, line);
    strcat(new_header, "\n");
    lf->header = new_header;
}

void lex_file_append_footer(t_lex_file *lf, const char *line)
{
    if (!lf || !line)
        return;
    size_t len_existing = lf->footer ? strlen(lf->footer) : 0;
    size_t len_line = strlen(line);
    char *new_footer = malloc(len_existing + len_line + 2);
    if (!new_footer)
        return;
    if (lf->footer)
    {
        strcpy(new_footer, lf->footer);
        free(lf->footer);
    }
    else
    {
        new_footer[0] = '\0';
    }
    strcat(new_footer, line);
    strcat(new_footer, "\n");
    lf->footer = new_footer;
}
