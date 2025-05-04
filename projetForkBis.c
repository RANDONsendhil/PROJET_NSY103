#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sched.h>
#include "biblio.h"
#include <signal.h>
#include <sys/types.h>
#define MAXMESS 1024

int main()
{
    int fils;
    unsigned short port = 8000;
    char message[MAXMESS];
    fils = fork();
    char input[100];
    
     
    if (fils < 0)
    {
        perror("Erreur fork");
        exit(1);
    }
    else if (fils == 0)
    {
        // Fils:  émetteur
        printf("%d : Je suis le fils\n", getpid());

        while (1) {
            printf("<%d> : Veuillez saisir un message\n", getpid());
            fgets(message, MAXMESS, stdin);
            message[strcspn(message, "\n")] = 0;

            if (emission("127.0.0.1", port, message) != 0) {
                fprintf(stderr, "Erreur d’émission.\n");
            }
            kill(getpid(), SIGSTOP);
        }
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
                kill(fils, SIGCONT);
            }
            else
            {
                printf(" Erreur de réception\n");
            }
            usleep(100000);
        }
    }
    return 0;
}