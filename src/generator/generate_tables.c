#include "ft_lex.h"                                                                              
                                                                                                    
/*                                                                                               
traduit les strucs t_dfa generees par le programme en tableaux statiques C                       
ces tableaux a deux dimensions permettent  a 'yylex()' de savoir tres rapidement                 
vers quel etat avancer en lisant un caracters ASCII donne                                        
*/                                                                                               
void generate_tables(FILE *out, t_dfa **dfas, int rule_count)                                    
{                                                                                                
    int i;                                                                                       
    int s;                                                                                       
    int c;                                                                                       
                                                                                                    
    fprintf(out, "/* -- Tables de transition (DFA) pour chaque regle -- */\n");                  
    fprintf(out, "#define RULE_COUNT %d\n", rule_count);                                         
                                                                                                    
    fprintf(out, "int yy_transition[%d][%d][256] = {\n", rule_count > 0 ? rule_count : 1,        
DFA_MAX_STATES);                                                                                   
    i = 0;                                                                                       
    while (i < rule_count)                                                                       
    {                                                                                            
        fprintf(out, "    {\n");                                                                 
        s = 0;                                                                                   
        while (s < dfas[i]->count)                                                               
        {                                                                                        
            fprintf(out, "        {");                                                           
            c = 0;                                                                               
            while (c < DFA_ALPHABET)                                                             
            {                                                                                    
                fprintf(out, "%d", dfas[i]->states[s].transition[c]);                            
                if (c < DFA_ALPHABET - 1)                                                        
                    fprintf(out, ", ");                                                          
                c++;                                                                             
            }                                                                                    
            fprintf(out, "}");                                                                   
            if (s < dfas[i]->count - 1)                                                          
                fprintf(out, ",");                                                               
            fprintf(out, "\n");                                                                  
            s++;                                                                                 
        }                                                                                        
        fprintf(out, "    }");                                                                   
        if (i < rule_count - 1)                                                                  
            fprintf(out, ",");                                                                   
        fprintf(out, "\n");                                                                      
        i++;                                                                                     
    }                                                                                            
    if (rule_count == 0)                                                                         
        fprintf(out, "    {0}\n");                                                               
    fprintf(out, "};\n\n");                                                                      
                                                                                                    
    fprintf(out, "int yy_accepting[%d][%d] = {\n", rule_count > 0 ? rule_count : 1,              
DFA_MAX_STATES);                                                                                   
    i = 0;                                                                                       
    while (i < rule_count)                                                                       
    {                                                                                            
        fprintf(out, "    {");                                                                   
        s = 0;                                                                                   
        while (s < dfas[i]->count)                                                               
        {                                                                                        
            fprintf(out, "%d", dfas[i]->states[s].accepting ? 1 : 0);                            
            if (s < dfas[i]->count - 1)                                                          
                fprintf(out, ", ");                                                              
            s++;                                                                                 
        }                                                                                        
        fprintf(out, "}");                                                                       
        if (i < rule_count - 1)                                                                  
            fprintf(out, ",");                                                                   
        fprintf(out, "\n");                                                                      
        i++;                                                                                     
    }                                                                                            
    if (rule_count == 0)                                                                         
        fprintf(out, "    {0}\n");                                                               
    fprintf(out, "};\n\n");                                                                      
}           