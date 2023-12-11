#include <stdio.h>
int main()
{
	unsigned int i = 1;
	char *c = (char *)&i;
	printf("Val of c: %p\n",*c);
	if (*c)
		printf("Little endian");
	else
		printf("Big endian");
	
	unsigned char arr[2] = {0x01, 0x00};
    unsigned short int x = *(unsigned short int *) arr;
    printf("\nx: %d\n", x);


	return 0;
}
