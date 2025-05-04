#include "biblio.h"
#include <stdio.h>
#include <string.h>

int main()
{
    char response;

    unsigned short port = get_valid_port();
    getchar();
    input_user_message_loop(port);
    return 0;
}
