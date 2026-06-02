/*
le bute c que avec le lexer on a :
(
a
|
b
)
*
c

et le ast
                CONCAT
                /      \
             STAR       c
              |
              OR
             /   \
            a     b


un regex parser =
generer les priorites:
    1 (haut)        ()
    2               * + ?
    3               concat
    4 (bas)         .
*/


#include "ft_lex.h"

//HELPERS
//current char

static char peek(t_parser *p)
{
    return p->input[p->pos];
}

//consume char
static char get(t_parser *p)
{
    return p->input[p->pos++];
}

//prototypes interns
static t_ast *parse_expr(t_parser *p);
static t_ast *parse_term(t_parser *p);
static t_ast *parse_factor(t_parser *p);
static t_ast *parse_primary(t_parser *p);
/*
la grammaire importante
c la cle du parser
expr    → term ('|' term)*
term    → factor factor*
factor  → primary ('*' | '+' | '?')*
primary → CHAR | '(' expr ')'
*/


//parser expr or
static t_ast *parse_expr(t_parser *p)
{
    t_ast *left = parse_term(p);

    while (peek(p) == '|')
    {
        get(p); // skip '|'

        t_ast *right = parse_term(p);
        left = ast_or(left, right);
    }
    return left;
}


//parse term (concat)
//c la partie qui gere la concatenation implicite
/*
    ab
    abc
    a*b
    (a|b)c
    ab*c
    sont tous des concatenations

    l idee :
        - parser le premier factor
        - tant quon peut commencer un nouveau factor
        - parser le nouveau factor
        - cree un noeud CONTACT

    ex:
        abc
    je construit progressivement :
         CONCAT
         /   \
        a     b
    puis :
              CONCAT
             /      \
         CONCAT      c
         /   \
        a     b
*/

static t_ast *parse_term(t_parser *p)
{
    t_ast *left;
    t_ast *right;

    left = parse_factor(p);
    while (c && c != '|' && c != ')')   
    {
        right = parse_factor(p);
        left = ast_concat(left, right);
        c = peek(p);
    }
    return left;
}
// pourquoi s arreter sur | et ) parceque quand parse_term rencontre | il doit laisser
// parse_expr gerer l alternative et pour ) il doit rendre la main a parse_primary





//factor -> primary ('*' | '+' | '?')*
static t_ast *parse_factor(t_parser *p)
{
    t_ast *node;
    node = parse_primary(p);
    while (1)
    {
        if (peek(p) == '*')
        {
            get(p);
            node = ast_star(node);
        }
        else if (peek(p) == '+')
        {
            get(p);
            node = ast_star(node);
        }
        else if (peek(p) == '+')
        {
            get(p);
            node = ast_plus(node);
        }
        else if(peek(p) == '?')
        {
            get(p);
            node = ast_question(node);
        }
        else
            break;
    }
    return node;
}


//primary -> CHAR | '(' expr ')'
static t_ast *parse_primary(t_parser *p)
{
    t_ast *node
    char c;

    if (peek(p) != '(')
    {
        get(p);
        node = parse_expr(p);
        if (peek(p) != ')')
        {
            syntax_error("regex", p->pos, "missing closing parenthesis");
            return NULL
        }
        get(p);
        return node;
    }
    c = peek(p);
    if (c == '\0')
    {
        syntax_error("regex", p->pos, "unexpected end of regex");
        return NULL;
    }
    if (c == '|' || c == ')' || c == '*' || c == '+' || c == '?')
    {
        syntax_error("regex", p->pos, "unexpected operator");
        return NULL
    }
    get(p);
    return (ast_char(c));
}




//fonction d entree

t_ast *regex_parse(char *regex)
{
    t_parser p;
    t_ast *root;

    p.input = regex;
    p.pos = 0;

    root = parse_expr(&p);

    if (!root)
        return NULL;

    if (peek(&p) != '\0')
    {
        syntax_error("regex", p.pos, "unexpected character");
        return NULL;
    }

    return root;
}