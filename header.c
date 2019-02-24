// Creating headers
#include <string.h>
#include <stdio.h>

extern const int SIZE_BUFF;
char status_code_200[] = "200 OK";
char status_code_404[] = "404 Not Found";
char starting_header_tmpl[] = "HTTP/1.1 %s";
char content_type_tmpl[] = "Content-Type: %s";
char content_lenth_tmpl[] = "Content-Length: %d";
char connection[] = "Connection: close";
char headers_tmpl[] = "%s\r\n%s\r\n%s\r\n%s\r\n\r\n";

void make_headers(char* type, char* headers_buffer, int content_size) {
	char starting_header[SIZE_BUFF];
	bzero(starting_header, sizeof(starting_header));
	char content_type[SIZE_BUFF];
	bzero(content_type, sizeof(content_type));
	char content_lenth[SIZE_BUFF];
	bzero(content_lenth, sizeof(content_lenth));
	
	sprintf(content_type, content_type_tmpl, type);
	sprintf(content_lenth, content_lenth_tmpl, content_size);
	
	if (strncmp(type,"404\0",4) == 0) {
		sprintf(starting_header, starting_header_tmpl, status_code_404);
	}
	else {
		sprintf(starting_header, starting_header_tmpl, status_code_200);	
	}	
	sprintf(headers_buffer, headers_tmpl, starting_header, content_type, content_lenth, connection);	
}
