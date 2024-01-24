// Simple read program

#include "../common.h"
#include <unistd.h>
#include <sys/select.h>
#include <sys/poll.h>


int main(int argc, char *argv[]){
    int fd=0;
    char buff[11];
    int ret, pret;
    
    struct pollfd fds[1];
    int timeout;

    while(1){
        fds[0].fd = fd;
        fds[0].events = 0;
        fds[0].events |= POLLIN;

        timeout = 5000;

        pret = poll(fds, 1, timeout);

        if(pret == 0){
            printf("\npret= %d", pret);
            printf("\tTimeOut\n");
        }else{
            memset((void *)buff, 0,11);
            ret = read(fd, (void *)buff, 10);   // read data from KB
            printf("ret=%d\n", ret);
            if(ret != -1){
                printf("buf= %s\n", buff);
            }
        }
    }
    return 0;
}
