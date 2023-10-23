#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "struct_eg.h"

int main(){
    struct struct_eg s1;
    s1.id = 1024;
    s1.s2.s2_id = 2048;

    int a = s1.id;
    int b = s1.s2.s2_id;

    printf("Outer Struct ID: %d\n", a);
    printf("Inner Struct ID : %d\n", b);

    char *program = "./build/sum ";
    char num1[10], num2[10];
    sprintf(num1, "%d", a);     // converting int to string 
    sprintf(num2, "%d", b);

    int command_length = strlen(program) + strlen(num1) + strlen(num2) + 3;

    char *command = (char *)malloc(command_length);
    if (command == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        return 1;
    }

    if (snprintf(command, command_length, "%s %s %s", program, num1, num2) >= command_length) {
        fprintf(stderr, "Command buffer too small!\n");
        free(command);
        return 1;
    }

    printf("Command executing: %s\n", command);
    int return_val = system(command);

    // check for the return value
    if (return_val == -1) {
        fprintf(stderr, "Command execution failed!\n");
    } else {
        if (WIFEXITED(return_val)) {
            int exit_status = WEXITSTATUS(return_val);
            printf("Exit status of the 'sum' program: %d\n", exit_status);
        } else {
            fprintf(stderr, "Child process did not exit normally.\n");
        }
    }

    free(command);

    return 0;
}