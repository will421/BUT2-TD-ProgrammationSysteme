#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define TAILLE 4

typedef struct data
{
    int valeur;
    pthread_mutex_t mutex;
} data;

void initialiserTableau(data *tableau)
{
    for (int i = 0; i < TAILLE; i++)
    {
        tableau[i].valeur = 0;
        pthread_mutex_init(&(tableau[i].mutex), NULL);
    }
}

void *afficherTableau(char *source, data *tableau)
{
    printf("%s :%d %d %d %d\n", source, tableau[0].valeur, tableau[1].valeur, tableau[2].valeur, tableau[3].valeur);
}

void *ajouter4(void *arg)
{
    data *tableau = (data *)arg;
    for (int i = 0; i < TAILLE; i++)
    {
        pthread_mutex_lock(&(tableau[i].mutex));
        tableau[i].valeur += 4;
        sleep(1);
        pthread_mutex_unlock(&(tableau[i].mutex));
    }
    afficherTableau("ajouter4", tableau);
    pthread_exit(NULL);
}

void *diviser2(void *arg)
{
    data *tableau = (data *)arg;
    for (int i = 0; i < TAILLE; i++)
    {
        pthread_mutex_lock(&(tableau[i].mutex));
        tableau[i].valeur /= 2;
        sleep(1);
        pthread_mutex_unlock(&(tableau[i].mutex));
    }
    afficherTableau("diviser2", tableau);
    pthread_exit(NULL);
}

void *multiplier4(void *arg)
{
    data *tableau = (data *)arg;
    for (int i = 0; i < TAILLE; i++)
    {
        pthread_mutex_lock(&(tableau[i].mutex));
        tableau[i].valeur *= 4;
        sleep(1);
        pthread_mutex_unlock(&(tableau[i].mutex));
    }
    afficherTableau("multiplier4", tableau);
    pthread_exit(NULL);
}

void *soustraire5(void *arg)
{
    data *tableau = (data *)arg;
    for (int i = 0; i < TAILLE; i++)
    {
        pthread_mutex_lock(&(tableau[i].mutex));
        tableau[i].valeur -= 5;
        sleep(1);
        pthread_mutex_unlock(&(tableau[i].mutex));
    }
    afficherTableau("soustraire5", tableau);
    pthread_exit(NULL);
}

int main()
{
    data tableau[TAILLE];
    pthread_t threadAddition;
    pthread_t threadDivision;
    pthread_t threadMultiplication;
    pthread_t threadSoustraction;

    initialiserTableau(tableau);
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
