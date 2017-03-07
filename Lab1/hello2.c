#include <stdio.h>
int main(void)
{
	char s[100];
	printf("Enter your name: ");
    scanf("%99s", s);
    printf("Hello, %s\n", s);
    return 0;
} 
