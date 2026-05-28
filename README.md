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
        