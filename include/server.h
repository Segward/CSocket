// server.h

void handle_post_message(int socket, char* args) {
    char* response = "Message received";
    printf("POST /message args: %s\n", args);
    write(socket, response, strlen(response));
}

void handle_request(int socket) {
    char buffer[1024] = {0};
    read(socket, buffer, 1024);

    // Extracting the argument from the request
    char* args = strstr(buffer, "?arg=");
    char* argsdup;
    if (args != NULL) {
        char* arg = args + strlen("?arg=");
        char* end = strchr(arg, '\n');
        argsdup = strndup(arg, end - arg);
    }
    
    // Handling the request
    if (strncmp(buffer, POST_MESSAGE, strlen(POST_MESSAGE)) == 0) {
        handle_post_message(socket, argsdup);
    }
}