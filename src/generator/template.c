#include "ft_lex.h"

/*
    * Génère un template basique pour lire et stocker les caractères sans perdre de mémoire.        
    * Un buffer yy_pushback permet le "unget" indispensable pour le fallback d'un DFA.              
    */ 
void write_template(FILE *out)
{
    fprintf(out, "/* -- Code de lecture de l'entree (template) -- */\n");
    fprintf(out, "int yy_pushback[4096];\n");
    fprintf(out, "int yy_pb_pos = 0;\n\n");

    fprintf(out, "int yy_get_char(void) {\n");
    fprintf(out, "    if (!yyin) yyin = stdin;\n");
    fprintf(out, "    if (yy_pb_pos > 0) return yy_pushback[--yy_pb_pos];\n");
    fprintf(out, "    return fgetc(yyin);\n");
    fprintf(out, "}\n\n");

    fprintf(out, "void yy_unget_char(int c) {\n");
    fprintf(out, "    if (c != EOF && yy_pb_pos < 4096) {\n");
    fprintf(out, "        yy_pushback[yy_pb_pos++] = c;\n");
    fprintf(out, "    }\n");
    fprintf(out, "}\n\n");
}
