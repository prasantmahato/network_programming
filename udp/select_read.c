// Simple read program

#include "../common.h"
#include <unistd.h>
#include <sys/select.h>

void main(){
    int fd=0;
    char buff[11];
    int ret, sret;
    fd_set readfs;
    struct timeval timeout;

    while(1){
        FD_ZERO(&readfs);
        FD_SET(fd, &readfs);
        timeout.tv_sec = 3;
        timeout.tv_usec  = 0;

        sret = select(8, &readfs, NULL, NULL, &timeout);
        if(sret == 0){
            printf("\nsret= %d", sret);
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
}
