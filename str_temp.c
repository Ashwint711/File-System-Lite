#include<stdio.h>
#include<string.h>
#include "headers.h"

int main(int argc, void *args[])
{
	if(strcmp("sign.jpg", args[1]) == 0)
		printf("Matched!\n");
	else
		printf("Doesnt match!\n");
	return 0;
}
