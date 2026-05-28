# ft_lex

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue?style=for-the-badge">
  <img src="https://img.shields.io/badge/Project-ft__lex-orange?style=for-the-badge">
  <img src="https://img.shields.io/badge/Theory-Automata-red?style=for-the-badge">
  <img src="https://img.shields.io/badge/Regex-DFA%20%2F%20NFA-green?style=for-the-badge">
</p>

---

# 🧠 What is ft_lex ?

`ft_lex` is a reimplementation of the historical Unix tool **lex**.

But there is an important detail:

> **Lex is NOT a lexer.**  
> Lex is a **lexer generator**.

You write rules using regex patterns, and `lex`
generates a complete lexer written in C.

---

# ⚡ What is a Lexer ?

A lexer (tokenizer) reads text character by character
and transforms it into logical units called **tokens**.

Example:

```txt
42 + 1337 * (21 - 5)
```

Becomes:

| Text | Token |
|------|------|
| 42 | NUMBER |
| + | PLUS |
| 1337 | NUMBER |
| * | MULTIPLY |
| ( | OPEN_PAREN |
| 21 | NUMBER |
| - | MINUS |
| 5 | NUMBER |
| ) | CLOSE_PAREN |

---

# 🔥 The Real Goal of ft_lex

This project is NOT just about regex.

You are building:

```txt
Regex
   ↓
NFA
   ↓
DFA
   ↓
Generated C code
```

Which means:

- Parsing `.l` files
- Parsing regex
- Building automata
- DFA optimization
- Code generation
- Producing `lex.yy.c`

---

# 🏗 Compiler Pipeline

A real compiler pipeline looks like this:

```txt
Source Code
     ↓
Lexer
     ↓
Tokens
     ↓
Parser
     ↓
AST
     ↓
Compilation
```

The lexer is the **first stage** of every compiler.

Without lexer:

- no parser
- no compiler
- no interpreter

---

# 🧩 Regex → Automata

Regex:

```regex
[0-9]+
```

Human meaning:

> one or more digits

Machine meaning:

```txt
(start)
   |
 [0-9]
   ↓
(NUMBER)
   ↓
 [0-9]
   ↺
```

A regex is actually a **state machine**.

---

# 🤖 Finite State Machines

Core idea:

```txt
current_state
+
input_character
=
next_state
```

This is the foundation of:

- compilers
- regex engines
- syntax highlighters
- shells
- parsers
- browsers

---

# 🔀 NFA vs DFA

## NFA

Non Deterministic Finite Automaton

- multiple possible paths
- epsilon transitions
- easy to build from regex

Example:

```txt
     ε
   ↙   ↘
  a     b
```

---

## DFA

Deterministic Finite Automaton

Rule:

```txt
1 state
+
1 character
=
1 next state
```

DFA are:

- fast
- deterministic
- perfect for lexers

---

# ⚡ Why DFA Lexers Are Fast

A lexer generated from a DFA is often just:

```c
state = transition[state][c];
```

That's almost the entire engine.

No recursion.  
No backtracking.  
No complex logic.

Which is why tools like:

- GCC
- Clang
- Flex
- Lex

can process millions of characters extremely fast.

---

# 📏 Longest Match Rule

The lexer always chooses:

1. the longest possible token
2. the first matching rule if equal

Example:

```lex
if          KEYWORD
[a-z]+      IDENTIFIER
```

Input:

```txt
if
```

Result:

```txt
KEYWORD
```

Because both match,
but the first rule wins.

---

# 🧠 Internal Architecture

```txt
main.c
  ↓
read .l file
  ↓
parse lex syntax
  ↓
extract regex + actions
  ↓
regex parser
  ↓
build NFA
  ↓
convert NFA → DFA
  ↓
optimize DFA
  ↓
generate C code
  ↓
write lex.yy.c
```

---

# 📚 What You Learn

`ft_lex` teaches:

- Automata Theory
- DFA / NFA
- Regex internals
- Parsing
- Compiler design
- Code generation
- Language theory

At the end:

```txt
regex ≠ magic
regex = machine
```

---

# 🌌 The Deep Idea

A programming language is ultimately:

```txt
text
 ↓
tokens
 ↓
states
 ↓
transitions
 ↓
rules
```

And yet from this:

- Linux exists
- Python exists
- browsers exist
- games exist
- compilers exist

---

# ❤️ Final Thought

`ft_lex` is not just a regex project.

It is about understanding:

> how machines read the world.

---

# 📖 References

- Compilers: Principles, Techniques, and Tools
- POSIX lex specification
- Dragon Book
- Automata Theory
- Flex & Lex documentation

---

# 👨‍💻 Author

```txt
alanty gros
```








ft_lex — Liste courte des trucs à apprendre
1. Bases des lexers

Cherche :

what is a lexer
lexical analysis
compiler pipeline
lexer vs parser

Comprendre :

texte → tokens
2. Regex

Cherche :

regular expressions theory
regex operators
regex precedence

Maîtriser :

|
*
+
?
()
[]
3. Automates finis

Cherche :

finite state automata
finite state machine

Comprendre :

état + caractère = nouvel état
4. NFA

Cherche :

NFA explained
epsilon transitions

Comprendre :

regex → NFA
5. DFA

Cherche :

DFA explained
transition table

Comprendre :

state = table[state][c];
6. Thompson Construction ⭐ IMPORTANT

Cherche :

Thompson construction
regex to NFA
7. Subset Construction ⭐ ULTRA IMPORTANT

Cherche :

subset construction
NFA to DFA
powerset construction
8. Longest Match Rule

Cherche :

maximal munch
longest match lexer
9. Structure Lex/Flex

Cherche :

flex tutorial
lex file structure
yylex explained
yytext
10. Parsing regex ⭐ GROS MORCEAU

Cherche :

recursive descent parser
regex parser
shunting yard algorithm
🏆 Les 3 trucs les plus importants
1.
Regex → NFA
2.
NFA → DFA
3.
DFA → ultra fast lexer
        



ordre de travaille

1. Comprendre le regex

