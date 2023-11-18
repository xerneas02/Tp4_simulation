# Simulation de Population de Lapins

Ce programme simule l'évolution d'une population de lapins sur plusieurs années en fonction de différentes configurations. Il utilise un générateur de nombres aléatoires Mersenne Twister pour modéliser la reproduction des lapins et la survie en fonction de l'âge.

## Compilation

Le projet est accompagné d'un fichier `Makefile` qui simplifie le processus de compilation. Pour compiler le code, exécutez la commande suivante dans le répertoire du projet :

```bash
make
```
Cela générera l'exécutable `bin/main.exe`.

## Exécution
Une fois compilé, vous pouvez exécuter le programme en utilisant la commande suivante :
```bash
./bin/main.exe
```
## Contenu du Projet
- main.cpp : Le fichier source principal contenant la fonction main et la logique principale de la simulation.
- simulation.hpp et simulation.cpp : Les fichiers définissant la classe Simulation pour la simulation de la population de lapins.
- rabbitCategory.hpp et rabbitCategory.cpp : Les fichiers définissant la classe RabbitCategory pour représenter une catégorie de lapins.
- mt.hpp : Le fichier définissant le générateur de nombres aléatoires Mersenne Twister.
- latex/latex.h : Le fichier définissant la classe LatexFile pour générer des fichiers LaTeX avec des graphiques.

## Auteur
Mathis Roubille & Thomas Dupois
