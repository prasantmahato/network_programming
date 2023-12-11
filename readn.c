#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

const int PROG_BAR_LENGHT = 60;

void update_bar(int percent_done){
    int num_chars = percent_done * PROG_BAR_LENGHT / 100;
    printf("\r[");
    for(int i = 0; i < num_chars; i++){
        // printf("%c",219);
        printf("#");
    }
    for(int i = 0; i < PROG_BAR_LENGHT - num_chars; i++){
        printf(" ");
    }
    printf("] %d%% Done", percent_done);
    // fflush(stdout);
}

void readn(int arr[], int n){
    printf("\t\t\t\t\t\tData \t Position \t byteRead \t byteLeft\n");
    printf("\n");
    for(int i=0; i<n; i++){
        update_bar((i+1)*10);
        usleep(200000);
        fflush(stdout);
        printf("\t\t\t\t\t\t%d \t %p ", arr[i], &arr[i]);
        printf("%*d \t\t %d\n",9,i+1,n-i-1);
    }
}

void writen(int arr[], int n){
    printf("\t\t\t\t\t\tData \t Position \t byteWritten \t byteLeft\n");
    for(int i=0; i<n; i++){
        arr[i] *= 10;
        printf("\t\t\t\t\t\t%d \t %p ", arr[i], &arr[i]);
        printf("%*d \t\t %d\n",9,i+1,n-i-1);
        update_bar((i+1)*10);
        usleep(200000);
    }
}

int main(){
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // ssize_t read = readn(1, arr, 10);
    readn(arr, 10);
    printf("\n");
    writen(arr, 10);
    printf("\n");
    return 0;
}