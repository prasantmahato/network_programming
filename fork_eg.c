#include <stdio.h>
#include <unistd.h>

int main(){

    pid_t pid;
    if((pid = fork()) >= 0 ){
        if(pid == 0){
            for(int i=0; i<100; i++)
                printf("Child Process \t PID: %d \t getpid: %d\n",pid, getpid());
        }else{
            for(int i=0; i<100; i++)
                printf("Parent process \t PID: %d \t getpid: %d\n",pid, getpid());
        }
    }else{
        printf("Failed to create the process..\n");
    }
    printf("\n");

    fork();
    fork();
    printf("GETPID(): %d\n", getpid());
    return 0;
}