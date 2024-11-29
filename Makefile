# Makefile

CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -include src/pch.h
PCH = src/pch.h.gch

all: client server

$(PCH): src/pch.h
	$(CC) $(CFLAGS) -c src/pch.h

client: $(PCH) src/client.c
	$(CC) $(CFLAGS) -o client src/client.c

server: $(PCH) src/server.c
	$(CC) $(CFLAGS) -o server src/server.c

src/client.o: src/client.c
	$(CC) $(CFLAGS) -c src/client.c

src/server.o: src/server.c
	$(CC) $(CFLAGS) -c src/server.c

clean:
	rm -f client server $(PCH) src/*.o