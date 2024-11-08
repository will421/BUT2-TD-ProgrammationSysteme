# TD1 - Les pointeurs

## Exercice 0 : premier code C

```c
#include <stdio.h>

int main(const int argc, char *argv[] ){
    //argc : nombre d’arguments, argv : le tableau contenant la valeur des arguments
    int a = 1 ;
    printf(" le chiffre est %d \n ", a);

    char clavier[100];
    printf(" Saisissez le texte : ");
    scanf("%s", clavier);
    printf("vous avez saisie : %s \n", clavier);

    printf("\nMainenant, on va lister tous les arguments (argv)\n");
    int i;
    for (i = 0; i < argc; i++){
        printf("%s \n", argv[i]);
    }
    return 0;
}

```

Commande de compilation : `gcc nom_du_fichier.c -o nom_executable`

Execution : `./nom_executable`

## Exercice 1 : pointeurs simples

Créer 3 fonctions "*plus*", "*moins*" et "*fois*".

Chacune des trois fonctions prend 3 paramètres de type pointeur d’entier (int*) et effectue l’opération entre les deux premiers paramètres pour stocker le résultat dans le troisième.

Dans le *main()*, définir 3 variables de type entier x, y et z (x=50, y=20, z=0).
Puis tester les 3 fonctions en affichant le résultat entre chaque utilisation d’une fonction.

## Exercice 2 : pointeurs avec structure

Définir une structure "Coordonnees" contenant 3 entiers (x, y, z)

La fonction *main()* déclare une variable **ici** de type "Coordonnees". Elle envoie l’adresse de cette variable à une fonction *"initialiser"* qui initialise respectivement les valeurs x, y et z à 1,
5 et 2.

Ensuite, la fonction *main()* envoie l’adresse de la variable **ici** aux 3 fonctions suivantes :
* afficher : affiche la valeur de x, y et z ;
* multiplier : multiplie x et y puis stocke le résultat dans z ;
* additionner : additionne x et y puis stocke le résultat dans z.

La fonction *"afficher"* peut être utilisée plusieurs fois afin de voir l’évolution des opérations.

## Exercice 3 : pointeurs plus

Reprendre l’exercice précédent, mais cette fois la fonction *"afficher"* sera appelée dans les fonctions de multiplication et d’addition

## Exercice 4 : création de tableau dynamique

