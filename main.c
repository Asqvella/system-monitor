// Central application management
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <pthread.h>
#include "server.h"
#include "metrics.h"

const int LISTEN_PORT = 8080;
const int SIZE_BUFF = 1024;

// Working HTTP web-server
void* serving(void* arg) {
	int server_fd = start_server(LISTEN_PORT);
	while(1) {
		int client_fd = accept(server_fd, 0, 0);
		if (client_fd < 0) {
			printf("server: accept() = fail\n");
		}
		process(client_fd);
		if (close(client_fd) < 0) {
			printf("server: close(client_fd) = fail\n");
		}
	}
	stop_server(server_fd);
	return NULL;
}

// Writing data to database
void* collecting(void* arg) {
	while(1) {
		points p;
		get_points(&p);
		add_points_to_db(&p);
		sleep(1);
	}
	return NULL;
}

// Checking max value and alerting
void* checking(void* arg) {
	while(1) {
		points p;
		get_points(&p);
		check_and_alert(&p);
		sleep(50);
	}
	return NULL;
}

int main(void) {
	pthread_t server;
	pthread_t collector;
	pthread_t checker;

	pthread_create(&server, NULL, serving, NULL);
	pthread_create(&collector, NULL, collecting, NULL);
	pthread_create(&checker, NULL, checking, NULL);

	pthread_join(server, NULL);
	pthread_join(collector, NULL);
	pthread_join(checker, NULL);
  	return 0;
}
