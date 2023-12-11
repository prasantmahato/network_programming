#include "../common.h"

int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int n;
    int sockfd;
    int connfd;
    SA servaddr, clientaddr;
    uint8_t buff[MAXLINE+1], recv_line[MAXLINE+1];
    pid_t pid;  // process id from fork()
    unsigned int childProcCount = 0;
    int PORT = atoi(argv[1]);


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
        int len = sizeof(clientaddr);
        printf("Waiting for connection on port %d \n",PORT);
        fflush(stdout);
        connfd = accept(sockfd, (struct sockaddr *)&clientaddr, &len);

        char * client_ip = inet_ntoa(clientaddr.sin_addr);
        printf("Accepted new connection from a client %s:%d\n", client_ip, ntohs(clientaddr.sin_port));

        if((pid = fork()) < 0){
            perror("fork() error.!");
            return EXIT_FAILURE;
        }
        else if(pid == 0){  // Child process
            close(sockfd);  // child closes listening socket

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

        }

        snprintf((char *)buff, sizeof(buff), "HTTP/1.1 200 OK\r\n\r\nHello World\n");
        write(connfd, (char *)buff, strlen((char *)buff));
        close(connfd);
        childProcCount++;

        // Handle zombiee process
        while (childProcCount)
        {
            pid = waitpid((pid_t)-1, NULL, WNOHANG);
            if(pid < 0) return EXIT_FAILURE;
            else if(pid == 0)   break;
            else    childProcCount--;

        }
        
    }

    return EXIT_SUCCESS;
}