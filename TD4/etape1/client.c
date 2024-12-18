#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 6000
#define BUFFER_SIZE 1024

int sock;
struct sockaddr_in serverAddr;

void creerSocket()
{
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Erreur lors de la création du socket");
        exit(EXIT_FAILURE);
    }
}

void connexionAuServeur()
{
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Se connecter au serveur
    if (connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        perror("Erreur lors de la connexion");
        exit(EXIT_FAILURE);
    }

    printf("Connecté au serveur !\n");
}

void lireEtEnvoyerUnMessage(char message[])
{
    printf("> ");
    if (fgets(message, BUFFER_SIZE, stdin) != NULL)
    {
        // Envoyer un message au serveur
        send(sock, message, strlen(message), 0);
    }
}

int main(int argc,char* argv[])
{
    char message[BUFFER_SIZE];

    creerSocket();
    connexionAuServeur();

    while (1)
    {
        lireEtEnvoyerUnMessage(message);
    }
}