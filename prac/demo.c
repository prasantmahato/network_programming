#include <stdio.h>
#include <unistd.h>

int main() {
    execl("/bin/ls", "ls", "-l", NULL);

    // If exec fails, the following code will be executed
    perror("execl");
    return -1;
}
