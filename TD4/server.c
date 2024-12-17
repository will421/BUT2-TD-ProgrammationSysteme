#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 6000
#define BUFFER_SIZE 1024

// TIP : Utiliser perror à la place de printf permet d'avoir plus d'informations sur l'erreur

int server_fd;
struct sockaddr_in pointDeRencontreLocal;
struct sockaddr_in pointDistant;
int longueurAdresseDistante;

void creerSocketEcoute()
{
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Erreur lors de la création du socket");
        exit(EXIT_FAILURE);
    }
}

void assignerPort()
{
    // remplir la zone mémoire de l'adresse avec des 0
    memset(&pointDeRencontreLocal, 0x00, sizeof(pointDeRencontreLocal));
    // Mode TCP
    pointDeRencontreLocal.sin_family = AF_INET;
    // Ecoute sur toutes les interfaces
    pointDeRencontreLocal.sin_addr.s_addr = htonl(INADDR_ANY);
    // Sur le port 6000
    pointDeRencontreLocal.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&pointDeRencontreLocal, sizeof(pointDeRencontreLocal)) == -1)
    {
        perror("Erreur lors du bind");
        exit(EXIT_FAILURE);
    }
}

void ecouter()
{
    if (listen(server_fd, 3) == -1)
    {
        perror("Erreur lors du listen");
        exit(EXIT_FAILURE);
    }
    printf("Serveur en écoute sur le port %d...\n", PORT);
}

int accepterConnexion()
{
    int socket;
    // Accepter une connexion
    if ((socket = accept(server_fd, (struct sockaddr *)&pointDistant, (socklen_t *)&longueurAdresseDistante)) == -1)
    {
        perror("Erreur lors de l'acceptation");
        exit(EXIT_FAILURE);
    }
    printf("Client connecté !\n");
    return socket;
}

void traiterLeMessage(int socket, char buffer[])
{
    // Lire un message du client
    // BUFFER_SIZE - 1 pour laisser de l'espace pour le \0
    int bytes_read = recv(socket, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_read > 0)
    {
        // Ajout du \0 en fin de chaîne pour ne pas afficher plus du buffer que désiré
        buffer[bytes_read] = '\0';
        printf("Message reçu : %s", buffer);
    }
    else if (bytes_read == 0)
    {
        printf("Client déconnecté.\n");
        exit(EXIT_SUCCESS);
    }
    else
    {
        perror("Erreur lors de la réception du message");
    }
}

// Programme principale
int main(int argc, char *argv[])
{
    int fdSocketCommunication;
    // Initialise un buffer rempli de zero
    char buffer[BUFFER_SIZE] = {0};
    printf("Démarrage du serveur\n");

    creerSocketEcoute();
    assignerPort();
    ecouter();

    fdSocketCommunication = accepterConnexion();

    while (1)
    {
        traiterLeMessage(fdSocketCommunication, buffer);
    }
}