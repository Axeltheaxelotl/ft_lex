#include "ft_lex.h"

/*
la fonction ecrit le squelette de base en haut du fichier genere
j y place les bibliotheque standarts et on declare les variables goblales
classiques de tout bon lexer (yytext, yyleng, yyin)
*/
void generate_headers(FILE *out)
{
    //je met un petit commentaire pour prevenir que c est un code autogenere
    fprintf(out, "/* -- Fichier genere automatiquement pat ft_lex -- */\n\n");

    //bibliotheques basiques
    fprintf(out, "#include <stdio.h>\n");
    fprintf(out, "#include <stdlib.h>\n");
    fprintf(out, "#include <string.h>\n");
    fprintf(out, "#include <stdbool.h>\n\n");

    // Variables globales classiques que l'utilisateur pourra manipuler dans ses actions         
    fprintf(out, "/* Variables globales standard */\n");                                         
    fprintf(out, "char *yytext = NULL;\n"); // Pointeur vers le token actuel                     
    fprintf(out, "int yyleng = 0;\n");      // Longueur du token                                 
    fprintf(out, "FILE *yyin = NULL;\n\n"); // Fichier source à analyser 
}