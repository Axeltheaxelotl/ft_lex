#include "ft_lex.h"

//caracteres speciaux

static int is_special(char c)
{
    return (c == '|' || c == '*' || c == '+' || c == '?' || c == '(' || c == ')');
}


//cree un token

static t_token make_token(t_token_type type, char value, size_t pos)
{
    t_token tok;

    tok.type = type;
    tok.value = value;
    tok.pos = pos;
    return (tok);
}


//next token

t_token regex_next_token(t_regex_lexer *lx)
{
    char c;
    while (lx->input[lx->pos]) //on lit tout le regex
    {
        c = lx->input[lx->pos++];
        //operateurs
        if (c == '|')
            return make_token(TOK_OR, c, lx->pos);
        if (c == '*')
            return make_token(TOK_STAR, c, lx->pos);
        if (c == '+')
            return make_token(TOK_PLUS, c, lx->pos);
        if (c == '?')
            return make_token(TOK_QUESTION, c, lx->pos);

        //parenthese
        if (c == '(')
            return make_token(TOK_OPEN_PAREN, c, lx->pos);
        if (c == ')')
            return make_token(TOK_CLOSE_PAREN, c, lx->pos);

        //char normal
        if (!is_special(c))
            return make_token(TOK_CHAR, c, lx->pos);

        //classes de caracteres
        if (c == '[')
            return make_token(TOK_LBRACKET, c);
        if (c == ']')
            return make_token(TOK_RBRACKET, c);
        if (c == '-')
            return make_token(TOK_DASH, c);
        //erreur
        syntax_error("regex", lx->pos, "invalid character");
    }
    //fin input
    return make_token(TOK_END, 0, lx->pos);
}