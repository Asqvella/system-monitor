// Working with queries 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "metrics.h"
#include "file.h"
#include "header.h"

extern const int SIZE_BUFF;

char json_tmpl[] = "{\"time\":%d,\"traffic\":%d,\"ram\":%d,\"hdd\":%d,\"cpu\":%d,\"cpu_temp\":%d,\"hdd_temp\":%d,\"mb_temp\":%d}";

// Get data from client
void get_data(char *request, char *method, char *url) {
	char sep[] = " ";
   	char *istr;
	// get method
	istr = strtok(request, sep);
	strcat(method, istr);
	// get url
	istr = strtok(NULL, sep);
	strcat(url, istr);
}

// Send request
void send_reply(int client_fd, char* headers_buffer, char* content_buffer) {	
	int size = 0;
	size = strlen(headers_buffer) + strlen(content_buffer) + 1; // + "\0"
	char answer_buffer[size];
 	bzero(answer_buffer, sizeof(answer_buffer));
	sprintf(answer_buffer, "%s%s", headers_buffer, content_buffer);
	if (write(client_fd, answer_buffer, strlen(answer_buffer)) < 0) {
		printf("send_reply(write()) = fail");
	} 
}

// Serve metrics endpoint.
void serve_metrics(int client_fd, char *type) {
	char content_buffer[SIZE_BUFF];
	bzero(content_buffer, sizeof(content_buffer));

	points p;
	get_points(&p);
	sprintf(content_buffer, json_tmpl, p.time, p.traffic, p.ram, p.hdd, p.cpu, p.cpu_temp, p.hdd_temp, p.mb_temp);
	
	char headers_buffer[SIZE_BUFF];
	bzero(headers_buffer, sizeof(headers_buffer));

	int content_size = strlen(content_buffer);
	make_headers(type, headers_buffer, content_size);
	send_reply(client_fd, headers_buffer, content_buffer);
}

void serve_page(int client_fd, char *type, char *path) {
 	char headers_buffer[SIZE_BUFF];
 	bzero(headers_buffer, sizeof(headers_buffer));

	int content_size = get_file_size(path);

	char content_buffer[content_size];
 	bzero(content_buffer, sizeof(content_buffer));

	get_file_content(path, content_buffer, content_size);
	make_headers(type, headers_buffer, content_size);
	send_reply(client_fd, headers_buffer, content_buffer);
}
