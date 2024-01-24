// Simple read program

#include "../common.h"
#include <unistd.h>
#include <sys/select.h>

void main(){
    int fd=0;
    char buff[11];
    int ret;

    while(1){
        memset((void *)buff, 0,11);
        ret = read(fd, (void *)buff, 10);   // read data from KB
        printf("ret=%d\n", ret);

        if(ret != -1){
            printf("buf= %s\n", buff);
        }
    }
}
