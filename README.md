# ft_lex - Un Générateur d'Analyseur Lexical (Lexer)

**ft_lex** est une implémentation personnalisée de l'outil standard POSIX `lex`. C'est un générateur d'analyseur lexical écrit en C.

Un "lexer" (ou analyseur lexical) est un programme qui lit une séquence de caractères (du texte) et la transforme en une séquence de **tokens** (des jetons porteurs de sens). C'est souvent la toute première étape dans la compilation d'un langage de programmation.

L'objectif de `ft_lex` est de lire un fichier de règles `.l` (contenant des expressions régulières) et de générer automatiquement un code source C (`lex.yy.c`) très performant capable de reconnaître ces modèles dans un texte donné.

---

## Sommaire
1. [Utilisation et Compilation](#utilisation-et-compilation)
2. [Comment ça marche ? L'Architecture Interne](#comment-ça-marche--larchitecture-interne)
3. [1. L'Arbre Syntaxique Abstrait (AST)](#1-larbre-syntaxique-abstrait-ast)
4. [2. L'Automate Fini Non-Déterministe (NFA)](#2-lautomate-fini-non-déterministe-nfa)
5. [3. La Construction de Sous-ensembles (Subset Construction)](#3-la-construction-de-sous-ensembles-subset-construction)
6. [4. L'Automate Fini Déterministe (DFA) et sa Minimisation](#4-lautomate-fini-déterministe-dfa-et-sa-minimisation)
7. [5. La Génération du Code C](#5-la-génération-du-code-c)

---

## Utilisation et Compilation

Pour compiler le projet et générer les exécutables :
```bash
make
```
Cela produit deux fichiers essentiels requis par la norme POSIX :
- L'exécutable `ft_lex` : le programme qui génère le code en C.
- La bibliothèque statique `libl.a` : une librairie utilitaire contenant un point d'entrée par défaut (`main`) et une gestion de la fin de fichier (`yywrap`).

### Exemple d'utilisation

1. **Créer un fichier de règles (`scanner.l`)** :
   ```lex
   %%
   [0-9]+  printf("NUMBER: %s\n", yytext);
   "+"     printf("PLUS\n");
   %%
   ```
2. **Générer le code source C** avec `ft_lex` :
   ```bash
   ./ft_lex scanner.l
   ```
   *(Cela va créer le fichier `lex.yy.c` dans votre dossier).*

3. **Compiler l'analyseur généré** en le liant avec la `libl` :
   ```bash
   cc -o scanner lex.yy.c -L. -ll
   ```

4. **Tester l'analyseur** :
   ```bash
   echo "42+" | ./scanner
   ```

---

## Comment ça marche ? L'Architecture Interne

Générer un analyseur lexical ne consiste pas juste à faire des gros `if/else`. Pour des raisons de performance mathématique, l'outil repose sur la théorie des automates. 

Voici le pipeline (flux de données) exact de `ft_lex` pour chaque expression régulière trouvée dans le fichier `.l` :
`Regex -> AST -> NFA -> DFA -> DFA Minimisé -> Code C`.

Voici les explications détaillées de chacune de ces étapes.

---

### 1. L'Arbre Syntaxique Abstrait (AST)

La première étape est de lire l'expression régulière (ex: `(a|b)*c`) et d'en comprendre la structure hiérarchique.
Le programme transforme cette chaîne de caractères en un arbre, appelé **AST (Abstract Syntax Tree)**. 

* Dans un AST, les "feuilles" sont les caractères individuels (ex: `a`, `b`, `c`).
* Les "noeuds" (les intersections) sont les opérateurs (ex: `OR` pour `|`, `STAR` pour `*`, `CONCAT` pour lier deux caractères).

**Pour la regex `(a|b)*c`, l'AST généré ressemblera à :**
```text
          CONCAT
         /      \
       STAR      'c'
        |
        OR
       /  \
     'a'  'b'
```
Cette étape de parsing s'assure que les priorités mathématiques sont respectées (l'étoile s'applique bien au résultat du `OU`, et le tout est concaténé avec `c`).

---

### 2. L'Automate Fini Non-Déterministe (NFA)

Une fois l'AST obtenu, on le traduit en un **NFA (Nondeterministic Finite Automaton)** grâce à **l'algorithme de construction de Thompson**.

Un automate fini est comme un jeu de plateau avec des cases (les "états") et des flèches entre les cases (les "transitions").
* On commence sur une case "Départ".
* On lit une lettre du texte, et on suit la flèche qui porte cette lettre.
* Si à la fin du mot on atterrit sur une case "Acceptante" (finale), alors le mot est valide !

**Pourquoi "Non-Déterministe" ?**
Dans un NFA, pour un même état, il peut y avoir :
* Plusieurs flèches qui portent la même lettre.
* Des flèches "fantômes" (les transitions **Epsilon** `ε`), qu'on peut traverser sans avoir à lire aucune lettre.

L'algorithme de Thompson est très simple car il crée des petits blocs de NFA de manière modulaire (un bloc pour `*`, un bloc pour `|`, etc.) et relie ces blocs entre eux à l'aide de ces fameuses transitions fantômes Epsilon.

Cependant, il est impossible de faire tourner un NFA de façon performante dans un programme informatique, car face à un "choix" non déterministe, l'ordinateur devrait tester toutes les possibilités en parallèle (ce qui prendrait trop de temps).

---

### 3. La Construction de Sous-ensembles (Subset Construction)

C'est ici qu'intervient l'algorithme de la **Subset Construction** (ou "déterminisation").
Son but est de convertir notre NFA complexe et incertain en un **DFA (Deterministic Finite Automaton)**.

**Le principe :**
Un DFA est strictement déterministe. Pour chaque état et chaque lettre, il n'y a **qu'une seule flèche possible**. Et il n'y a **aucune transition Epsilon**. C'est parfait pour un ordinateur !

Pour construire le DFA à partir du NFA, on fait des "groupes d'états" :
1. On calcule la "Fermeture Epsilon" (Epsilon-closure) de notre point de départ, c'est-à-dire toutes les cases du NFA qu'on peut atteindre sans lire aucune lettre. Ce grand groupe de cases devient le **premier état unique** de notre DFA.
2. Pour chaque lettre de l'alphabet (ex: `a`), on regarde où toutes ces cases nous mènent. Le groupe de cases d'arrivée forme un **nouvel état** du DFA.
3. On répète l'opération en boucle jusqu'à ce qu'il n'y ait plus de nouveaux groupes.

Le résultat est un automate où on sait toujours exactement où on va, ce qui permet à `lex.yy.c` de trouver les tokens en temps constant $O(n)$ !

---

### 4. L'Automate Fini Déterministe (DFA) et sa Minimisation

Le Subset Construction fonctionne parfaitement, mais il a tendance à créer des DFAs avec énormément d'états redondants (des états qui font exactement la même chose mais qui n'ont pas été fusionnés). Cela prendrait trop de mémoire RAM (tables de transition gigantesques).

C'est pourquoi nous appliquons l'**Algorithme de Minimisation de Moore** (ou de Hopcroft).
Cet algorithme cherche les états "équivalents" et les fusionne. 
* Deux états sont considérés équivalents si, peu importe la lettre qu'on lit ensuite, ils nous amèneront tous les deux vers un succès ou tous les deux vers un échec.
* L'algorithme regroupe ces états et affine les partitions jusqu'à obtenir le DFA le plus petit possible mathématiquement.

---

### 5. La Génération du Code C

Maintenant que nous avons le DFA parfait, optimisé et minimal pour chaque règle, il faut en faire un programme C (`lex.yy.c`).

Le générateur de code C (`src/generator/`) va parcourir le DFA et écrire de gigantesques tableaux à deux dimensions (tableaux de `transitions`) dans le fichier C. 

```c
// Exemple du tableau généré dans lex.yy.c
int yy_transition[RULE_COUNT][ETATS][ALPHABET] = { ... };
```

La boucle principale générée (la fonction `yylex()`) est un simulateur universel de DFA :
1. Elle lit un caractère du flux entrant (`stdin` ou un fichier).
2. Elle interroge le tableau : `prochain_etat = yy_transition[regle][etat_actuel][caractere]`.
3. Si elle atteint un "état acceptant", elle note la longueur du texte trouvé.
4. Si le DFA se bloque (plus de flèches), elle s'arrête, renvoie le plus long match valide trouvé (règle du **Longest Match**), exécute le bout de code C (printf, return, etc) que vous avez associé à la règle dans votre `.l`, et recommence la boucle pour le prochain token !