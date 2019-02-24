main: 
	gcc main.c metrics.c server.c serve.c file.c header.c -lpthread -lsqlite3 -lcurl

clean: 
	rm a.out

