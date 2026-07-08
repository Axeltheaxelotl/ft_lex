#include "ft_lex.h"

/*
affiche une erreur de syntaxe precise (pratique pour indiquer que la regex tapee par l utilisateur du ft_lex est mal formee, par exemple)
*/
void syntax_error(const char *file, int line, const char *msg)
{
    fprintf(stderr, "%s:%d syntaxe error: %s\n", file, line, msg);
}