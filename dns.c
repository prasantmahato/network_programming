#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>

void performDNS(const char *host_or_ip);
void performReverseDNS(const char *host_or_ip);

int main()
{
    while (1)
    {
        printf("\n0. Exit");
        printf("\n1. DNS Lookup");
        printf("\n2. Reverse DNS Lookup");
        printf("\nChoose an option: ");

        int choice;
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            char host_or_ip[256];
            printf("\nEnter hostname or IP address: ");
            scanf("%s", host_or_ip);
            performDNS(host_or_ip);
            break;
        }
        case 2:
        {
            char host_or_ip[256];
            printf("\nEnter IP address: ");
            scanf("%s", host_or_ip);
            performReverseDNS(host_or_ip);
            break;
        }
        case 0:
            printf("\nExiting...\n");
            return EXIT_SUCCESS;
        default:
            printf("\nInvalid choice. Please choose a valid option.\n");
        }
    }
}

void performDNS(const char *host_or_ip)
{
    struct addrinfo hint;
    struct addrinfo *result;

    memset(&hint, 0, sizeof(hint));
    hint.ai_family = AF_UNSPEC;     // Unspecified, get whatever is available
    hint.ai_socktype = SOCK_STREAM; // TCP connection

    int status = getaddrinfo(host_or_ip, NULL, &hint, &result);
    if (status)
    {
        fprintf(stderr, "getaddrinfo failed: %s\n", gai_strerror(status));
        return;
    }

    struct addrinfo *tmp = result;
    while (tmp)
    {
        printf("Entry:\n");
        printf("\tType: %i\n", tmp->ai_socktype);
        printf("\tFamily: %i\n", tmp->ai_family);

        char address_string[INET6_ADDRSTRLEN]; // longest address string possible
        void *addr;
        if (tmp->ai_family == AF_INET)
        {
            // IPv4
            addr = &((struct sockaddr_in *)tmp->ai_addr)->sin_addr;
        }
        else
        {
            // IPv6
            addr = &((struct sockaddr_in6 *)tmp->ai_addr)->sin6_addr;
        }
        // network to printable
        inet_ntop(tmp->ai_family, addr, address_string, INET6_ADDRSTRLEN);

        printf("\tAddress: %s\n", address_string);

        tmp = tmp->ai_next;
    }

    freeaddrinfo(result);
}

void performReverseDNS(const char *host_or_ip)
{
    struct sockaddr_in sa;
    struct sockaddr_in6 sa6;
    void *addr = NULL;

    // Try to parse input as both IPv4 and IPv6
    if (inet_pton(AF_INET, host_or_ip, &(sa.sin_addr)) == 1) {
        addr = &(sa.sin_addr);
    } else if (inet_pton(AF_INET6, host_or_ip, &(sa6.sin6_addr)) == 1) {
        addr = &(sa6.sin6_addr);
    } else {
        printf("Invalid IP address format.\n");
        exit(1);
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
            exit(1);
        }
    }
}