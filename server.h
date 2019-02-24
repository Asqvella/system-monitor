// HTTP Server Interface
int start_server(int port);
void stop_server(int server_fd);
void process(int client_fd);
