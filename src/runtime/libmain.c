#include <stdlib.h>
extern int yylex(void);

int main(void) {
    while (yylex() != 0);
    exit(0);
}
