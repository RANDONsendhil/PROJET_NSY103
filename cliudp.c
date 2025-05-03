#include "biblio.h"
#include <stdio.h>
#include <string.h>

int main()
{
    char response;

    char input[100];

    unsigned short port = get_valid_port();
    while (1)
    {   
        printf("Entrez un message (entrez un seul point \".\" pour quitter) :\n");
        printf("> ");
       
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Erreur de lecture de l'entrée.\n");
            break;
        }
   
        size_t len = strlen(input);
        if (len > 0 && input[len - 1] == '\n') {
            input[len - 1] = '\0';
        }
     
        if (strlen(input) == 0) {
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

    return 0;
}
