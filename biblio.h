int emission(char* ip, unsigned short port, char* message);
int reception(unsigned short port, char *message);
unsigned short get_valid_port();
int emit_user(int port);
void emit_user_message(int port);
void emit_user_message_loop(int port);

