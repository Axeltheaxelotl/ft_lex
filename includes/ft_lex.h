#ifndef FT_LEX_H
#define FT_LEX_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>

typedef struct s_lex_file t_lex_file;
typedef struct s_dfa t_dfa;
typedef struct s_nfa t_nfa;
typedef struct s_ast t_ast;
typedef struct s_nfa_state t_nfa_state;
typedef struct s_nfa_transition t_nfa_transition;
typedef struct s_nfa_state_set t_nfa_state_set;
typedef struct s_token t_token;
typedef struct s_regex_lexer t_regex_lexer;

#include "tokens.h"
#include "lexer_file.h"
#include "ast.h"
#include "nfa.h"
#include "dfa.h"
#include "regex.h"
#include "parser.h"
#include "generator.h"
#include "error.h"


#endif