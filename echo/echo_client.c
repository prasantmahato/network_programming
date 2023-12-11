#include "../common.h"

int main(int argc, char *argv[]){

    if(argc != 3){
        fprintf(stderr, "Usage: %s <server_ip> <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int n;
    int sockfd;
    int send_bytes;
    char receive_line[MAXLINE] = {0};
    char send_line[MAXLINE] = {0};
    struct sockaddr_in servaddr;
    int PORT = atoi(argv[2]);

    

    // Create a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        perror("Error creating socket");
        return EXIT_FAILURE;
    }else{
        printf("Socket created with sockfd %d \n", sockfd);
    }

    // Initialize api for address
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);

    // convert server ip from text to binary
    if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0){
        perror("inet_pton error");
        return EXIT_FAILURE;
    }

    // Establish connection to the server
    if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ){
        perror("Connect error");
        return 0;
    }else{
        printf("Connection established..\n");
    }

    // Send get request
    sprintf(send_line, "GET / HTTP/1.1\r\n\r\n");
    send_bytes = strlen(send_line);

    if(write(sockfd, send_line, send_bytes) != send_bytes){
        perror("Write/Request error..");
        return EXIT_FAILURE;
    }


    // Read and display the server's response
    while ((n = recv(sockfd, receive_line, MAXLINE-1,0)) > 0) {
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

    // close socket
    // close(sockfd);
    return 0;
}