#ifndef GENERATOR_H
#define GENERATOR_H

#include "ft_lex.h"

int	generate_c_file(
		t_dfa *dfa,
		const char *filename
		);

#endif