Signification des regex
a
ab
`a
etc ...


1.1 Lexer regex

transformer (a|b)*c en token

ex :
input:          output:

(a|b)*c         OPEN
                CHAR (a)
                OR
                CHAR(b)
                CLOSE
                STAR
                CHAR(c)



















Get responses tailored to you

Log in to get answers based on saved chats, plus create images and upload files.
# ft_lex

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue?style=for-the-badge">
  <img src="https://img.shields.io/badge/Project-ft__lex-orange?style=for-the-badge">
  <img src="https://img.shields.io/badge/Theory-Automata-red?style=for-the-badge">
  <img src="https://img.shields.io/badge/Regex-DFA%20%2F%20NFA-green?style=for-the-badge">
</p>

---

# 🧠 What is ft_lex ?

ft_lex is a reimplementation of the historical Unix tool **lex**.

But there is an important detail:

> **Lex is NOT a lexer.**  
> Lex is a **lexer generator**.

You write rules using regex patterns, and lex
generates a complete lexer written in C.

---

# ⚡ What is a Lexer ?

A lexer (tokenizer) reads text character by character
and transforms it into logical units called **tokens**.

Example:

txt
42 + 1337 * (21 - 5)



Becomes:

| Text | Token |
|------|------|
| 42 | NUMBER |
| + | PLUS |
| 1337 | NUMBER |
| * | MULTIPLY |
| ( | OPEN_PAREN |
| 21 | NUMBER |
| - | MINUS |
| 5 | NUMBER |
| ) | CLOSE_PAREN |

---

# 🔥 The Real Goal of ft_lex

This project is NOT just about regex.

You are building:

txt
Regex
   ↓
NFA
   ↓
DFA
   ↓
Generated C code



Which means:

- Parsing 
.l files
- Parsing regex
- Building automata
- DFA optimization
- Code generation
- Producing lex.yy.c

---

# 🏗 Compiler Pipeline

A real compiler pipeline looks like this:

txt
Source Code
     ↓
Lexer
     ↓
Tokens
     ↓
Parser
     ↓
AST
     ↓
Compilation



The lexer is the **first stage** of every compiler.

Without lexer:

- no parser
- no compiler
- no interpreter

---

# 🧩 Regex → Automata

Regex:

regex
[0-9]+



Human meaning:

> one or more digits

Machine meaning:

txt
(start)
   |
 [0-9]
   ↓
(NUMBER)
   ↓
 [0-9]
   ↺



A regex is actually a **state machine**.

---

# 🤖 Finite State Machines

Core idea:

txt
current_state
+
input_character
=
next_state



This is the foundation of:

- compilers
- regex engines
- syntax highlighters
- shells
- parsers
- browsers

---

# 🔀 NFA vs DFA

## NFA

Non Deterministic Finite Automaton

- multiple possible paths
- epsilon transitions
- easy to build from regex

Example:

txt
     ε
   ↙   ↘
  a     b



---

## DFA

Deterministic Finite Automaton

Rule:

txt
1 state
+
1 character
=
1 next state



DFA are:

- fast
- deterministic
- perfect for lexers

---

# ⚡ Why DFA Lexers Are Fast

A lexer generated from a DFA is often just:

c
state = transition[state][c];



That's almost the entire engine.

No recursion.  
No backtracking.  
No complex logic.

Which is why tools like:

- GCC
- Clang
- Flex
- Lex

can process millions of characters extremely fast.

---

# 📏 Longest Match Rule

The lexer always chooses:

1. the longest possible token
2. the first matching rule if equal

Example:

lex
if          KEYWORD
[a-z]+      IDENTIFIER



Input:

txt
if



Result:

txt
KEYWORD



Because both match,
but the first rule wins.

---

# 🧠 Internal Architecture

txt
main.c
  ↓
read .l file
  ↓
parse lex syntax
  ↓
extract regex + actions
  ↓
regex parser
  ↓
build NFA
  ↓
convert NFA → DFA
  ↓
optimize DFA
  ↓
generate C code
  ↓
write lex.yy.c



---

# 📚 What You Learn

ft_lex teaches:

- Automata Theory
- DFA / NFA
- Regex internals
- Parsing
- Compiler design
- Code generation
- Language theory

At the end:

txt
regex ≠ magic
regex = machine



---

# 🌌 The Deep Idea

A programming language is ultimately:

txt
text
 ↓
tokens
 ↓
states
 ↓
transitions
 ↓
rules



And yet from this:

- Linux exists
- Python exists
- browsers exist
- games exist
- compilers exist

---

# ❤️ Final Thought

ft_lex is not just a regex project.

It is about understanding:

> how machines read the world.

---

# 📖 References

- Compilers: Principles, Techniques, and Tools
- POSIX lex specification
- Dragon Book
- Automata Theory
- Flex & Lex documentation

---

# 👨‍💻 Author

txt
alanty gros










ft_lex — Liste courte des trucs à apprendre
1. Bases des lexers

Cherche :

what is a lexer
lexical analysis
compiler pipeline
lexer vs parser

Comprendre :

texte → tokens
2. Regex

Cherche :

regular expressions theory
regex operators
regex precedence

Maîtriser :

|
*
+
?
()
[]
3. Automates finis

Cherche :

finite state automata
finite state machine

Comprendre :

état + caractère = nouvel état
4. NFA

Cherche :

NFA explained
epsilon transitions

Comprendre :

regex → NFA
5. DFA

Cherche :

DFA explained
transition table

Comprendre :

state = table[state][c];
6. Thompson Construction ⭐ IMPORTANT

Cherche :

Thompson construction
regex to NFA
7. Subset Construction ⭐ ULTRA IMPORTANT

Cherche :

subset construction
NFA to DFA
powerset construction
8. Longest Match Rule

Cherche :

maximal munch
longest match lexer
9. Structure Lex/Flex

Cherche :

flex tutorial
lex file structure
yylex explained
yytext
10. Parsing regex ⭐ GROS MORCEAU

Cherche :

recursive descent parser
regex parser
shunting yard algorithm
🏆 Les 3 trucs les plus importants
1.
Regex → NFA
2.
NFA → DFA
3.
DFA → ultra fast lexer
        

β
This project is currently under beta-test, until it is validated by a fair number of
students in the 42 community. Please report any typo, incoherence, inconsistency, error,
using the form https://tally.so/r/3lVDJo
ft_lex
easy lexing
Summary: You probably developed lexers (or tokenizers) in previous projects. Now,
let’s create a generic lexer to use in all your projects!
Version: 1.00
Contents
I Forewords 2
II Objectives 3
II.1 Description . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 3
II.2 Example . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 4
III General rules 6
IV Mandatory part 7
IV.1 The program . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 7
IV.2 Testing . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 8
V Bonus part 9
V.1 Polyglotism . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 9
V.2 Compression . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 9
VI Submission and peer-evaluation 11
1
Chapter I
Forewords
— Would you like a drink? asked Colin. My pianocktail is finished, you could try it out.
— It works? asked Chick.
— Perfectly. I had trouble getting all the bugs out but the results go beyond my expectations.
I got a truly astounding mix out of Black and Tan Fantasy.
— How did you make it work? asked Chick.
— With every note, said Colin, I’ve matched a spirit, liqueur or flavoring. The loud pedal
corresponds to whipped egg and the soft pedal to ice. For seltzer water, you need to do a trill
in the upper register. The quantities are in direct proportion with the duration: the 64th note
equals a 16th part, a quarter note one part and a whole note four parts. When playing a slow
tune, a leveling system is put to work so that the quantity is not increased—that would make
for too abundant a cocktail—only the alcohol content. And, depending on the length of the
tune, the part’s valence can be changed, reducing it for example to one one-hundredth to get a
drink that takes into account all of the harmonies by means of a lateral regulator.
— That’s complicated, said Chick.
— Everything is controlled by electrical contacts and relays; I won’t give you the details, you
know all that. And besides, what’s more, the piano really works.
— That’s marvelous! said Chick.
— There’s only one problem, said Colin. The loud pedal for the whipped egg. I had to put in
a special system of interlocking parts because when you play a tune that’s too "hot," pieces of
omelet fall into the cocktail and it’s hard to swallow. I’ll modify that. For the time being, you
just need to be careful. For the sour cream, it’s low G.
— I’m going to make myself one on Loveless Love, said Chick. It’ll be great.
— It’s still in the junk room that I turned into a workshop, said Colin, because the protection
plates aren’t screwed in. Come on, let’s go. I’ll set it for two cocktails of about twenty cen-
tiliters, to start off with.
Chick sat down at the piano. At the end of the tune, part of the front panel opened up with
a clap and a row of glasses appeared. Two of them were filled to the rim with an appetizing
mixture.
— You scared me, said Colin. At one point you hit a wrong note. Luckily, it was in harmony.
— It accounts for the harmony? said Chick.
— Not all the time, said Colin. That would be too complicated. There are only a few con-
straints. Drink and come eat.
Boris Vian L’Écume des jours
The pianocktail could be an example of a finite-state transducer, its input alphabet is the
set of all the key of the piano and its output alphabet is the set of all the cocktail ingredients.
2
Chapter II
Objectives
In this project, you will implement the POSIX lex utility.
During this project, you will learn about automata theory, formal language theory, Chom-
sky hierarchy, dragons and a lot of weird mathematical symbols and Greek letters.
II.1 Description
Lex is a program that generates lexical analyzers (aka scanners or lexers or tokenizers).
It takes a .l file (a lex-specific format) as input and outputs a lex.yy.c file containing
the C source code that represent the lexer.
Lexical analysis is the process of converting a sequence of characters into a sequence
of lexical tokens.
This step is generally combined with syntactic analysis: the process of converting a
sequence of tokens into a data structure (often an Abstract Syntax Tree).
This is why lex is typically combined with yacc, another utility that will generates a
parser (this is the goal of the next project in this branch ft_yacc).
3
ft_lex easy lexing
II.2 Example
$> cat scanner.l
%%
[0-9]+ printf("NUMBER: %s\n", yytext);
"+" |
"-" |
"*" |
"/" printf("OPERATOR: %s\n", yytext);
"(" printf("OPEN PARENTHESIS\n");
")" printf("CLOSED PARENTHESIS\n");
"\n" printf("NEWLINE\n");
[[:blank:]] // ignore whitespaces
. printf("Invalid character: %c\n", *yytext);
$> lex scanner.l && clang -o scanner lex.yy.c -ll
$> echo "42+1337+(21*19)" | ./scanner
NUMBER: 42
OPERATOR: +
NUMBER: 1337
OPERATOR: +
OPEN PARENTHESIS
NUMBER: 21
OPERATOR: *
NUMBER: 19
CLOSED PARENTHESIS
NEWLINE
4
ft_lex easy lexing
A NFA recognizing the regex (( )*( | ) * * ?)*( )*( | ) *( *| *)
Generated by the bot @happyautomata made by @thingskatedid
5
Chapter III
General rules
• This project will only be evaluated by actual human beings. You are therefore free
to organize and name your files as you wish, although you need to respect some
requirements listed below.
• You are allowed to write your program in any of the following languages:
◦ C
◦ C++
◦ Java
◦ Zig
◦ Rust
◦ Caml/OCaml
◦ Any purely functional language
◦ Assembly (please don’t)
• In all cases, you are only allowed to use the standard library.
• The executable file must be named ft_lex.
• The libl must be named libl.
• If you use a compiled language, you must submit a Makefile or a configuration for
the native build system of your language.
• You have to handle errors in a sensitive manner. In no way can your program quit
in an unexpected manner (Segmentation fault, bus error, double free, etc).
• If a user error occurs (e.g., invalid regex in the .l file), your program must provide
a detailed error message (e.g., lexer.l:12 unexpected token ’)’)
6
Chapter IV
Mandatory part
IV.1 The program
• You must implement the lex utility as described by POSIX.1-2024 with all its
options and functionalities.
• Therefore, you must also implement the libl (a small utility library) as specified by
POSIX and write a makefile to compile it.
• You may choose any language from the list above, but the target language must be
C.
• The output C file must contain a compiled deterministic finite automaton.
• In the output file (and in the libl), you may only use the following functions:
◦ all the functions from <stdio.h>
◦ all the functions from <string.h>
◦ malloc(3)
◦ realloc(3)
◦ calloc(3)
◦ free(3)
Flex can be useful if you don’t understand the documentation and need
to experiment by yourself.
In some cases, POSIX says that something has unspecified behaviour
(for example, when using a locale other than POSIX). This means that
you are not required to handle these cases, but your program must not
crash. I advise you to read the POSIX terminology: here
7
ft_lex easy lexing
man dot
IV.2 Testing
You must provide example .l files, as well as files to parse, that cover all functionalities
of your ft_lex.
8
Chapter V
Bonus part
V.1 Polyglotism
You’ve done the difficult part, now let’s add another target language to your ft_lex, this
can be any language!
For the input file format you can take inspiration from the existing implementations (alex,
golex, jlex, ocamllex...) or invent a new one if you prefer.
You must add a flag to your program to switch the target language.
If you plan to realize cc1 later, think about the language that you
will use to make it.
Obviously, if you create a C++ version, you can’t simply reuse the C
code be creative.
V.2 Compression
As you can see, a deterministic finite automaton can be very very heavy (If you are not
convinced, try this regex: ‘(a{0,10000}){0,10000}‘).
For this bonus you must add some sort of compression algorithm to your program that
must really lighten your DFA, we’re talking about a 2x difference (for example try with
flex -t lexer.l | wc and flex -t -Cf lexer.l | wc).
Add a flag to your program that will enable this feature.
9
ft_lex easy lexing
The bonus part will only be assessed if the mandatory part is
PERFECT. Perfect means the mandatory part has been integrally done
and works without malfunctioning. If you have not passed ALL the
mandatory requirements, your bonus part will not be evaluated at all.
10
Chapter VI
Submission and peer-evaluation
Turn in your assignment in your Git repository as usual. Only the work inside your repos-
itory will be evaluated during the defense. Don’t hesitate to double check the names of
your folders and files to ensure they are correct.
11

j ai pas compris a quoi sert le regex dans ce projet esque je vais vraiment l utiliser ou bien m en servire d exemple et explique moi ce que c'est

Oui, tu vas vraiment utiliser les regex partout dans ft_lex.
En fait, le cœur du projet c’est précisément ça :

regex  →  automate  →  lexer

Le regex n’est pas juste un exemple décoratif.
C’est le langage que l’utilisateur écrit pour décrire les tokens.
🔥 Le vrai rôle du regex dans ft_lex

Quand quelqu’un écrit un fichier .l :

[0-9]+      NUMBER
[a-zA-Z]+   WORD
"+"         PLUS

toi, avec ft_lex, tu dois comprendre ces regex.

Puis transformer ça en machine.
🧠 Ce qu’est un regex

Un regex (regular expression) est une manière de décrire un motif de texte.

Exemples :
Regex	Signification
a	le caractère a
ab	la chaîne ab
`a	b`
a*	zéro ou plusieurs a
a+	un ou plusieurs a
[0-9]	un chiffre
[a-z]	une lettre minuscule
Exemple concret

Regex :

[0-9]+

Veut dire :

    “une suite de chiffres”

Donc :

42
1337
99999

matchent.

Mais :

abc
4a2

ne matchent pas.
⚡ Dans ft_lex, le regex sert à définir les tokens

Exemple :

%%
[0-9]+      printf("NUMBER\n");
"+"         printf("PLUS\n");
[a-z]+      printf("WORD\n");
%%

Ton programme devra :

    lire ces regex

    les parser

    construire un automate

    générer du C

🔥 Le regex devient une machine

Le point ultra important :

regex ≠ texte magique
regex = automate

Par exemple :

ab*

veut dire :

a
ab
abb
abbb

L’automate correspondant :

(start) --a--> (S1) --b--> (S1)

🧩 Pourquoi on transforme les regex en automates ?

Parce qu’un ordinateur ne “comprend” pas directement :

[a-z]+

Il comprend des états :

state + character = next_state

Donc tu fais :

regex
↓
NFA
↓
DFA
↓
table de transitions
↓
lexer ultra rapide

📌 Ce que TU vas coder

Tu vas coder :
1. Un parser de regex

Comprendre :

(a|b)*c+

comme une vraie structure logique.
2. Thompson Construction

Transformer le regex en NFA.

Par exemple :

a|b

devient :

      ε
    ↙   ↘
   a     b

3. Subset Construction

Transformer le NFA en DFA.

Car les DFA sont rapides.
4. Génération de code C

Produire un fichier comme :

state = transition[state][c];

🎯 En réalité ft_lex est surtout :

    un projet d’automates

    un projet de théorie des langages

    un mini compilateur

Le regex est juste le “langage d’entrée”.
🧠 Analogie simple

Imagine :

Regex = plan
Automate = machine construite à partir du plan
Lexer = machine qui travaille

📌 Exemple complet

Tu écris :

[0-9]+

Ton programme construit quelque chose comme :

(start)
   |
 digit
   ↓
(NUMBER)
   |
 digit
   ↺

Puis génère du C :

while (isdigit(c))
    state = transition[state][c];

❤️ Le moment où tout clique

Au début on croit que :

regex = fonction bizarre

Mais après ft_lex tu comprends que :

regex = description mathématique d’une machine

Et ça change complètement la vision des compilateurs et des langages.
🏆 Les 3 parties les plus importantes du projet
1. Parser les regex

Comprendre :

(a|b)*c+

2. Regex → NFA

(Thompson)
3. NFA → DFA

(Subset construction)

C’est LE cœur du projet.
📚 Ce que je te conseille d’apprendre dans l’ordre
Étape 1 — Regex simples

Comprendre :

a
ab
a*
a+
a?
a|b

Étape 2 — Automates

Comprendre :

état + caractère = nouvel état

Étape 3 — Thompson Construction

Le plus important.
Étape 4 — Subset Construction

Transformer NFA → DFA.
🔥 Résumé ultra simple

Le regex sert à :

décrire des tokens

Et ton projet consiste à :

transformer ces regex
en machine capable de lire du texte

Donc oui :

✅ tu vas énormément utiliser les regex
✅ tu dois les parser
✅ tu dois les transformer en automates
✅ c’est le cœur du projet

fait moi un shema complet du projet et de ces etapes

🧠 Vue Globale de ft_lex

                ┌──────────────────────┐
                │     fichier .l       │
                │  (règles utilisateur)│
                └──────────┬───────────┘
                           │
                           ▼
                ┌──────────────────────┐
                │  Parser fichier .l   │
                │----------------------│
                │ lit les sections lex │
                │ extrait regex/actions│
                └──────────┬───────────┘
                           │
                           ▼
                ┌──────────────────────┐
                │    Parser Regex      │
                │----------------------│
                │ comprend :           │
                │   |  *  +  ?  [] ()  │
                │ construit un AST     │
                └──────────┬───────────┘
                           │
                           ▼
                ┌──────────────────────┐
                │   Thompson Build     │
                │----------------------│
                │ Regex → NFA          │
                │ ajoute ε-transitions │
                └──────────┬───────────┘
                           │
                           ▼
                ┌──────────────────────┐
                │  Subset Construction │
                │----------------------│
                │ NFA → DFA            │
                │ fusion des états     │
                └──────────┬───────────┘
                           │
                           ▼
                ┌──────────────────────┐
                │   Optimisation DFA   │
                │----------------------│
                │ compression tables   │
                │ suppression états    │
                └──────────┬───────────┘
                           │
                           ▼
                ┌──────────────────────┐
                │ Génération code C    │
                │----------------------│
                │ crée lex.yy.c        │
                │ tables transitions   │
                │ moteur yylex()       │
                └──────────┬───────────┘
                           │
                           ▼
                ┌──────────────────────┐
                │ Compilation clang/gcc│
                └──────────┬───────────┘
                           │
                           ▼
                ┌──────────────────────┐
                │     Lexer final      │
                │----------------------│
                │ lit du texte         │
                │ produit des tokens   │
                └──────────────────────┘

🔥 Pipeline complet détaillé
1️⃣ Lecture du fichier .l

Exemple :

%%
[0-9]+      printf("NUMBER\n");
[a-z]+      printf("WORD\n");
"+"         printf("PLUS\n");
%%

Ton programme lit ça.
2️⃣ Parsing du format lex

Tu dois séparer :

REGEX          ACTION

Donc obtenir quelque chose comme :
Regex	Action
[0-9]+	printf(...)
[a-z]+	printf(...)
3️⃣ Parsing du regex

Tu transformes :

(a|b)*c+

en structure logique.

Exemple d’AST :

              CONCAT
             /      \
          STAR      PLUS
            |         |
           OR         c
         /    \
        a      b

4️⃣ Thompson Construction ⭐

Transformer l’AST en NFA.
Exemple :

Regex :

ab*

NFA :

(start) --a--> (S1) --ε--> (S2)
                        ↑    |
                        └-b--┘

🧠 Pourquoi un NFA ?

Parce qu’il est :

✅ facile à construire
✅ proche du regex
✅ mathématiquement propre

Mais :

❌ lent à exécuter directement
5️⃣ Subset Construction ⭐⭐⭐

Transformer :

NFA → DFA

Idée

Un état DFA représente :

PLUSIEURS états NFA

Exemple

NFA :

A --a--> B
A --a--> C

DFA :

{A} --a--> {B,C}

🔥 Résultat final : DFA

Règle :

1 état + 1 caractère = 1 seul état suivant

Exemple :

        digit
   ┌─────────────┐
   ▼             │
(NUMBER) --------┘

6️⃣ Tables de transitions

Le DFA devient :

transition[state][character]

Exemple :

state = transition[state][c];

C’est quasiment tout le lexer.
7️⃣ Longest Match Rule

Le lexer doit retenir :

dernier état valide rencontré

Exemple

Règles :

if          KEYWORD
[a-z]+      IDENTIFIER

Input :

if

Les deux matchent.

Mais :

la première règle gagne

8️⃣ Génération de lex.yy.c

Ton programme écrit du vrai C :

int yylex(void)
{
    while ((c = getchar()))
    {
        state = transition[state][c];

        if (accepting[state])
            ...
    }
}

9️⃣ Compilation

clang lex.yy.c -ll

↓

scanner executable

🔟 Lexer final

Input :

42 + abc

Output :

NUMBER
PLUS
IDENTIFIER

🧩 Architecture complète du projet

ft_lex/
│
├── parser/
│   ├── lex_parser.c
│   ├── regex_parser.c
│   └── ast.c
│
├── automata/
│   ├── nfa.c
│   ├── dfa.c
│   ├── epsilon.c
│   └── subset_construction.c
│
├── optimizer/
│   └── dfa_minimization.c
│
├── generator/
│   ├── codegen.c
│   └── templates.c
│
├── libl/
│   └── runtime.c
│
├── include/
│
├── tests/
│
└── main.c

🧠 Les structures importantes
AST Regex

typedef enum e_regex_type
{
    R_CHAR,
    R_CONCAT,
    R_OR,
    R_STAR,
    R_PLUS,
    R_OPTIONAL
} t_regex_type;

NFA State

typedef struct s_nfa_state
{
    int id;

    struct s_transition *transitions;

    bool accepting;
} t_nfa_state;

DFA Table

int transition[MAX_STATES][256];

🔥 Les 3 algorithmes du projet
1️⃣ Parsing regex

Transformer :

(a|b)*c

↓

AST
2️⃣ Thompson Construction

Transformer :

AST → NFA

3️⃣ Subset Construction

Transformer :

NFA → DFA

📌 Ordre idéal de développement
Phase 1

✅ parser .l
Phase 2

✅ parser regex
Phase 3

✅ construire AST
Phase 4

✅ Thompson NFA
Phase 5

✅ subset construction DFA
Phase 6

✅ moteur DFA
Phase 7

✅ génération C
🌌 Vision profonde du projet

Tu construis littéralement :

un programme
qui fabrique
des programmes

ft_lex est un :

lexer generator

Pas juste un lexer.
❤️ Le cerveau du projet

Regex
   ↓
Mathématiques
   ↓
Automates
   ↓
Tables
   ↓
Code C
   ↓
Lexer ultra rapide

C’est exactement comme fonctionnent :

    Flex

    Lex

    Clang

    GCC

    moteurs regex

    syntax highlighters

    parsers modernes


donne mooi la structure complete de ce projet je veut quelle soit la plus logique et comprenssible possible

🏗 Structure complète et logique de ft_lex

Le but :

séparer clairement :
- parsing
- automates
- génération
- runtime
- utilitaires

Comme un vrai compilateur.
🌌 Vision globale

                ┌────────────┐
                │  scanner.l │
                └─────┬──────┘
                      │
          parsing du fichier lex
                      │
                      ▼
             regex + actions
                      │
                parsing regex
                      │
                      ▼
                    AST
                      │
               Thompson build
                      │
                      ▼
                    NFA
                      │
            subset construction
                      │
                      ▼
                    DFA
                      │
               optimisation
                      │
                      ▼
                génération C
                      │
                      ▼
                 lex.yy.c

📁 Structure complète recommandée

ft_lex/
│
├── Makefile
├── README.md
├── lex.yy.c                 # généré
│
├── include/
│   ├── ft_lex.h
│   ├── token.h
│   ├── regex.h
│   ├── ast.h
│   ├── nfa.h
│   ├── dfa.h
│   ├── parser.h
│   ├── generator.h
│   └── error.h
│
├── src/
│
│   ├── main/
│   │   └── main.c
│   │
│   ├── lexer_file/
│   │   ├── lex_file_parser.c
│   │   ├── lex_sections.c
│   │   ├── lex_rules.c
│   │   └── lex_actions.c
│   │
│   ├── regex/
│   │   ├── regex_lexer.c
│   │   ├── regex_parser.c
│   │   ├── regex_ast.c
│   │   ├── regex_concat.c
│   │   ├── regex_charset.c
│   │   ├── regex_escape.c
│   │   └── regex_utils.c
│   │
│   ├── ast/
│   │   ├── ast_create.c
│   │   ├── ast_destroy.c
│   │   ├── ast_print.c
│   │   └── ast_utils.c
│   │
│   ├── nfa/
│   │   ├── nfa_create.c
│   │   ├── nfa_state.c
│   │   ├── nfa_transition.c
│   │   ├── nfa_epsilon.c
│   │   ├── thompson.c
│   │   ├── thompson_concat.c
│   │   ├── thompson_or.c
│   │   ├── thompson_star.c
│   │   ├── thompson_plus.c
│   │   └── thompson_optional.c
│   │
│   ├── dfa/
│   │   ├── dfa_create.c
│   │   ├── dfa_state.c
│   │   ├── subset_construction.c
│   │   ├── epsilon_closure.c
│   │   ├── move.c
│   │   ├── dfa_minimization.c
│   │   ├── dfa_table.c
│   │   └── dfa_debug.c
│   │
│   ├── generator/
│   │   ├── codegen.c
│   │   ├── generate_tables.c
│   │   ├── generate_yylex.c
│   │   ├── generate_headers.c
│   │   ├── generate_actions.c
│   │   └── template.c
│   │
│   ├── runtime/
│   │   ├── yyinput.c
│   │   ├── yytext.c
│   │   ├── yywrap.c
│   │   └── yyutils.c
│   │
│   ├── libl/
│   │   ├── libl.c
│   │   └── yywrap.c
│   │
│   ├── utils/
│   │   ├── vector.c
│   │   ├── hashmap.c
│   │   ├── string_builder.c
│   │   ├── queue.c
│   │   ├── stack.c
│   │   └── set.c
│   │
│   ├── error/
│   │   ├── error.c
│   │   ├── syntax_error.c
│   │   └── regex_error.c
│   │
│   └── debug/
│       ├── print_nfa.c
│       ├── print_dfa.c
│       ├── print_ast.c
│       └── graphviz.c
│
├── tests/
│   │
│   ├── regex/
│   ├── lexer/
│   ├── nfa/
│   ├── dfa/
│   └── integration/
│
├── examples/
│   ├── calculator.l
│   ├── json.l
│   ├── csv.l
│   ├── minishell.l
│   └── c_subset.l
│
└── docs/
    ├── regex.md
    ├── thompson.md
    ├── subset_construction.md
    └── architecture.md

🧠 Pourquoi cette structure est excellente

Parce qu’elle sépare :
Partie	Rôle
lexer_file	parse le .l
regex	comprend les regex
ast	structure logique
nfa	construction Thompson
dfa	subset construction
generator	génération C
runtime	fonctions lexer
utils	structures de données
🔥 Le flow exact entre dossiers
1️⃣ lexer_file/

Lit :

[0-9]+    printf("NUMBER");

Transforme en :

rule.regex = "[0-9]+";
rule.action = "printf(...)";

2️⃣ regex/

Comprend :

(a|b)*c+

et construit :

AST regex

3️⃣ ast/

Stocke :

CONCAT
 ├── STAR
 │    └── OR(a,b)
 └── PLUS(c)

4️⃣ nfa/

Transforme AST → NFA.

Le vrai cœur mathématique.
5️⃣ dfa/

Transforme :

NFA → DFA

avec subset construction.
6️⃣ generator/

Produit :

lex.yy.c

7️⃣ runtime/

Contient :

yytext
yywrap
input()

🔥 Structures importantes
AST

typedef struct s_ast
{
    int type;

    struct s_ast *left;
    struct s_ast *right;

    char value;
} t_ast;

NFA

typedef struct s_nfa_state
{
    int id;

    bool accepting;

    t_transition *transitions;
} t_nfa_state;

DFA

typedef struct s_dfa_state
{
    int id;

    bool accepting;

    int transitions[256];
} t_dfa_state;

📌 Les dossiers les plus importants
⭐ regex/

Tu vas y passer énormément de temps.

Car parser les regex est difficile.
⭐ nfa/

Le cœur Thompson.
⭐ dfa/

Le cœur algorithmique.

Subset construction = énorme morceau.
⭐ generator/

La magie finale.
🧩 Ordre conseillé de développement
Phase 1

utils/

Créer :

    vector

    stack

    queue

    set

Phase 2

regex/
ast/

Faire parser regex.
Phase 3

nfa/

Faire Thompson.
Phase 4

dfa/

Faire subset construction.
Phase 5

generator/

Produire C.
🧠 Vision mentale parfaite du projet

         REGEX
            │
            ▼
      arbre logique
            │
            ▼
           NFA
            │
            ▼
           DFA
            │
            ▼
     table transitions
            │
            ▼
      code C ultra rapide

🔥 Le vrai cerveau du projet

Le projet tourne autour de :

subset_construction.c

et :

thompson.c

C’est littéralement :

le moteur de tout lex/flex

❤️ Conseil ultra important

Ne commence PAS par :

générer du C

Commence par :

regex → NFA → DFA

Car si les automates sont mauvais :

tout le projet est mort


esque tu peut m expliquer a quoi servent chaque fichier et aussi ce que c est que une ast

🧠 D’abord : qu’est-ce qu’une AST ?

AST signifie :

Abstract Syntax Tree

En français :

Arbre Syntaxique Abstrait

C’est une représentation structurée d’une expression.
🔥 Pourquoi une AST existe ?

Quand tu lis un regex :

(a|b)*c+

Pour un humain c’est simple.

Mais pour un programme :

ce n’est qu’une suite de caractères

Donc il faut transformer :

"(a|b)*c+"

en structure logique.
📌 Exemple concret

Regex :

ab|c

Tu pourrais croire :

(a b) | c

Et c’est effectivement ça.

L’AST devient :

         OR
        /  \
    CONCAT  c
     /   \
    a     b

⚡ Pourquoi c’est utile ?

Parce qu’après :

tu peux construire le NFA récursivement

Par exemple :

si noeud = OR
→ construire branche gauche
→ construire branche droite
→ ajouter ε-transitions

🧩 Exemple avec a*

Regex :

a*

AST :

      STAR
        |
        a

Exemple avec (a|b)*c+

AST :

             CONCAT
            /      \
         STAR      PLUS
           |          |
           OR         c
         /    \
        a      b

❤️ Donc une AST sert à :

donner une structure logique au regex

C’est la base :

    des compilateurs

    des parseurs

    des regex engines

🔥 Maintenant les fichiers
📁 include/

Contient tous les .h
ft_lex.h

Header principal.

Contient :

typedef struct ...

et les includes globaux.
regex.h

Définit :

types regex
fonctions regex
tokens regex

Exemple :

enum e_regex_type
{
    R_CHAR,
    R_OR,
    R_STAR
};

ast.h

Définit la structure AST.

Exemple :

typedef struct s_ast
{
    int type;

    struct s_ast *left;
    struct s_ast *right;

    char value;
} t_ast;

nfa.h

Définit :

états NFA
transitions
epsilon

dfa.h

Définit :

états DFA
tables transitions

parser.h

Fonctions parsing.
generator.h

Fonctions génération C.
🔥 DOSSIER regex/

Le parser regex.
regex_lexer.c

Découpe le regex en tokens.

Exemple :

(a|b)*c

devient :
caractère	token
(	OPEN
a	CHAR
`	`
b	CHAR
)	CLOSE
*	STAR
regex_parser.c

Construit l’AST.

Le vrai parser.

Transforme :

tokens regex

↓

AST

regex_ast.c

Fonctions utilitaires AST.

Créer :

create_node(...)

regex_concat.c

Gère la concaténation implicite.

Exemple :

ab

signifie :

a CONCAT b

regex_charset.c

Gère :

[a-z]
[0-9]

regex_escape.c

Gère :

\n
\t
\*

🔥 DOSSIER ast/

Manipule l’arbre AST.
ast_create.c

Crée les noeuds.
ast_destroy.c

Libère la mémoire.
ast_print.c

Affiche l’AST pour debug.

Exemple :

CONCAT
 ├── a
 └── STAR(b)

🔥 DOSSIER nfa/

Le cœur Thompson.
thompson.c

Transforme AST → NFA.

LE fichier important.
thompson_concat.c

Construit :

A puis B

thompson_or.c

Construit :

A | B

avec epsilon branches.
thompson_star.c

Construit :

A*

avec boucle epsilon.
thompson_plus.c

Construit :

A+

thompson_optional.c

Construit :

A?

nfa_state.c

Crée états NFA.
nfa_transition.c

Ajoute transitions.
nfa_epsilon.c

Gère ε-transitions.
🔥 DOSSIER dfa/

Le deuxième énorme morceau.
subset_construction.c

Transforme :

NFA → DFA

Le fichier le plus important après Thompson.
epsilon_closure.c

Calcule :

tous les états accessibles via ε

move.c

Calcule :

où va un ensemble d’états avec un caractère

dfa_table.c

Construit :

transition[state][char]

dfa_minimization.c

Optimise le DFA.

Fusionne états identiques.
dfa_debug.c

Affiche DFA.
🔥 DOSSIER generator/

Produit lex.yy.c
codegen.c

Fichier principal génération.
generate_tables.c

Écrit :

int transition[...][256]

generate_yylex.c

Écrit :

int yylex(void)

generate_actions.c

Ajoute :

printf(...)

des règles lex.
template.c

Contient morceaux fixes du code C.
🔥 DOSSIER runtime/

Fonctions du lexer final.
yyinput.c

Lecture caractères.
yytext.c

Stocke texte matché.
yywrap.c

Fin de fichier.
🔥 DOSSIER utils/

Structures de données.
vector.c

Tableau dynamique.
stack.c

Pile.

Très utilisée pour parser.
queue.c

File FIFO.

Utilisée dans subset construction.
set.c

Ensemble d’états.

Très important pour DFA.
hashmap.c

Mapping rapide.
🔥 DOSSIER debug/

Ultra utile.
print_nfa.c

Affiche automate.
print_dfa.c

Affiche DFA.
graphviz.c

Génère graphes visuels.

Très utile pour debug.
🌌 Le flow exact

regex texte
     ↓
tokens regex
     ↓
AST
     ↓
NFA
     ↓
DFA
     ↓
transition table
     ↓
code C

❤️ Les fichiers les PLUS importants
⭐ regex_parser.c

Comprendre regex.
⭐ thompson.c

Construire NFA.
⭐ subset_construction.c

Construire DFA.
⭐ codegen.c

Générer lexer.
🧠 Le cœur intellectuel du projet

Le projet entier tourne autour de :

transformer une expression mathématique
en machine exécutable

Et cette transformation passe par :

AST

Parce qu’une AST donne :

une structure logique exploitable


donne moi les etapes que je doit faire pour faire ce projet dans l ordre dans lequelle je devrait les faire

🧠 Ordre idéal pour faire ft_lex

Le plus gros piège :

vouloir générer lex.yy.c trop tôt

Il faut construire les fondations dans le bon ordre.
🌌 Vision globale

Tu construis :

regex
   ↓
AST
   ↓
NFA
   ↓
DFA
   ↓
lexer C

Donc tu dois coder exactement dans cet ordre.
🏗 PHASE 0 — Préparation du projet
✅ Étape 0.1 — Structure du repo

Créer :

include/
src/
tests/
examples/

✅ Étape 0.2 — Utils

Créer :

vector
stack
queue
set
string builder

Car tout le projet dépend de ça.
🔥 PHASE 1 — Comprendre les regex

⚠️ Très importante.

Avant de coder :

tu dois comprendre :
Regex	Signification
a	caractère
ab	concat
`a	b`
a*	répétition
a+	une ou plusieurs
a?	optionnel
✅ Étape 1.1 — Lexer regex

Créer :

regex_lexer.c

Transformer :

(a|b)*c

en tokens.
Exemple

Input :

(a|b)*c

Output :

OPEN
CHAR(a)
OR
CHAR(b)
CLOSE
STAR
CHAR(c)

🔥 PHASE 2 — Parser regex
✅ Étape 2.1 — AST

Créer :

typedef struct s_ast
{
    int type;
    struct s_ast *left;
    struct s_ast *right;
    char value;
} t_ast;

✅ Étape 2.2 — Parser récursif

Créer :

regex_parser.c

Transformer :

tokens

↓

AST

⚡ Objectif

Regex :

(a|b)*c+

AST :

             CONCAT
            /      \
         STAR      PLUS
           |          |
           OR         c
         /    \
        a      b

✅ Étape 2.3 — Affichage AST

Créer :

print_ast()

Très important pour debug.
🔥 PHASE 3 — Thompson Construction ⭐

LE vrai début du projet.
✅ Étape 3.1 — Structures NFA

Créer :

typedef struct s_nfa_state
{
    int id;
    bool accepting;
    t_transition *transitions;
} t_nfa_state;

✅ Étape 3.2 — Transitions

Créer :

caractère
epsilon

✅ Étape 3.3 — Thompson pour chaque opérateur
CHAR

a

↓

(start)--a-->(end)

CONCAT

ab

↓

A puis B

OR

a|b

↓

      ε
    ↙   ↘
   a     b

STAR

a*

↓

boucle epsilon.
PLUS

a+

OPTIONAL

a?

✅ Étape 3.4 — Affichage NFA

Créer :

print_nfa()

🔥 PHASE 4 — Subset Construction ⭐⭐⭐

Le plus gros morceau algorithmique.
✅ Étape 4.1 — epsilon closure

Comprendre :

tous les états accessibles via ε

✅ Étape 4.2 — move()

Calculer :

où vont les états avec un caractère

✅ Étape 4.3 — DFA states

Un état DFA représente :

un ensemble d’états NFA

✅ Étape 4.4 — Construire le DFA

Transformer :

NFA → DFA

✅ Étape 4.5 — Affichage DFA

Créer :

print_dfa()

🔥 PHASE 5 — Simulateur DFA

Avant de générer du C :

tester ton DFA directement.
✅ Étape 5.1 — Lire caractères

Faire :

state = transition[state][c];

✅ Étape 5.2 — Acceptation

Détecter :

état final

✅ Étape 5.3 — Longest match

Le lexer doit retenir :

dernier état valide

🔥 PHASE 6 — Parser .l

Maintenant seulement.
✅ Étape 6.1 — Lire sections

Lex file :

%{
code
%}

%%
rules
%%

user code

✅ Étape 6.2 — Extraire règles

Transformer :

regex + action

🔥 PHASE 7 — Multi-regex DFA

Maintenant :

plusieurs règles.
✅ Étape 7.1 — Fusionner NFA

Créer :

super état initial

avec epsilon vers tous les regex.
✅ Étape 7.2 — Priorités lex

Gérer :

longest match
+
première règle gagne

🔥 PHASE 8 — Génération de code C

Maintenant seulement.
✅ Étape 8.1 — Générer tables

transition[state][256]

✅ Étape 8.2 — Générer yylex()

int yylex(void)

✅ Étape 8.3 — Générer actions

Insérer :

printf(...)

🔥 PHASE 9 — libl

Créer :

yywrap
yytext
etc

🔥 PHASE 10 — Optimisation

Maintenant seulement.
✅ DFA minimization

Fusion états identiques.
✅ Compression tables

Bonus.
🧠 Ordre exact ultra résumé
1️⃣ Utils

vector stack set queue

2️⃣ Regex lexer

regex → tokens

3️⃣ Regex parser

tokens → AST

4️⃣ Thompson

AST → NFA

5️⃣ Subset construction

NFA → DFA

6️⃣ DFA simulator

tester lexer

7️⃣ Parse .l

regex + actions

8️⃣ Multi-rule DFA

vrai lexer

9️⃣ Génération C

lex.yy.c

🔥 Les 3 étapes les plus difficiles
⭐ Regex parser

Car précédence.
⭐ Thompson

Car epsilon transitions.
⭐ Subset construction

Car ensembles d’états.
❤️ Conseil CRUCIAL

Ne passe PAS à l’étape suivante tant que :

la précédente n’est pas PARFAITE

Par exemple :

❌ ne fais PAS DFA si :

le NFA est faux

Sinon :

tu vas debug dans l’enfer

🌌 La vraie progression mentale

Tu vas progressivement comprendre :

regex
→ logique
→ graphes
→ automates
→ compilateurs

Et c’est exactement ce que ce projet veut enseigner.


