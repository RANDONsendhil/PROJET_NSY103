#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include "biblio.h"
#define MAXMESS 100

/*******************************************************************
   Boucle d'attendre et de reception d'un message UDP

   -> En argument d'entree :
              - numero de Port d'écoute,
              - buffer message pour receptionner le message

   -> En argument de sortie :
               0 = OK et le buffer message en paramètre d'entrée
               contient le message
          -1 = faute

 Auteurs : Emile Geahchan
 version du 2/12/20
 *******************************************************************/

int reception(unsigned short port, char *message)
{
    int sock;
    struct sockaddr_in local, distant;
    socklen_t len = sizeof(distant);
    int n;

    // Création de la socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        perror("Erreur lors de la création de la socket :");
        return -1;
    }

    // Préparation de la structure d'adresse locale
    memset(&local, 0, sizeof(local));
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = INADDR_ANY;
    local.sin_port = htons(port);

    // Liaison de la socket au port
    if (bind(sock, (const struct sockaddr *)&local, sizeof(local)) < 0)
    {
        perror("Erreur lors du bind HERE recption:");
        close(sock);
        return -1;
    }

    n = recvfrom(sock, message, MAXMESS - 1, 0, (struct sockaddr *)&distant, &len);
    if (n <= 0)
    {
        perror("Erreur lors de la réception");
        close(sock);
        return -1;
    }

    message[n] = '\0'; // Terminer la chaîne
    // Afficher le message reçu (optionnel)
    printf("(Port: %d): Message reçu:  %s\n", port, message);

    // Fermeture de la socket
    close(sock);
    return 0;
}

/*******************************************************************
   Emission d'un message UDP

   -> En argument d'entree :
              - Adresse IP du serveur en notation décimale pointée
              - Port d'écoute du serveur
              - Message à envoyer

   -> En argument de sortie :
               0 = OK
          -1 = faute

 Auteurs : Emile Geahchan
 version du 2/12/20
 *******************************************************************/

int emission(char *ip, unsigned short port, char *message)
{
    int sock;
    struct sockaddr_in local, distant;
    struct in_addr addr;
    ssize_t sent_bytes;

    // Conversion de l'adresse IP
    if (inet_aton(ip, &addr) == 0)
    {
        fprintf(stderr, "Adresse IP invalide : %s\n", ip);
        fprintf(stderr, "Usage : client <IP> <Port> <message>\n");
        return -1;
    }

    // Création de la socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        perror("Erreur lors de la création de la socket :");
        return -1;
    }

    // Préparation de l'adresse locale
    memset(&local, 0, sizeof(local));
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = INADDR_ANY;
    local.sin_port = 0; // Laisser le système choisir le port

    if (bind(sock, (const struct sockaddr *)&local, sizeof(local)) < 0)
    {
        perror("Erreur lors du bind :");
        close(sock);
        return -1;
    }

    // Préparation de l'adresse distante (serveur)
    memset(&distant, 0, sizeof(distant));
    distant.sin_family = AF_INET;
    distant.sin_addr = addr;
    distant.sin_port = htons(port);

    // Envoi du message
    sent_bytes = sendto(sock, message, strlen(message), 0,
                        (const struct sockaddr *)&distant, sizeof(distant));
    if (sent_bytes < 0)
    {
        perror("Erreur lors de l'envoi du message :");
        close(sock);
        return -1;
    }

    close(sock);
    return 0;
}

// Fonction pour obtenir un numéro de port valide
unsigned short get_valid_port()
{
    unsigned short port;

    while (1)
    {
        printf("Entrez un numéro de port à 4 chiffres : ");

        // Vérifie si l'entrée est un nombre
        if (scanf("%hu", &port) != 1)
        {
            printf("Entrée invalide. Veuillez entrer un nombre.\n");
            while (getchar() != '\n')
                ; // Vider le tampon
            continue;
        }

        // Vérifie si le numéro de port est à 4 chiffres
        if (port >= 1000 && port <= 9999)
        {
            return port; // Port valide
        }
        else
        {
            printf("Le numéro de port doit être un nombre à 4 chiffres entre 1000 et 9999.\n");
        }
    }
}

int emit_user(int port)
{
    char input[100];

    while (1)
    {
        printf("Entrez un message (entrez un seul point \".\" pour quitter) :");
        printf("> ");
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("Erreur de lecture de l'entrée.\n");
            break;
        }

        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n')
        {
            input[len - 1] = '\0';
        }

        if (strlen(input) == 0)
        {
            continue;
        }

        if (strcmp(input, ".") == 0)
        {
            break;
        }

        printf("Vous avez entré : %s\n", input);

        if (emission("127.0.0.1", port, input) != 0)
        {
            printf("Message n'a pas été envoyé!!!\n");
        }
        else
        {
            printf("Message a été envoyé\n");
        }
    }
    printf("Fin de la lecture.\n");
}

void emit_user_message(int port)
{
    char input[100];

    printf("Entrez un message :");
    printf("> ");
    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        printf("Erreur de lecture de l'entrée.\n");
    }

    size_t len = strlen(input);
    if (len > 0 && input[len - 1] == '\n')
    {
        input[len - 1] = '\0';
    }

    printf("Vous avez entré : %s\n", input);

    if (emission("127.0.0.1", port, input) != 0)
    {
        printf("Message n'a pas été envoyé!!!\n");
    }
    else
    {
        printf("Message a été envoyé\n");
    }
}

void emit_user_message_loop(int port)
{   
    char input[100];
    while (1)
    {   
        printf("Entrez un message (entrez un seul point \".\" pour quitter) :");
        emit_user_message(port);
        if (strlen(input) == 0) continue;
        if (strcmp(input, ".") == 0) break;
    }
}