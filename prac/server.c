#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>

#define MAXLINE 4096
#define SA struct sockaddr_in
#define PORT 12345

int main(int argc, char *argv[]){
    int n;
    int sockfd;
    int connfd;
    SA servaddr;
    uint8_t buff[MAXLINE+1];
    uint8_t recv_line[MAXLINE+1];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        perror("socket() failed.!");
        return EXIT_FAILURE;
    }

    bzero((struct sockaddr *)&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if( bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
        perror("bind() error.!");
        return EXIT_FAILURE;
    }

    if(listen(sockfd, 10) < 0){
        perror("listen() error.!");
        return EXIT_FAILURE;
    }

    for(;;){
        SA addr;
        socklen_t addr_len;

        printf("Waiting for connection on port %d \n",PORT);
        fflush(stdout);
        connfd = accept(sockfd, (struct sockaddr *) NULL, NULL);

        memset(recv_line, 0, MAXLINE);
        while( (n = read(connfd, recv_line, MAXLINE-1)) > 0){
            printf("%s",recv_line);

            if(recv_line[n-1] == '\n')
                break;
            memset(recv_line, 0, MAXLINE);
        }

        if(n<0){
            perror("Read() error..");
            return EXIT_FAILURE;
        }

        snprintf((char *)buff, sizeof(buff), "HTTP/1.1 200 OK\r\n\r\nHello World\n");
        write(connfd, (char *)buff, strlen((char *)buff));
        close(connfd);
    }

    return EXIT_SUCCESS;
}