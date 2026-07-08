#include "ft_lex.h"

//retoune le nom du type de noeud ast en string
static const char *ast_type_str(t_ast_type type)
{
    if (type == AST_CHAR)
        return ("CHAR");
    if (type == AST_CONCAT)
        return ("CONCAT");
    if (type ==AST_OR)
        return ("OR");
    if (type == AST_STAR)
        return ("STAR");
    if (type == AST_PLUS)
        return ("PLUS");
    if (type == AST_OPTIONAL)
        return ("OPTINAL");
    return ("UNKNOWN");
}


//affiche l arbre ast avec indentation pour la profondeur
void ast_print(t_ast *node, int depth)
{
    int i;
    if (!node)
        return;
    i = 0;
    while (i < depth)
    {
        printf (" ");
        i++;
    }
    if (node->type == AST_CHAR)
        printf("%s('%c')\n", ast_type_str(node->type), node->value);
    else
        printf("%s\n", ast_type_str(node->type));
    ast_print(node->left, depth + 1);
    ast_print(node->right, depth + 1);
}




/*
ex de sortie pour (a|b)*c :

    CONCAT
      STAR
        OR
          CHAR('a')
          CHAR('b')
      CHAR('c')
*/