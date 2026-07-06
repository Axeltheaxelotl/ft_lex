#include "ft_lex.h"

//libere tout l arbre recursivement (post-ordre)
void ast_free(t_ast *node)
{
    if (!node)
        return;
    ast_free(node->left);
    ast_free(node->right);
    free(node);
}