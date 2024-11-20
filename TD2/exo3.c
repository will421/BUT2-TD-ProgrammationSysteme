#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void afficherPere() {
    printf("Je suis un père ! PID = %d. PID de mon pere = %d\n", getpid(), getppid());
}

void afficherFils(int index) {
    printf("Je suis un fils %d de pid : %d, père est : %d\n", index, getpid(), getppid());
}

void erreur(const char *message) {
    printf("Erreur durant : %s\n", message);
    exit(EXIT_FAILURE);
}

int main(const int argc, char const *argv[]) {
    int fils1;
    int fils2;

    char *argsProgramme1[] = {"3.A.prog", NULL};
    char *argsProgramme2[] = {"3.B.prog", NULL};

    switch (fils1 = fork()) {
        case -1:
            erreur("fork fils1");
            break;
        case 0:
            afficherFils(1);
            execv(argsProgramme1[0], argsProgramme1);
            // normalement rien n'est executé après execv
            erreur("execv");
            break;
    }

    switch (fils2 = fork()) {
        case -1:
            erreur("fork fils2");
            break;
        case 0:
            afficherFils(2);
            execv(argsProgramme2[0], argsProgramme2);
            // normalement rien n'est executé après execv
            erreur("execv");
            break;
    }

    // ici le pere
    wait(&fils1);
    wait(&fils2);
    printf("Fin du programme\n");

    return EXIT_SUCCESS;
}
