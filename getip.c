#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, char *argv[]){
    if(argc < 2){
        printf("Usage : %s <hostname>\n",argv[0]);
        return EXIT_FAILURE;
    }

    const char *hostname = argv[1];
    
    struct addrinfo hint;
    struct addrinfo *result;

    memset(&hint, 0, sizeof(hint));
    // hint.ai_family = AF_INET;   // IPv4
    // hint.ai_family = AF_INET6;   // IPv6
    hint.ai_family = AF_UNSPEC;   // Unspecified, get whatever is available
    hint.ai_socktype = SOCK_STREAM; // TCP connection


    int status = getaddrinfo(hostname, NULL, &hint, &result);
    if(status){
        printf("getaddrinfor failed!");
        return EXIT_FAILURE;
    }

    struct addrinfo *tmp = result;
    while(tmp){
        printf("Entry:\n");
        printf("\tType: %i\n", tmp->ai_socktype);
        printf("\tFamily: %i\n", tmp->ai_family);

        char address_string[INET6_ADDRSTRLEN];  // longest address string possible
        void *addr;
        if(tmp->ai_family == AF_INET){  
            // v4 
            addr = &((struct sockaddr_in *)tmp->ai_addr)->sin_addr;
        }else{
            // v6
            addr = &((struct sockaddr_in6 *)tmp->ai_addr)->sin6_addr;
        }
        // network to printable
        inet_ntop(tmp->ai_family,addr, address_string, INET6_ADDRSTRLEN);  

        printf("\tAddress: %s\n", address_string);
        tmp = tmp->ai_next;
    }

    freeaddrinfo(result);
    return EXIT_SUCCESS;
}