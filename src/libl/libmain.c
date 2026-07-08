extern int yylex(void);

int main(void) {
    while (yylex() != 0);
    return 0;
}
