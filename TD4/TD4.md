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

L'idée, c'est qu'après chaque connexion reçu, il faut créer un thread pour s'occuper de la reception de messages pour la connexion.

Utiliser `pthread_detach` pour detacher le thread créé du thread principal et ne plus avoir à l'attendre

```c
void lancerThread(data *data)
{
    if (pthread_create(&thread_id, NULL, threadFct, data) != 0)
    {
        perror("erreur de creation du thread");
        exit(EXIT_FAILURE);
    }
    // Pour que le systeme nettoie le thread sans appel à pthread_join
    pthread_detach(thread_id);
}
```

A savoir que `pthread_exit` ne fonctionnera plus. Pour arreter le thread, il faudra sortir de la fonction avec `return`.

Autre information, `pthread_t` est juste une variable pour contenir l'"id" vers un thread, lors de l'appel à `pthread_create`. La variable peut être réutilisé si il n'y a plus besoin de l'id. Il n'y a donc pas besoin d'en créer plein.

### Etape 2 : D'autres types de clients

Pour le moment, notre client ne peut qu'envoyer des messages. C'est dû au fait que sur un terminal, il est compliquer de demander à l'utilisateur de taper des message tout en affichant de nouveaux messages.

Pour contourner cette limitation nous allons créer 2 clients :
* un `client` qui est identique au client actuel et qui va uniquement envoyer des messages
* un `client-receveur` dont le seul rôle sera de recevoir des messages du serveur et de les afficher

Pour que le serveur puisse les différencier, le premier message envoyé par le client contiendra son rôle.
* le message contiendra `emetteur` pour le `client`
* le message contiendra `receveur` pour le `client-receveur`

Le serveur lui, va traiter les sockets de `client` comme il le fait déjà.
Pour les `client-receveur`, il enverra le message reçu depuis chaque `client`

Vous trouverez un `client-receveur` fonctionel dans le dossier `etape2`

### Etape 3 : Echanger plus d'informations

Nous allons établir un protocole pour donner de l'information sur le contenu de messages.

* Le premier message (après le rôle) émit par `client` et reçu par `serveur` contiendra le pseudo du client.
    * Il faudra demander le pseudo à l'utilisateur client
    * Coté serveur, il faudra stocker ce pseudo l'afficher à la connexion et à chaque message reçu
    * Et le transmettre aux `client-receveur`

### Etape 4 : Ajout d'historique

Le serveur devra stocker les 20 derniers messages reçu pour les envoyer aux `clients-receveur` dès leur connexion.