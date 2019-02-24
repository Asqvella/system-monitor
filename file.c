// Working with file
#include <stdio.h> 
#include <fcntl.h>
#include <unistd.h>

int get_file_size(char* path) {
	int content_size = 0;
	FILE* file = fopen(path, "r");
	if (file < 0) {
		printf("get_file_size(fopen()) = fail");
	}
 	while (fgetc(file) != EOF) {
		++content_size;
	}
 	fclose(file);
	return content_size;
}

void get_file_content(char* path, char* content, int content_size) {
	int content_fd = open(path, O_RDONLY);
	if (content_fd < 0) {
		printf("get_file_content(open()) = fail");
	}
	read(content_fd, content, content_size);
	close(content_fd);
}
