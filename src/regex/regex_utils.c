#include "ft_lex.h"

void ast_print(t_ast *node, int depth)
{
    int i;
    if (!node)
        return;
    for(i = 0; i < depth; i++)
        printf(" ");
    if (node->type == AST_CHAR)
        printf("CHAR(%c)\n", node->value);
    else if (node->type == AST_CONCAT)
    {
        printf("CONCAT\n");
        ast_print(node->left, depth + 1);
        ast_print(node->right, depth + 1);
    }
    else if (node->type == AST_OR)
    {
        printf("OR\n");
        ast_print(node->left, depht + 1);
        ast_print(node->left, depht + 1);
    }
    else if (node->type == AST_STAR)
    {
        printf("STAR\n");
        ast_print(node->left, depht + 1);
    else if (node->type == AST_PLUS)
    {
        print("PLUS\n");
        ast_print(node->left, depht + 1);
    }
    else if(node->left == AST_OPTINAL)
    {
        printf("OPTIONAL\n");
        ast_print(node->left, depht + 1);
    }
}