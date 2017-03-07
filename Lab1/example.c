#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(void)
{
    char s[100];
    int i;
    int ran = rand() % 10;
    char message[] = "/0";
	srand(time(0));
	printf("Enter your name: ");
    scanf("%99s", s);
    printf("%d\n", ran);
    message[] = "Hello, "; 
    message[] = "Hi there, ";
    for (i = 0; i < ran; i++){
    	printf("%d: %s %s", ran, message, s);
    }
}
