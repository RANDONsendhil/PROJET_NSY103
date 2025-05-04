#include <stddef.h>

int emission(char* ip, unsigned short port, char* message);
int reception(unsigned short port, char *message);
unsigned short get_valid_port();
void getInput(char *buffer, size_t size);
void input_user_message(int port);
void input_user_message_loop(int port);
void dispatch_message(int port, char *message);
