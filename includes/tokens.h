#ifndef TOKENS_H
#define TOKENS_H

#include "ft_lex.h"

//tokens utiliser par le regex
// ex :
// (a|b)*c
// 
// OPEN
// CHAR (a)
// OR
// CHAR(b)
// CLOSE
// STAR
// CHAR (c)
// EOF


typedef enum e_token_type
{
    TOK_CHAR,

    TOK_OR,
    TOK_STAR,
    TOK_PLUS,
    TOK_OPTIONAL,

    TOK_OPEN,
    TOK_CLOSE,

    TOK_LBRACKET,
    TOK_RBRACKET,

    TOK_DASH,
    
    TOK_END,
} t_token_type;

typedef struct s_token
{
    t_token_type type;
    char value;
} t_token;

#endif