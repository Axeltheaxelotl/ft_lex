#ifndef ERROR_H
# define ERROR_H
/*
genere lex.yy.c
*/
void	fatal_error(const char *msg);

void	syntax_error(
			const char *file,
			int line,
			const char *msg
			);

#endif