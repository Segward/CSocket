// server.c

#include "pch.h"
#include "server.h"

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Setting up the address structure
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);

    // Converting address from text to binary form
    if (inet_pton(AF_INET, HOST, &address.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Binding the socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listening for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Accepting an incoming connection
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            close(server_fd);
            exit(EXIT_FAILURE);
        }

        // Handling the request
        handle_request(new_socket);

        // Closing the socket
        close(new_socket);
    }

    close(server_fd);
    return 0;
}