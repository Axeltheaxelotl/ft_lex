%%
[0-9]+ print(f"NUMBER: {self.yytext}")
"+" print(f"OPERATOR: {self.yytext}")
"-" print(f"OPERATOR: {self.yytext}")
"*" print(f"OPERATOR: {self.yytext}")
"/" print(f"OPERATOR: {self.yytext}")
"(" print("OPEN PARENTHESIS")
")" print("CLOSED PARENTHESIS")
"\n" print("NEWLINE")
[ \t] pass
. print(f"Invalid character: {self.yytext}")
