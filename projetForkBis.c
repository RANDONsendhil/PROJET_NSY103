#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include "biblio.h"
#include <signal.h>
#define MAXMESS 1024

int main()
{
    int pere;
    int fils;
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
        emit_user_message_loop(port);
        exit(EXIT_SUCCESS);
        kill(getpid(), SIGSTOP);
         
    }
    else
    {
        // Père : récepteur
        printf("<%d>Je suis le père\n", getpid());
        char message[MAXMESS];
        while (1)
        {
            if (reception(port, message) == 0)
            {
                printf("<%d>Je suis le père: message réçu du fils,  <Message du fils: %s> \n", getpid(), message);
                kill(getpid(), SIGCONT);
            }
            else
            {
                printf(" Erreur de réception\n");
            }
        }
    }
    return 0;
}