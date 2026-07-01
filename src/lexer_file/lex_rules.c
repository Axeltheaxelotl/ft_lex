#include "lexer_file.h"

bool lex_file_add_rule(t_lex_file *lf, const char *regex, const char *action)
{
    if (!lf || !regex || !action)
        return false;
    if (lf->rule_count >= MAX_RULES)
    {
        fprintf(stderr, "Error: Maximum rule limit reached (%d rules).\n", MAX_RULES);
        return false;
    }
    lf->rules[lf->rule_count].regex = strdup(regex);
    lf->rules[lf->rule_count].action = strdup(action);
    if (!lf->rules[lf->rule_count].regex || !lf->rules[lf->rule_count].action)
    {
        free(lf->rules[lf->rule_count].regex);
        free(lf->rules[lf->rule_count].action);
        return false;
    }
    lf->rule_count++;
    return true;
}