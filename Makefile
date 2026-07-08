NAME = ft_lex
LIBL = libl.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes

SRCS = src/ast/ast_create.c \
       src/ast/ast_destroy.c \
       src/ast/ast_print.c \
       src/ast/ast_utils.c \
       src/debug/graphviz.c \
       src/debug/print_ast.c \
       src/debug/print_dfa.c \
       src/debug/print_nfa.c \
       src/dfa/dfa_create.c \
       src/dfa/dfa_debug.c \
       src/dfa/dfa_minimization.c \
       src/dfa/dfa_state.c \
       src/dfa/dfa_table.c \
       src/dfa/epsilon_closure.c \
       src/dfa/move.c \
       src/dfa/subset_construction.c \
       src/error/error.c \
       src/error/regex_error.c \
       src/error/syntax_error.c \
       src/generator/codegen.c \
       src/generator/generate_actions.c \
       src/generator/generate_headers.c \
       src/generator/generate_tables.c \
       src/generator/generate_yylex.c \
       src/generator/template.c \
       src/lexer_file/lex_actions.c \
       src/lexer_file/lex_file_parsing.c \
       src/lexer_file/lex_rules.c \
       src/lexer_file/lex_sections.c \
       src/main.c \
       src/nfa/nfa_create.c \
       src/nfa/nfa_epsilon.c \
       src/nfa/nfa_state.c \
       src/nfa/nfa_transition.c \
       src/nfa/thompson.c \
       src/nfa/thompson_concat.c \
       src/nfa/thompson_optional.c \
       src/nfa/thompson_or.c \
       src/nfa/thompson_plus.c \
       src/nfa/thompson_star.c \
       src/regex/regex_escape.c \
       src/regex/regex_lexer.c \
       src/regex/regex_parser.c \
       src/utils/hashmap.c \
       src/utils/queue.c \
       src/utils/set.c \
       src/utils/stack.c \
       src/utils/string_builder.c \
       src/utils/vector.c

BONUS_SRCS = src/bonus/bonus_polyglotism.c

ifdef WITH_BONUS
    SRCS += $(BONUS_SRCS)
    CFLAGS += -DBONUS
endif

OBJS_DIR = obj/
OBJS = $(SRCS:src/%.c=$(OBJS_DIR)%.o)

RUNTIME_SRCS = src/libl/yywrap.c \
               src/libl/libmain.c

RUNTIME_OBJS = $(RUNTIME_SRCS:src/%.c=$(OBJS_DIR)%.o)

all: $(NAME) $(LIBL)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(LIBL): $(RUNTIME_OBJS)
	ar rcs $(LIBL) $(RUNTIME_OBJS)

$(OBJS_DIR)%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME) $(LIBL)

re: fclean all

bonus:
	$(MAKE) WITH_BONUS=1 all

.PHONY: all clean fclean re bonus
