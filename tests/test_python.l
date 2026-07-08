%%
[ \t\n]+    pass
[0-9]+      print(f"NUMBER: {self.yytext}")
[a-zA-Z]+   print(f"WORD: {self.yytext}")
"=="        print("EQ")
"!="        print("NEQ")
"="         print("ASSIGN")
"+"         print("PLUS")
"-"         print("MINUS")
.           print(f"UNKNOWN: {self.yytext}")
%%
