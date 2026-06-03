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

static t_ast *parse_expr(t_parser *p);
static t_ast *parse_term(t_parser *p);
static t_ast *parse_factor(t_parser *p);
static t_ast *parse_primary(t_parser *p);
static t_ast *parse_bracket(t_parser *p);


//fait avancer le lexer d un token
static void advance(t_pasrer *p)
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
    advance(p); // Consomme '['                                                                  
                                                                                                
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
        advance(p); //consomme le
    }
}




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