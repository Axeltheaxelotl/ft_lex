#include "ft_lex.h"

/*
traduit les strucs t_dfa generees par le programme en tableaux statiques C
ces tableaux a deux dimensions permettent  a 'yylex()' de savoir tres rapidement
vers quel etat avancer en lisant un caracters ASCII donne
*/
void generate_tables(FILE *out, t_dfa **dfas, int rule_count, bool use_compression)
{
    int i;
    int s;
    int c;
    
    int eq_classes[256];
    int class_rep[256];
    int num_classes = 0;

    if (use_compression)
    {
        for (c = 0; c < 256; c++)
        {
            bool found = false;
            for (int cls = 0; cls < num_classes; ++cls)
            {
                int rep = class_rep[cls];
                bool equivalent = true;
                for (int r = 0; r < rule_count; r++)
                {
                    for (int st = 0; st < dfas[r]->count; st++)
                    {
                        if (dfas[r]->states[st].transition[c] != dfas[r]->states[st].transition[rep])
                        {
                            equivalent = false;
                            break;
                        }
                    }
                    if (!equivalent) break;
                }
                if (equivalent)
                {
                    eq_classes[c] = cls;
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                class_rep[num_classes] = c;
                eq_classes[c] = num_classes;
                num_classes++;
            }
        }
    }
    else
    {
        num_classes = 256;
        for (c = 0; c < 256; c++) eq_classes[c] = c;
    }

    fprintf(out, "/* -- Tables de transition (DFA) pour chaque regle -- */\n");
    fprintf(out, "#define RULE_COUNT %d\n", rule_count);
    
    if (use_compression)
    {
        fprintf(out, "int yy_ec[256] = {");
        for (c = 0; c < 256; c++) {
            fprintf(out, "%d%s", eq_classes[c], c < 255 ? ", " : "");
        }
        fprintf(out, "};\n\n");
    }

    fprintf(out, "int yy_transition[%d][%d][%d] = {\n", rule_count > 0 ? rule_count : 1, DFA_MAX_STATES, num_classes);
    i = 0;
    while (i < rule_count)
    {
        fprintf(out, "    {\n");
        s = 0;
        while (s < dfas[i]->count)
        {
            fprintf(out, "        {");
            c = 0;
            while (c < num_classes)
            {
                int char_to_check = use_compression ? class_rep[c] : c;
                fprintf(out, "%d", dfas[i]->states[s].transition[char_to_check]);
                if (c < num_classes - 1)
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

    fprintf(out, "int yy_accepting[%d][%d] = {\n", rule_count > 0 ? rule_count : 1, DFA_MAX_STATES);
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