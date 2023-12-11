#include <stdint.h>
#include <stdio.h>

int main(){
    uint64_t word1 = 0x50524153414e54;    // hex for "prasant"
    char *ptr = (char *)&word1;

    for(int i=0; i<7; i++)
        printf("%02x ", (unsigned int)ptr[i]);
    printf("\n");
    for (int i=0; i<7; i++)
    {
        printf("%c ", (char)ptr[i]);
    }
    printf("\n");
    return 0;
}