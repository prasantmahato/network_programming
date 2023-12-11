#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

const int PROG_BAR_LENGHT = 60;

void update_bar(int percent_done)
{
    int num_chars = percent_done * PROG_BAR_LENGHT / 100;
    printf("\r[");
    for (int i = 0; i < num_chars; i++)
    {
        printf("#");
    }
    for (int i = 0; i < PROG_BAR_LENGHT - num_chars; i++)
    {
        printf(" ");
    }
    printf("] %d%% Done", percent_done);
    fflush(stdout);
}

int main()
{

    for (int i = 0; i <= 100; i++)
    {
        update_bar(i);
        usleep(200000);
    }
    printf("\n");
    return EXIT_SUCCESS;
}