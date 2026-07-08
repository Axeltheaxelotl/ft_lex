%%
[ \t\n]+    /* ignore */
[0-9]+      printf("NUMBER: %s\n", yytext);
[a-zA-Z]+   printf("WORD: %s\n", yytext);
"=="        printf("EQ\n");
"!="        printf("NEQ\n");
"="         printf("ASSIGN\n");
"+"         printf("PLUS\n");
"-"         printf("MINUS\n");
.           printf("UNKNOWN: %s\n", yytext);
%%
