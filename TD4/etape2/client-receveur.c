#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 6000
#define BUFFER_SIZE 1024

int sock;
struct sockaddr_in serverAddr;
char buffer[BUFFER_SIZE];


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

void envoyerRole() {
    char * role = "receveur";
    if(send(sock, role, strlen(role), 0) == -1) {
        perror("Erreur à l'envoi du rôle");
    }
    printf("Role envoyé\n");
}

void recevoirEtAfficherUnMessage()
{
    int bytes_read = recv(sock, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_read > 0)
    {
        // Ajout du \0 en fin de chaîne pour ne pas afficher plus du buffer que désiré
        buffer[bytes_read] = '\0';
        printf("Message reçu : %s", buffer);
    }
    else if (bytes_read == 0)
    {
        printf("Serveur déconnecté.\n");
        close(sock);
        exit(EXIT_SUCCESS);
    }
    else
    {
        perror("Erreur lors de la réception du message");
        close(sock);
        exit(EXIT_FAILURE);
    }
}

int main(int argc,char* argv[])
{
    creerSocket();
    connexionAuServeur();

    envoyerRole();
    while (1)
    {
        recevoirEtAfficherUnMessage();
    }
}