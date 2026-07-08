#include "bonus_polyglotism.h"

void py_generate_tables(FILE *out, t_dfa **dfas, int rule_count)
{
    fprintf(out, "        # Tableau listant les automates (DFA) pour chaque regle\n");
    fprintf(out, "        self.dfas = []\n");
    for (int i = 0; i < rule_count; i++)
    {
        fprintf(out, "        dfa_%d = {\n", i);
        fprintf(out, "            'table': [\n");
        for (int s = 0; s < dfas[i]->count; s++)
        {
            fprintf(out, "                [");
            for (int c = 0; c < 256; c++)
            {
                fprintf(out, "%d, ", dfas[i]->states[s].transition[c]);
            }
            fprintf(out, "], # Etat %d\n", s);
        }
        fprintf(out, "            ],\n");
        fprintf(out, "            'accepting': [\n");
        for (int s = 0; s < dfas[i]->count; s++)
        {
            if (dfas[i]->states[s].accepting)
                fprintf(out, "                %d,\n", s);
        }
        fprintf(out, "            ]\n");
        fprintf(out, "        }\n");
        fprintf(out, "        self.dfas.append(dfa_%d)\n", i);
    }
}

void py_generate_yylex(FILE *out)
{
    fprintf(out, "\n");
    fprintf(out, "    # Le moteur principal de reconnaissance lexicale\n");
    fprintf(out, "    def yylex(self):\n");
    fprintf(out, "        import sys\n");
    fprintf(out, "        while self.pos < len(self.text):\n");
    fprintf(out, "            longest_match_len = 0\n");
    fprintf(out, "            best_rule_id = -1\n");
    fprintf(out, "            \n");
    fprintf(out, "            for rule_id, dfa in enumerate(self.dfas):\n");
    fprintf(out, "                state = 0\n");
    fprintf(out, "                match_len = 0\n");
    fprintf(out, "                last_accepting_len = 0\n");
    fprintf(out, "                i = self.pos\n");
    fprintf(out, "                \n");
    fprintf(out, "                while i < len(self.text):\n");
    fprintf(out, "                    char_code = ord(self.text[i])\n");
    fprintf(out, "                    if char_code > 255: break\n");
    fprintf(out, "                    \n");
    fprintf(out, "                    state = dfa['table'][state][char_code]\n");
    fprintf(out, "                    if state == -1: break\n");
    fprintf(out, "                    \n");
    fprintf(out, "                    match_len += 1\n");
    fprintf(out, "                    i += 1\n");
    fprintf(out, "                    if state in dfa['accepting']:\n");
    fprintf(out, "                        last_accepting_len = match_len\n");
    fprintf(out, "                \n");
    fprintf(out, "                if last_accepting_len > longest_match_len:\n");
    fprintf(out, "                    longest_match_len = last_accepting_len\n");
    fprintf(out, "                    best_rule_id = rule_id\n");
    fprintf(out, "            \n");
    fprintf(out, "            if best_rule_id != -1:\n");
    fprintf(out, "                self.yytext = self.text[self.pos : self.pos + longest_match_len]\n");
    fprintf(out, "                self.pos += longest_match_len\n");
    fprintf(out, "                self.actions[best_rule_id]()\n");
    fprintf(out, "            else:\n");
    fprintf(out, "                print(f\"Lexical error at: '{self.text[self.pos]}'\", file=sys.stderr)\n");
    fprintf(out, "                self.pos += 1\n");
}

void py_generate_actions(FILE *out, t_lex_file *lf)
{
    fprintf(out, "\n    # -- Actions générées depuis le fichier .l --\n");
    for (int i = 0; i < lf->rule_count; i++)
    {
        fprintf(out, "    def action_%d(self):\n", i);
        fprintf(out, "        %s\n", lf->rules[i].action);
    }
}

int generate_python_file(t_lex_file *lf, t_dfa **dfas, const char *filename)
{
    FILE *out = fopen(filename, "w");
    if (!out) return 0;

    if (lf->header) fprintf(out, "%s\n\n", lf->header);

    fprintf(out, "class Lexer:\n");
    fprintf(out, "    def __init__(self, text):\n");
    fprintf(out, "        self.text = text\n");
    fprintf(out, "        self.pos = 0\n");
    fprintf(out, "        self.yytext = \"\"\n");

    py_generate_tables(out, dfas, lf->rule_count);

    fprintf(out, "\n        self.actions = [\n");
    for (int i = 0; i < lf->rule_count; i++)
    {
        fprintf(out, "            self.action_%d,\n", i);
    }
    fprintf(out, "        ]\n");

    py_generate_yylex(out);
    py_generate_actions(out, lf);

    if (lf->footer)
    {
        fprintf(out, "\n# --- Code utilisateur (footer) --- \n");
        fprintf(out, "%s\n", lf->footer);
    }
    else
    {
        fprintf(out, "\n# --- Test par défaut ---\n");
        fprintf(out, "if __name__ == '__main__':\n");
        fprintf(out, "    import sys\n");
        fprintf(out, "    text = sys.stdin.read()\n");
        fprintf(out, "    lex = Lexer(text)\n");
        fprintf(out, "    lex.yylex()\n");
    }

    fclose(out);
    return 1;
}