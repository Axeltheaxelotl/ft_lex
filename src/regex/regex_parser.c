#include "ft_lex.h"

static t_ast *parse_expr(t_parser *p);
static t_ast *parse_term(t_parser *p);
static t_ast *parse_factor(t_parser *p);
static t_ast *parse_primary(t_parser *p);
static t_ast *parse_bracket(t_parser *p);

//fait avancer le lexer d un token
static void advance(t_parser *p)
{
    p->current = regex_next_token(&(p->lexer));
}

//parse expr ->term ('|' term)*
static t_ast *parse_expr(t_parser *p)
{
    t_ast *left = parse_term(p);
    if (!left)
        return NULL;
    while (p->current.type == TOK_OR)
    {
        advance(p); // saute le '|'
        t_ast *right = parse_term(p);
        if (!right)
            return NULL;
        left = ast_or(left, right);
    }
    return left;
}

//parse term  -> factor factor* (concatenation implicite)
static t_ast *parse_term(t_parser *p)
{
    t_ast *left = parse_factor(p);
    if (!left)
        return NULL;
    //concatenation implicite si le token suivant peut debuter un nouveau facteur
    while (p->current.type == TOK_CHAR || p->current.type == TOK_OPEN || p->current.type == TOK_LBRACKET)
    {
        t_ast *right = parse_factor(p);
        if (!right)
            return NULL;
        left = ast_concat(left, right);
    }
    return left;
}

static t_ast *parse_factor(t_parser *p)
{
    t_ast *node = parse_primary(p);
    if (!node)
        return NULL;
    while (p->current.type == TOK_STAR || p->current.type == TOK_PLUS || p->current.type == TOK_OPTIONAL)
    {
        if (p->current.type == TOK_STAR)
        {
            advance(p);
            node = ast_star(node);
        }
        else if (p->current.type == TOK_PLUS)
        {
            advance(p);
            node = ast_plus(node);
        }
        else if (p->current.type == TOK_OPTIONAL)
        {
            advance(p);
            node = ast_question(node);
        }
    }
    return node;
}

static t_ast *parse_bracket(t_parser *p)
{
    t_ast *bracket_ast = NULL;

    while (p->lexer.input[p->lexer.pos] != ']' && p->lexer.input[p->lexer.pos] != '\0')
    {
        char start_c = p->lexer.input[p->lexer.pos++];

        if (start_c == '\\')
        {
            if (p->lexer.input[p->lexer.pos] == '\0')
            {
                syntax_error("regex", p->lexer.pos, "escape incomplet dans les crochets");
                return NULL;
            }
            start_c = regex_unescape_char(p->lexer.input[p->lexer.pos++]);
        }

        // Détection de plage (ex: a-z)
        if (p->lexer.input[p->lexer.pos] == '-')
        {
            p->lexer.pos++; // Consomme '-'
            if (p->lexer.input[p->lexer.pos] == ']' || p->lexer.input[p->lexer.pos] == '\0')
            {
                // Le '-' est à la fin, c'est un caractère littéral
                t_ast *char_ast = ast_char(start_c);
                bracket_ast = bracket_ast ? ast_or(bracket_ast, char_ast) : char_ast;

                t_ast *dash_ast = ast_char('-');
                bracket_ast = ast_or(bracket_ast, dash_ast);
                break;
            }
            char end_c = p->lexer.input[p->lexer.pos++];
            if (end_c == '\\')
            {
                if (p->lexer.input[p->lexer.pos] == '\0')
                {
                    syntax_error("regex", p->lexer.pos, "escape incomplet dans les crochets");
                    return NULL;
                }
                end_c = regex_unescape_char(p->lexer.input[p->lexer.pos++]);
            }

            if (start_c > end_c)
            {
                syntax_error("regex", p->lexer.pos, "plage de caracteres invalide");
                return NULL;
            }

            // Ajoute tous les caractères de la plage dans l'union AST
            for (char rc = start_c; rc <= end_c; rc++)
            {
                t_ast *char_ast = ast_char(rc);
                bracket_ast = bracket_ast ? ast_or(bracket_ast, char_ast) : char_ast;
            }
        }
        else
        {
            t_ast *char_ast = ast_char(start_c);
            bracket_ast = bracket_ast ? ast_or(bracket_ast, char_ast) : char_ast;
        }
    }

    if (p->lexer.input[p->lexer.pos] != ']')
    {
        syntax_error("regex", p->lexer.pos, "crochet non ferme");
        return NULL;
    }
    p->lexer.pos++; // Consomme ']'
    advance(p);     // Resynchronise le lexer de jetons

    if (!bracket_ast)
    {
        syntax_error("regex", p->lexer.pos, "classe de caracteres vide");
        return NULL;
    }
    return bracket_ast;
}

//parse primary -> CHAR | '(' expr ')' | '[' bracket_expr ']'
static t_ast *parse_primary(t_parser *p)
{
    if (p->current.type == TOK_CHAR)
    {
        char val = p->current.value;
        advance(p);
        return ast_char(val);
    }
    else if(p->current.type == TOK_OPEN)
    {
        advance(p); //consomme le '('
        t_ast *node = parse_expr(p);
        if (!node)
            return NULL;
        if (p->current.type != TOK_CLOSE)
        {
            syntax_error("regex", p->lexer.pos, "missing closing parenthesis");
            return NULL;
        }
        advance(p); // consomme le ')'
        return node;
    }
    else if (p->current.type == TOK_LBRACKET)
    {
        return parse_bracket(p);
    }
    syntax_error("regex", p->lexer.pos, "unexpected token");
    return NULL;
}

//fonction d entree
t_ast *regex_parse(char *regex)
{
    t_parser p;
    t_ast *root;

    p.lexer.input = regex;
    p.lexer.pos = 0;
    p.lexer.in_quotes = false;
    advance(&p);

    root = parse_expr(&p);

    if (!root)
        return NULL;

    if (p.current.type != TOK_END)
    {
        syntax_error("regex", p.lexer.pos, "caractere pas attendue a la fin de l expression");
        return NULL;
    }

    return root;
}