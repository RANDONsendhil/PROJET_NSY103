#include <stdio.h>
#include <stdlib.h>
#include "biblio.h"
#define MAXMESS 1024
int main()
{
    char message[MAXMESS];

    // Récupération d'un port valide sur lequel le serveur va écouter
    unsigned short port = get_valid_port();

    printf("Le serveur UDP en attente d'un message sur le port: <%d>\n", port);

    // Boucle infinie pour écouter en permanence les messages entrants
    while (1)
    {
        // Appel de la fonction reception pour recevoir un message sur le port spécifié
        // Si la réception est un succès (renvoie 0), on affiche le message reçu
        if (reception(port, message) == 0)
        {
            printf("Message reçu côté serveur: %s\n", message);
        }
        else
        {
            // En cas d'échec de la réception, afficher une erreur sur stderr
            fprintf(stderr, "Erreur à la réception de message\n");
        }
    }
    return 0;
}