#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main()
{
    int client_socket;
    struct sockaddr_in server_address;
    char buffer[BUFFER_SIZE];

    // Create socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    // Prepare the sockaddr_in structure
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8888);
    server_address.sin_addr.s_addr = INADDR_ANY;
    

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("Failed to connect");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server\n");

    // Send and receive data
    while (1)
    {
        printf("Enter message (or 'q' to quit): ");
        fgets(buffer, BUFFER_SIZE, stdin);

        if (strcmp(buffer, "q\n") == 0)
            break;

        // Send message to server
        if (send(client_socket, buffer, strlen(buffer), 0) < 0)
        {
            perror("Failed to send");
            exit(EXIT_FAILURE);
        }

        // Receive message from server
        memset(buffer, 0, BUFFER_SIZE);
        if (recv(client_socket, buffer, BUFFER_SIZE, 0) < 0)
        {
            perror("Failed to receive");
            exit(EXIT_FAILURE);
        }

        printf("Server response: %s", buffer);
    }

    // Close the socket
    close(client_socket);

    return 0;
}
