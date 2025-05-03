#include <stdio.h>
#include <stdlib.h>
#include "biblio.h"
#define MAXMESS 1024
int main( ) {
  
    char message[MAXMESS];
    unsigned short port = get_valid_port();
  
    printf("Waiting for UDP message on port %d...\n", port);
    if (reception(port, message) == 0) {
        printf("Received message: %s\n", message);
    } else {
        fprintf(stderr, "Failed to receive message.\n");
    }
    return 0;
   
}