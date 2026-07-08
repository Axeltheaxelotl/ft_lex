#include "ft_lex.h"

//caracteres speciaux

static int is_special(char c)
{
    return (c == '|' || c == '*' || c == '+' || c == '?' || c == '(' || c == ')');
}


//cree un token

static t_token make_token(t_token_type type, char value)
{
    t_token tok;

    tok.type = type;
    tok.value = value;
    return (tok);
}


//next token

t_token regex_next_token(t_regex_lexer *lx)
{
    char c;
    while (lx->input[lx->pos]) //on lit tout le regex
    {
        c = lx->input[lx->pos++];

        if (c == '"') {
            lx->in_quotes = !lx->in_quotes;
            continue;
        }

        if (c == '\\') {
            if (lx->input[lx->pos]) {
                c = lx->input[lx->pos++];
                return make_token(TOK_CHAR, regex_unescape_char(c));
            } else {
                syntax_error("regex", lx->pos, "escape incomplet");
                return make_token(TOK_END, 0);
            }
        }

        if (lx->in_quotes) {
            return make_token(TOK_CHAR, c);
        }

        //operateurs
        if (c == '|')
            return make_token(TOK_OR, c);
        if (c == '*')
            return make_token(TOK_STAR, c);
        if (c == '+')
            return make_token(TOK_PLUS, c);
        if (c == '?')
            return make_token(TOK_OPTIONAL, c);

        //parenthese
        if (c == '(')
            return make_token(TOK_OPEN, c);
        if (c == ')')
            return make_token(TOK_CLOSE, c);

        //classes de caracteres (seul [ est utile au lexer pour parser le reste dans brackets])
        if (c == '[')
            return make_token(TOK_LBRACKET, c);
        if (c == '-')
            return make_token(TOK_DASH, c);

        //char normal
        if (!is_special(c))
            return make_token(TOK_CHAR, c);

        //erreur
        syntax_error("regex", lx->pos, "invalid character");
    }
    //fin input
    return make_token(TOK_END, 0);
}