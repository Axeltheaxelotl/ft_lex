#include "ft_lex.h"

//traduit les sequences d echappement classqiues
char regex_unescape_char(char c)
{
    if (c == 'n')
        return '\n';
    if (c == 't')
        return '\t';
    if (c == 'r')
        return '\r';
    return c; //retourne le caracter litterale (\* -> *, \\ -> \)
}