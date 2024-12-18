#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>

#define PORT 6000
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 5
#define MAX_NAME_LENGTH 11

// TIP : Utiliser perror à la place de printf permet d'avoir plus d'informations sur l'erreur

typedef struct client
{
    int socket;
    int id;
} client_t;

int server_fd;
struct sockaddr_in pointDeRencontreLocal;
struct sockaddr_in pointDistant;
int longueurAdresseDistante;
client_t clients[MAX_CLIENTS];
pthread_t thread_id;

void initialiserClients()
{

    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        clients[i].socket = 0;
    }
}

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

int recevoirLeMessage(client_t *client, char buffer[])
{
    int socket = client->socket;
    // Lire un message du client
    // BUFFER_SIZE - 1 pour laisser de l'espace pour le \0
    int bytes_read = recv(socket, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_read > 0)
    {
        // Ajout du \0 en fin de chaîne pour ne pas afficher plus du buffer que désiré
        buffer[bytes_read] = '\0';
        printf("[%d] Message reçu : %s", client->id, buffer);
        return 0;
    }
    else if (bytes_read == 0)
    {
        printf("[%d] Client déconnecté.\n", client->id);
        close(socket);
        client->socket = 0;
        return -1;
    }
    else
    {
        perror("Erreur lors de la réception du message");
        close(socket);
        client->socket = 0;
        return -1;
    }
}

void *threadCommunication(void *arg)
{
    char buffer[BUFFER_SIZE] = {0};
    client_t *client = (client_t *)arg;
    while (1)
    {
        if (recevoirLeMessage(client, buffer) == -1)
        {
            return NULL;
        };
    }
}

void lancerThread(client_t *client)
{
    if (pthread_create(&thread_id, NULL, threadCommunication, client) != 0)
    {
        perror("erreur de creation du thread");
        exit(EXIT_FAILURE);
    }
    // Pour que le systeme nettoie le thread sans appel à pthread_join
    pthread_detach(thread_id);
}

// Programme principale
int main(int argc, char *argv[])
{
    int fdSocketCommunication;
    pthread_t thread_id;
    // Initialise un buffer rempli de zero
    char buffer[BUFFER_SIZE] = {0};
    printf("Démarrage du serveur\n");

    initialiserClients();
    creerSocketEcoute();
    assignerPort();
    ecouter();

    while (1)
    {
        fdSocketCommunication = accepterConnexion();

        for (int i = 0; i < MAX_CLIENTS; i++)
        {
            if (clients[i].socket == 0)
            {
                clients[i].socket = fdSocketCommunication;
                clients[i].id = i;
                lancerThread(&(clients[i]));
                break;
            }
        }
    }
}