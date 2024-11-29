// client.c

#include "pch.h"
#include "client.h"

int main() {
    char args[1024];
    char request[4096];
    while (1) {
        printf("Enter a message to send to the server: ");
        if (fgets(args, sizeof(args), stdin) == NULL) {
            fprintf(stderr, "Error reading input\n");
            break;
        }

        snprintf(request, sizeof(request), "POST /message?arg=%s\n", args);
        send_request(request);
    }

    return 0;
}