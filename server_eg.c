#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#define MAXLINE 1024

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <server_IP>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Create a socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error creating socket");
        return EXIT_FAILURE;
    }

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;   // IPv4
    servaddr.sin_port = htons(5500);  // Daytime server port

    // Convert server IP address from text to binary
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0) {
        perror("inet_pton error");
        return EXIT_FAILURE;
    }

    // Establish connection to the server
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("connect error");
        return EXIT_FAILURE;
    }

    char receive_line[MAXLINE];
    int n;

    // Read and display the server's response
    while ((n = read(sockfd, receive_line, MAXLINE)) > 0) {
        receive_line[n] = 0;  // Null-terminate the received data
        if (fputs(receive_line, stdout) == EOF) {
            perror("fputs error");
            return EXIT_FAILURE;
        }
    }

    if (n < 0) {
        perror("read error");
        return EXIT_FAILURE;
    }

    // Close the socket and exit
    // close(sockfd);
    return EXIT_SUCCESS;
}


/*
    int Socket(int fam, int type, int protocol){
        int n = socket(fam, type, protocol);
        if(n < 0)   
            err_sys("socket error");
        return n;
    }
*/