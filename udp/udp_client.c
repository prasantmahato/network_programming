// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 12345
#define MAXLINE 1024
#define MSG_CONFIRM 0

// Driver code
int main(int argc, char *argv[])
{

	if (argc != 2)
	{
		printf("Usage: %s <server_ip>\n", argv[0]);
		return 1;
	}

	int sockfd;
	char buffer[MAXLINE];

	struct sockaddr_in servaddr;

	// Creating socket file descriptor
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));

	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;

	int n;
	do
	{
		char *hello = (char *)malloc(100 * sizeof(char));
		printf("Message: ");
		scanf("%s", hello);
		socklen_t len = sizeof(servaddr);
		sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));
		n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *)&servaddr, &len);
		buffer[n] = '\0';
		printf("Server : %s\n", buffer);
		free(hello);
	} while (1);

	close(sockfd);
	return 0;
}
