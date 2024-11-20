#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define N 2
#define MAX 10

int compteur = 0;
int fils[N];

void erreur(const char *message) {
    printf("Erreur durant : %s\n", message);
    exit(EXIT_FAILURE);
}

void afficherPere() {
    printf("Je suis un père ! PID = %d. PID de mon pere = %d\n", getpid(), getppid());
}

void afficherFils(const int index) {
    printf("Je suis le fils %d de pid : %d, père est : %d\n", index, getpid(), getppid());
}

void execFils(const int index) {
    while (compteur < MAX)
    {
        afficherFils(index);
        compteur++;
        sleep(1);
    }
    exit(EXIT_SUCCESS); // on kill les fils
}

void creerFils(const int index) {
    switch (fils[index] = fork()) {
        case -1:
            erreur("fork");
            break;
        case 0:
            execFils(index);
            break;
        default:
            break;
    }
}

int main(const int argc, char const *argv[]) {
    int i;
    int j;

    for (i = 0; i < N; i++) {
        creerFils(i);
    }

    for (j = 0; j < N; j++) {
        waitpid(fils[j], NULL, 0);
    }

    printf("Je suis le père ! PID = %d\n", getpid());
    printf("Fin du programme exo2\n");

    return EXIT_SUCCESS;
}
