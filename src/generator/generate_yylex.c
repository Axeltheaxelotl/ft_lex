#include "ft_lex.h"                                                                              
                                                                                                    
/*                                                                                               
    * Génère la fonction principale `int yylex(void)` qui simule le(s) DFA.                         
    * Elle lit les caractères, retient la correspondance la plus longue,                            
    * gère la remise des caractères dans le buffer (fallback) si aucune transition n'est trouvée,   
    * et exécute les actions correspondantes.                                                       
    */                                                                                              
void generate_yylex(FILE *out)                                                                   
{                                                                                                
    fprintf(out, "/* -- Fonction principale d'analyse lexicale -- */\n");                        
    fprintf(out, "int yylex(void) {\n");                                                         
    fprintf(out, "    int c;\n");                                                                
    fprintf(out, "    int states[RULE_COUNT > 0 ? RULE_COUNT : 1];\n");                          
    fprintf(out, "    int i;\n");                                                                
    fprintf(out, "    int last_accepting_rule = -1;\n");                                         
    fprintf(out, "    int last_accepting_len = 0;\n");                                           
    fprintf(out, "    char token_buf[4096];\n");                                                 
    fprintf(out, "    int token_len = 0;\n\n");                                                  
    fprintf(out, "    while (1) {\n");                                                           
    fprintf(out, "        token_len = 0;\n");                                                    
    fprintf(out, "        last_accepting_rule = -1;\n");                                         
    fprintf(out, "        last_accepting_len = 0;\n");                                           
    fprintf(out, "        for (i = 0; i < RULE_COUNT; i++) states[i] = 0;\n");                   
    fprintf(out, "        while ((c = yy_get_char()) != EOF) {\n");                              
    fprintf(out, "            if (token_len < 4095) token_buf[token_len++] = c;\n");             
    fprintf(out, "            else break;\n");                                                   
    fprintf(out, "            int any_alive = 0;\n");                                            
    fprintf(out, "            for (i = 0; i < RULE_COUNT; i++) {\n");                            
    fprintf(out, "                if (states[i] != -1) {\n");                                    
    fprintf(out, "                    states[i] = yy_transition[i][states[i]][c];\n");           
    fprintf(out, "                    if (states[i] != -1) {\n");                                
    fprintf(out, "                        any_alive = 1;\n");                                    
    fprintf(out, "                        if (yy_accepting[i][states[i]]) {\n");                 
    fprintf(out, "                            if (token_len > last_accepting_len) {\n");         
    fprintf(out, "                                last_accepting_rule = i;\n");
    fprintf(out, "                                last_accepting_len = token_len;\n");           
    fprintf(out, "                            } else if (token_len == last_accepting_len && "
                 "(last_accepting_rule == -1 || i < last_accepting_rule)) {\n");
    fprintf(out, "                                last_accepting_rule = i;\n");
    fprintf(out, "                            }\n");
    fprintf(out, "                        }\n");
    fprintf(out, "                    }\n");
    fprintf(out, "                }\n");
    fprintf(out, "            }\n");
    fprintf(out, "            if (!any_alive) {\n");
    fprintf(out, "                yy_unget_char(c);\n");
    fprintf(out, "                token_len--;\n");
    fprintf(out, "                break;\n");
    fprintf(out, "            }\n");
    fprintf(out, "        }\n");

    fprintf(out, "        if (last_accepting_rule != -1) {\n");
    fprintf(out, "            while (token_len > last_accepting_len) {\n");
    fprintf(out, "                token_len--;\n");
    fprintf(out, "                yy_unget_char(token_buf[token_len]);\n");
    fprintf(out, "            }\n");
    fprintf(out, "            token_buf[token_len] = '\\0';\n");
    fprintf(out, "            if (yytext) free(yytext);\n");
    fprintf(out, "            yytext = strdup(token_buf);\n");
    fprintf(out, "            yyleng = token_len;\n");
    fprintf(out, "            \n");
    fprintf(out, "            int returned;\n");
    fprintf(out, "            int val = yy_do_action(last_accepting_rule, &returned);\n");       
    fprintf(out, "            if (returned) return val;\n");
    fprintf(out, "            continue;\n");
    fprintf(out, "        }\n");

    fprintf(out, "        if (c == EOF && token_len == 0) return 0;\n");
    fprintf(out, "        if (token_len > 0) {\n");
    fprintf(out, "            while (token_len > 1) {\n");
    fprintf(out, "                token_len--;\n");
    fprintf(out, "                yy_unget_char(token_buf[token_len]);\n");
    fprintf(out, "            }\n");
    fprintf(out, "            printf(\"%%c\", token_buf[0]);\n");
    fprintf(out, "        }\n");
    fprintf(out, "    }\n");
    fprintf(out, "    return 0;\n");
    fprintf(out, "}\n");
}
