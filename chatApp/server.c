#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

int clients[MAX_CLIENTS];
int client_count = 0;

void broadcast(char *message, int sender) {
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (clients[i] != 0 && i != sender) {
            send(clients[i], message, strlen(message), 0);
        }
    }
}

int main() {
    int server_socket, new_socket;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];
    
    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Set up server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind socket to address
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    listen(server_socket, MAX_CLIENTS);

    printf("Server listening on port %d...\n", PORT);

    while (1) {
        socklen_t client_size = sizeof(client_addr);
        new_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_size);

        // Add new client to the array
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (clients[i] == 0) {
                clients[i] = new_socket;
                client_count++;
                break;
            }
        }

        // Create a new process for handling the client
        if (fork() == 0) {
            close(server_socket);  // Child process doesn't need the listener

            while (1) {
                memset(buffer, 0, sizeof(buffer));
                recv(new_socket, buffer, sizeof(buffer), 0);

                if (strcmp(buffer, "exit") == 0) {
                    printf("Client disconnected\n");
                    break;
                }

                printf("Client: %s", buffer);
                broadcast(buffer, client_count);
            }

            // Remove the client from the array
            for (int i = 0; i < MAX_CLIENTS; i++) {
                if (clients[i] == new_socket) {
                    clients[i] = 0;
                    client_count--;
                    break;
                }
            }

            close(new_socket);
            exit(0);
        } else {
            close(new_socket);  // Parent process doesn't need the accepted socket
        }
    }

    return 0;
}
