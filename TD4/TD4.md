# TD4 : Threads

## Exercice 1 : Répartir le travail

Écrire un programme qui initialise un tableau d'entier de taille **4** avec des **0**. 
Ce programme va lancer 4 threads en **parallèle**.
* Le premier thread ajoute 4 à chaque case du tableau
* Le deuxième thread divise par 2 chaque case du tableau
* Le troisième thread multiplie par 4 chaque case du tableau
* Le quatrième thread retranche 5 chaque case du tableau

Pour que les traitements s'exécutent en parallèle, ajoutez un appel à `sleep(1)` (nécessite `#include <unistd.h>`) après chaque opération.

Lancer plusieurs fois le programme, vous devriez avoir des résultats différents. \
(Ne pas oublier d'afficher les valeurs intermédiaires).

## Exercice 2 : Coordonner le travail

Reprendre l'exercice précédent mais utiliser des mutex pour proteger l'accès en écriture aux elements du tableau.

## Exercice 3 : Appliquer au client-serveur

Reprendre le code de server.c et client.c similaire ce qui à été fait au TD3

### Etape 1 : Plusieurs connexions

Permettre à plusieurs clients de se connecter à l'aide de threads

### Etape 2 : Echanger plus d'informations

Nous allons établir un protocole pour donner de l'information sur le contenu de messages.

* Le premier message émit et reçu contiendra le pseudo du client.
    * Il faudra demander le pseudo à l'utilisateur client
    * Coté serveur, il faudra stocker ce pseudo l'afficher à la connexion et à chaque message reçu

### Etape 3 : D'autres types de clients

Pour le moment, notre client ne peut qu'envoyer des messages. C'est dû au fait que sur un terminal, il est compliquer de demander à l'utilisateur de taper des message tout en affichant de nouveaux messages.

Pour contourner cette limitation nous allons créer 2 clients :
* un `client-emetteur` qui est identique au client actuel et qui va uniquement envoyer des messages
* un `client-receveur` dont le seul rôle sera de recevoir des messages du serveur et de les afficher

Pour que le serveur puisse les différencier, le premier message envoyé par le client contiendra son rôle.
* le message contiendra `emetteur` pour le `client-emetteur`
* le message contiendra `receveur` pour le `client-receveur`

Bien sur, l'emetteur enverra ensuite le pseudo comme fait dans l'étape 2.

Le serveur lui, va traiter les sockets de `client-emetteur` comme il le fait déjà.
Pour les `client-receveur`, il enverra une copie du message reçu depuis chaque `client-emetteur` (avec le pseudo ajouté)

### Etape 4 : Ajout d'historique

Le serveur devra stocker les 20 derniers messages reçu pour les envoyer aux `clients-receveur` dès leur connexion.