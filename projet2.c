#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include "biblio.h"
#include <signal.h>
#define MAXMESS 1024

int main()
{
    int pere; // PID du processus père
    int fils; // PID retourné par fork() pour le processus fils
    unsigned short port = 12345;

    pere = getpid();
    fils = fork();
    char input[100];
    // PERE

    if (fils < 0)
    {
        perror("Erreur fork");
        exit(1);
    }
    else if (fils == 0)
    {
        // Fils émetteur
        printf("<%d>Je suis le fils\n", getpid());

        // Appel d'une fonction qui permet au fils d'envoyer un message à travers le port
        input_user_message(port);
        exit(EXIT_SUCCESS);
    }
    else
    {
        // Père : récepteur
        printf("<%d>Je suis le père\n", getpid());
        char message[MAXMESS];

        // Le père attend un message envoyé sur le port défini
        reception(port, message);
        printf("<%d>Je suis le père: message réçu du fils,  <Message du fils: %s> \n", getpid(), message);
    }
    return 0;
}