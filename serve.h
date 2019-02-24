// Working with queries
void get_data(char *request, char *method, char *url);
void serve_page(int client_fd, char *type, char *path);
void serve_metrics(int client_fd, char *type);