Proposer un programme C qui demande de saisir une taille de tableau, puis alloue dynamiquement un tableau d’entiers de cette taille (voir [rappel](#rappel)), le remplit avec des valeurs aléatoires comprises entre 0 et 100 et l’affiche.

## Exercice 5 : modification de tableau dynamique

Reprendre le code précédent et, en plus, on changera la taille du tableau (en gardant les données initiales) en fonction d’une nouvelle taille saisie par l’utilisateur (voir [rappel](#rappel)). Si la taille est plus grande, il faut ajouter de nouvelles valeurs aléatoires.

On affichera le nouveau tableau.

## Exercice 6 : création de matrice dynamique

Proposer un programme C qui qui alloue dynamiquement une matrice (int **) d’entiers, la remplit avec des valeurs aléatoires et l’affiche.

Le nombre de lignes et de colonnes étant saisis, au clavier, par l’utilisateur.

## Exercice 7 : modification de matrice dynamique

Reprendre le code précédent et, en plus, on changera la taille de la matrice en fonction de deux nouveaux nombres de lignes et de colonnes saisis au clavier. La matrice doit garder les anciennes valeurs.

On affichera la nouvelle matrice

## Exercice 8 : tableau de chaînes de caractères

Proposer un programme C qui saisit un nombre **N** de chaînes. Puis alloue dynamique un tableau de **N** chaînes de caractères et le remplit avec des valeurs saisies dans le terminal. Les chaînes de caractères doivent aussi être alloué dynamiquement (en utilisant la taille de chaque chaîne entrée)

Le programme doit afficher, **à la fin**, les chaînes du tableau.

Fonctions utiles : Il faut inclure `string.h`
* `strlen(chaîne)` pour avoir la taille d'une chaîne
* `strcpy(tableauCible, tableauACopier)` pour copier une chaîne
* `fgets(chaîne, maxLength, stream)` pour remplacer `scanf` et qui permet de lire des espaces
    * Dans notre cas, **stream** sera `stdin`
* `atoi(chaîne)` pour convertir une chaîne en entier


## Rappel

### Création d'un tableau dynamique

```c
char * tableau = malloc(20 * sizeof(char)); //Allocation d'un tableau de 20 caractères
if (tableau == NULL) {
    printf("L'allocation n'a pu être réalisée\n");
} else {
    printf("L'allocation a été un succès\n");
    ... je fais des traitements ...
    free(tableau); //Libération des 20 caractères précédemment alloués
    tableau = NULL; // Invalidation du pointeur
}
```

### Modification d'un tableau

```c
char * tmp = realloc(tableau, nouvelleTaille * sizeof(char));
if (tmp == NULL) {
    free(tableau);
    printf("La réallocation n'a pu être réalisée\n");
} else {
    tableau = tmp;
}
```


# TD1 bonus - Les fichiers

> Pour ceux qui ont fini le TD1 en avance.

## Exercice 9 : utilisation des fonctions

Tout d’abord créer un fichier **test1.txt** avec 3 lignes écrites.
Écrire un programme effectuant les instructions suivantes :
* Création : `creat(nom, mode);` // créer un fichier test2.txt
* Ouverture :
    * int fd1 = `open(char[], O_RDONLY);` // ouvrir en lecture le fichier test1.txt
    * int fd2 = `open(char[], O_WRONLY);` // ouvrir en écriture le fichier test2.txt
* Lecture : `int read_size = read(fd, buffer, taille);` // lire 10 caractères de test1.txt
* Écriture : `int write_size = write(fd, buffer, taille);` // écrire ces 10 caractères dans test2
* Fermeture : `close(fd);` // fermer les fichiers test1.txt et test2.txt
* Renommer : `rename(ancienNom, nouveau);` // renommer test2.txt en test3.txt
* Suppression : `unlink(nom);` // supprimer le fichier test1.txt

## Exercice 10 :  utilisation de paramètres

Proposer un programme qui prend en paramètre (argv) deux noms.

Le but du programme est de copier le contenu du fichier portant le nom du premier
argument, dans un fichier portant le nom du second argument, puis d’effacer le premier
fichier.

Précision : le deuxième fichier n’existe pas, il sera créé par le programme

## Exercice 11 : lecture partielle

Faire un programme permettant d’ouvrir un fichier contenant au moins 30 caractères, de lire
les 10 caractères suivant les 15 premiers.

### Fonction utile
`lseek(fd, nombre_caracteres_a_decaler, option);`
Options : SEEK_CUR, SEEK_SET, SEEK_END

## Exercice 12 :  utilisation des fonctions, la suite

Écrire un programme effectuant les instructions suivantes :
* Création : `s = mkdir(chemin, mode);` // créer un dossier **TEST**
* Création de lien : `s = link(fichier, lien);` // définir un lien du fichier **test.txt** vers **t_link**
* Suppression de lien : `s = unlink(chemin);` // supprimer le lien
* Changement de répertoire : `s = chdir(chemin);` // aller dans le répertoire **TEST**
* Création : créer un fichier **test_td2.txt** dans le répertoire **TEST**
* Suppression : `s = rmdir(chemin);` // supprimer le dossier **TEST**

## Exercice 13 : listing d’un dossier

Faire un programme qui liste l’ensemble du contenu d’un dossier passé en paramètre (argv)
en affichant le nom et le type de chaque objet listé (fichier, lien, répertoire…)

## Exercice 14 : listing récursif de dossier

Variante du programme précédent.
Lister le contenu d’un répertoire et des répertoires situés à l’intérieur

## Exercice 15 :  création d’une arborescence

Écrire un programme demandant à l’utilisateur de saisir des noms de dossier à créer.

## Exercice 16 : un peu plus

Écrire un programme se présentant sous forme d’un menu, avec pour choix la création de
fichier ou de dossier, et la possibilité de naviguer dans les dossiers.