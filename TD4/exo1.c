#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define TAILLE 4

void *afficherTableau(char *source, int *tableau)
{
    printf("%s :%d %d %d %d\n", source, tableau[0], tableau[1], tableau[2], tableau[3]);
}

void *ajouter4(void *arg)
{
    int *tableau = (int *)arg;
    for (int i = 0; i < TAILLE; i++)
    {
        tableau[i] += 4;
        sleep(1);
    }
    afficherTableau("ajouter4", tableau);
    pthread_exit(NULL);
}

void *diviser2(void *arg)
{
    int *tableau = (int *)arg;
    for (int i = 0; i < TAILLE; i++)
    {
        tableau[i] /= 2;
        sleep(1);
    }
    afficherTableau("diviser2", tableau);
    pthread_exit(NULL);
}

void *multiplier4(void *arg)
{
    int *tableau = (int *)arg;
    for (int i = 0; i < TAILLE; i++)
    {
        tableau[i] *= 4;
        sleep(1);
    }
    afficherTableau("multiplier4", tableau);
    pthread_exit(NULL);
}

void *soustraire5(void *arg)
{
    int *tableau = (int *)arg;
    for (int i = 0; i < TAILLE; i++)
    {
        tableau[i] -= 5;
        sleep(1);
    }
    afficherTableau("soustraire5", tableau);
    pthread_exit(NULL);
}

int main()
{
    int tableau[TAILLE] = {0};
    pthread_t threadAddition;
    pthread_t threadDivision;
    pthread_t threadMultiplication;
    pthread_t threadSoustraction;

    afficherTableau("Tableau initial", tableau);

    if (pthread_create(&threadAddition, NULL, ajouter4, tableau) != 0)
    {
        perror("erreur de creation de threadAddition");
        return EXIT_FAILURE;
    }
    printf("Creation de threadAddition ok\n");

    if (pthread_create(&threadDivision, NULL, diviser2, tableau) != 0)
    {
        perror("erreur de creation de threadDivision");
        return EXIT_FAILURE;
    }
    printf("Creation de threadDivision ok\n");

    if (pthread_create(&threadMultiplication, NULL, multiplier4, tableau) != 0)
    {
        perror("erreur de creation de threadMultiplication");
        return EXIT_FAILURE;
    }
    printf("Creation de threadMultiplication ok\n");

    if (pthread_create(&threadSoustraction, NULL, soustraire5, tableau) != 0)
    {
        perror("erreur de creation de threadSoustraction");
        return EXIT_FAILURE;
    }
    printf("Creation de threadSoustraction ok\n");

    pthread_join(threadAddition, NULL);
    pthread_join(threadDivision, NULL);
    pthread_join(threadMultiplication, NULL);
    pthread_join(threadSoustraction, NULL);

    afficherTableau("Tableau final", tableau);
}
