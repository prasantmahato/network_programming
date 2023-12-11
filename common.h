#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#ifndef MAXLINE
#define MAXLINE 4096
#endif

#define SA struct sockaddr_in


