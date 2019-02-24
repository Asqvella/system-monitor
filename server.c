// HTTP Server Interface
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include "serve.h"

extern const int SIZE_BUFF;

char html[] = "text/html";
char json[] = "application/json";
char js[] = "text/javascript";

char index_path[] = "static/index.html";
char nf404_path[] = "static/404.html";
char jquery_path[] = "static/jquery.js";
char canvas_path[] = "static/canvas.js";

// Starts server on a given port.
int start_server(int port) {
	struct sockaddr_in svr_addr;

	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0) {
		printf("start_server(socket()) = fail\n");
	}

	svr_addr.sin_family = AF_INET;
	svr_addr.sin_addr.s_addr = INADDR_ANY;
	svr_addr.sin_port = htons(port);

	if (bind(server_fd, (struct sockaddr *) &svr_addr, sizeof(svr_addr)) < 0) {
		printf("start_server(bind()) = fail\n");
	}
	if (listen(server_fd, 1) < 0) {
		printf("start_server(listen()) = fail\n");
	} 

	return server_fd;
}

void stop_server(int server_fd) {
	if (close(server_fd) < 0) {
		printf("stop_server(close()) = fail\n");
	}
}

// Process an HTTP session for a given client.
void process(int client_fd) {
 	char request[SIZE_BUFF];
 	bzero(request, sizeof(request));
	recv(client_fd, request, sizeof(request), 0);
	
	char url[SIZE_BUFF];
	bzero(url, sizeof(url));
	char method[SIZE_BUFF];
	bzero(method, sizeof(method));
	get_data(request, method, url);

	// request verification
	if (strncmp(method, "GET\0", 4) == 0) {
 		if (strncmp(url, "/\0", 2) == 0) {
 			serve_page(client_fd, html, index_path);
 		}
 		else if (strncmp(url, "/json\0", 6) == 0) {
 			serve_metrics(client_fd, json);
  		}
		else if (strncmp(url, "/jquery.js\0", 11) == 0) {
 			serve_page(client_fd, js, jquery_path);
  		}
		else if (strncmp(url, "/canvas.js\0", 11) == 0) {
 			serve_page(client_fd, js, canvas_path);
  		}
		else {
 			serve_page(client_fd, html, nf404_path);	
  		}
  	}
	else {
		printf("process(unknown method)\n");
	}
}
