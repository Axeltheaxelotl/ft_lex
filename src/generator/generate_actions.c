#include "ft_lex.h"                                                                              
                                                                                                    
/*                                                                                               
    * Génère la fonction d'actions qui encapsule le code utilisateur (C) pour chaque règle.         
    * L'astuce du `returned` permet de capturer un `return NUM;` de l'utilisateur                   
    * et de le remonter jusqu'à la fonction yylex().                                                
    */                                                                                              
void generate_actions(FILE *out, t_lex_file *lf)                                                 
{                                                                                                
    int i;                                                                                       
                                                                                                    
    fprintf(out, "/* -- Actions associees a chaque regle -- */\n");                              
    fprintf(out, "int yy_do_action(int rule_index, int *returned) {\n");                         
    fprintf(out, "    *returned = 1;\n");                                                        
    fprintf(out, "    switch (rule_index) {\n");                                                 
                                                                                                    
    i = 0;                                                                                       
    while (i < lf->rule_count)                                                                   
    {                                                                                            
        fprintf(out, "        case %d:\n", i);                                                   
        fprintf(out, "            do {\n");                                                      
        if (lf->rules[i].action)                                                                 
            fprintf(out, "                %s\n", lf->rules[i].action);                           
        fprintf(out, "            } while(0);\n");                                               
        fprintf(out, "            *returned = 0;\n");                                            
        fprintf(out, "            break;\n");                                                    
        i++;                                                                                     
    }                                                                                            
                                                                                                    
    fprintf(out, "        default:\n");                                                          
    fprintf(out, "            *returned = 0;\n");                                                
    fprintf(out, "            break;\n");                                                        
    fprintf(out, "    }\n");                                                                     
    fprintf(out, "    return 0;\n");                                                             
    fprintf(out, "}\n\n");                                                                       
}        