// Working with metric
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sqlite3.h>
#include <curl/curl.h> 
#include "metrics.h"

extern const int SIZE_BUFF;

char name_db[] = "my_db.db";
sqlite3 *db;
char sql_query[] = "CREATE TABLE IF NOT EXISTS points(time INT NOT NULL, traffic INT NOT NULL, ram INT NOT NULL, hdd INT NOT NULL, cpu INT NOT NULL, cpu_temp INT NOT NULL, hdd_temp INT NOT NULL, mb_temp INT NOT NULL);";
char insert_request_tmpl[] = "INSERT INTO points VALUES(%d, %d, %d, %d, %d, %d, %d, %d);";

int max_value = your_number;
char URL[] = "your_url";
char USERPWD[] = "your_userpwd";
char POSTFIELDS[] = "your_postfields";

void get_points(points *p) {
	char buffer[SIZE_BUFF];
	FILE *ptr;

	ptr = popen("./script.sh", "r");
	if (!ptr) 
	{
		printf("popen() = fail!\n");
	}
	fgets(buffer, SIZE_BUFF, ptr);
	pclose(ptr);

	char *istr;
	char sep[] = " ";

	istr = strtok(buffer, sep);
	int time = atoi(istr);
	p->time = time;

	istr = strtok(NULL, sep);
	int traffic = atoi(istr);
	p->traffic = traffic;

	istr = strtok(NULL, sep);
	int ram = atoi(istr);
	p->ram = ram;

	istr = strtok(NULL, sep);
	int hdd = atoi(istr);
	p->hdd = hdd;

	istr = strtok(NULL, sep);
	int cpu = atoi(istr);
	p->cpu = cpu;

	istr = strtok(NULL, sep);
	int cpu_temp = atoi(istr);
	p->cpu_temp = cpu_temp;

	istr = strtok(NULL, sep);
	int hdd_temp = atoi(istr);
	p->hdd_temp = hdd_temp;	
	
	istr = strtok(NULL, sep);
	int mb_temp = atoi(istr);
	p->mb_temp = mb_temp;	
}

void add_points_to_db(points *p) {
	// rc - return code
	int rc = sqlite3_open(name_db, &db); 
	if (rc != SQLITE_OK) {
		printf("add_points_to_db(open(open or create db)) = fail\n");
	}	
	// execute query
	rc = sqlite3_exec(db, sql_query, 0, 0, 0); 
	if (rc != SQLITE_OK) { 
		printf("add_points_to_db(sql_exec(create table if no exists)) = fail\n");
	}
	char insert_request[SIZE_BUFF];
	bzero(insert_request, sizeof(insert_request));
	// glue string with point`s values
	sprintf(insert_request, insert_request_tmpl, p->time, p->traffic, p->ram, p->hdd, p->cpu, p->cpu_temp, p->hdd_temp, p->mb_temp);
	// execute query
	rc = sqlite3_exec(db, insert_request, 0, 0, 0); 
	if (rc != SQLITE_OK) {
		printf("add_points_to_db(sql_exec(insert request)) = fail\n"); 
	}
	sqlite3_close(db);
}

void check_and_alert(points *p) {
	if (p->ram >= max_value || p->hdd >= max_value || p->cpu >= max_value || p->traffic >= max_value || p->cpu_temp >= max_value || p->hdd_temp >= max_value || p->mb_temp >= max_value) {
		CURL *curl;
		CURLcode res;
		curl = curl_easy_init();
		if (curl) { 
			curl_easy_setopt(curl, CURLOPT_URL, URL);
			curl_easy_setopt(curl, CURLOPT_USERPWD, USERPWD);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, POSTFIELDS);
			res = curl_easy_perform(curl);
			if (res != CURLE_OK) {
				printf("check_and_alert(curl_easy_perform()) = fail\n");
			}
			printf("\n");
			curl_easy_cleanup(curl);
		}
	}
}
