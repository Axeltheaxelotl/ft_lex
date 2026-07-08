#include "ft_lex.h"

/*
affiche un msg d erreur generique puis quitte le programme avec un code d erreur
*/
void fatal_error(const char *msg)
{
    fprintf(stderr, "ft_lex fatal error: %s\n", msg);
    exit(EXIT_FAILURE);
}