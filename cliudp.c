#include "biblio.h"
#include <stdio.h>
#include <string.h>

int main()
{
    char response;

    unsigned short port = get_valid_port();
    getchar();
    emit_user(port);

    return 0;
}
