#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define N 3

void erreur(const char *message) {
    printf("Erreur durant : %s\n", message);
    exit(EXIT_FAILURE);
}

void execFils() {
    printf("Je suis un fils : %d, mon père est : %d\n", getpid(), getppid());
    exit(EXIT_SUCCESS); // on kill les fils
}

int main(const int argc, char const *argv[]) {
    int pid[N];

    for (int i = 0; i < N; i++) {
        switch (pid[i] = fork()) {
            case -1:
                erreur("fork");
            case 0:
                execFils();
            default:
                //ici le pere
                break;
        }
    }

    // à partir d'ici il ne reste que le père
    for (int j = 0; j < N; ++j) {
        waitpid(pid[j], NULL, 0);
    }

    printf("Je suis ton père : tout va bien !\n");

    return EXIT_SUCCESS;
}
