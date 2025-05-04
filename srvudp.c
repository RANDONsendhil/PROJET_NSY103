#include <stdio.h>
#include <stdlib.h>
#include "biblio.h"
#define MAXMESS 1024
int main()
{
    char message[MAXMESS];

    unsigned short port = get_valid_port();

    printf("Le serveur UDP en attente d'un message sur le port: <%d>\n", port);
    while (1)
    {
        if (reception(port, message) == 0)
        {
            printf("Message reçu côté serveur: %s\n", message);
        }
        else
        {
            fprintf(stderr, "Erreur à la réception de message\n");
        }
    }
    return 0;
}