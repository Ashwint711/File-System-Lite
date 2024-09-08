#include<stdio.h>
#include<string.h>
#include "headers.h"

int main(int argc, void *args[])
{
	if(argc < 3)
	{
		printf("Invalid command! [format : ./vdget <file_name> <disk_name>]\n");
		return -1;
	}

	unsigned char file_name[50];
	
	strcpy(file_name, trim_whitespace(args[1]));

	FILE *vdfile;
	vdfile = fopen(trim_whitespace(args[2]), "r+");
	if(vdfile == NULL)
	{
		printf("Failed to open disk!\n");
		return -1;
	}

	get_file(vdfile, file_name);

	return 0;

}
