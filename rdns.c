#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>

int main() {
    char ip_address[INET6_ADDRSTRLEN];

    // Input the IP address
    printf("Enter IP address: ");
    scanf("%s", ip_address);

    struct sockaddr_in sa;
    struct sockaddr_in6 sa6;
    void *addr = NULL;

    // Try to parse input as both IPv4 and IPv6
    if (inet_pton(AF_INET, ip_address, &(sa.sin_addr)) == 1) {
        addr = &(sa.sin_addr);
    } else if (inet_pton(AF_INET6, ip_address, &(sa6.sin6_addr)) == 1) {
        addr = &(sa6.sin6_addr);
    } else {
        printf("Invalid IP address format.\n");
        return EXIT_FAILURE;
    }

    if (addr != NULL) {
        char host_buffer[NI_MAXHOST];

        // Create a sockaddr structure based on the address family
        struct sockaddr_storage sa_storage;
        if (sa.sin_addr.s_addr != 0) {
            sa_storage.ss_family = AF_INET;
            ((struct sockaddr_in *)&sa_storage)->sin_addr = sa.sin_addr;
        } else {
            sa_storage.ss_family = AF_INET6;
            ((struct sockaddr_in6 *)&sa_storage)->sin6_addr = sa6.sin6_addr;
        }

        // Get the host name
        int status = getnameinfo((struct sockaddr *)&sa_storage, sizeof(sa_storage), host_buffer, NI_MAXHOST, NULL, 0, 0);
        if (status == 0) {
            printf("Host: %s\n", host_buffer);
        } else {
            fprintf(stderr, "getnameinfo failed: %s\n", gai_strerror(status));
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}
