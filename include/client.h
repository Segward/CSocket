// client.h

void send_request(const char *request) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    // Creating socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return;
    }

    // Setting up the address structure
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Converting address from text to binary form
    if (inet_pton(AF_INET, HOST, &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        close(sock);
        return;
    }

    // Connecting to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        close(sock);
        return;
    }

    // Sending the request to the server
    send(sock, request, strlen(request), 0);

    // Reading the response from the server
    read(sock, buffer, 1024);
    printf("Server response: %s\n", buffer);

    // Closing the socket
    close(sock);
}
