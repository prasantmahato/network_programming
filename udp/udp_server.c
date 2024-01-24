// server program for udp connection
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 12345
#define MAXLINE 1000

// Driver code
int main()
{
    char buffer[100];
    // char *message = "Hello Client";
    int listenfd, len;
    struct sockaddr_in servaddr, cliaddr;
    bzero(&servaddr, sizeof(servaddr));

    // Create a UDP Socket
    listenfd = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
    servaddr.sin_family = AF_INET;

    // bind server address to socket descriptor
    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    do
    {
        // receive the datagram
        len = sizeof(cliaddr);
        int n = recvfrom(listenfd, buffer, sizeof(buffer),
                         0, (struct sockaddr *)&cliaddr, &len); // receive message from server
        buffer[n] = '\0';
        // puts(buffer);
        printf("Client : %s\n", buffer);

        if(strcmp(buffer, "Bye") == 0)
        {
            printf("Client Disconnected.\n");
            break;
        }

        char *message = (char *)malloc(100 * sizeof(char));
        printf("Message: ");
        scanf("%s", message);

        // send the response
        sendto(listenfd, message, MAXLINE, 0,
               (struct sockaddr *)&cliaddr, sizeof(cliaddr));
        free(message);
    } while (1);
}
