#include<stdio.h>
#include "headers.h"

int main(int argc, void *args[])
{
	if(argc < 2)
	{
		printf("Invalid input! [format : ./vdls <disk_part>]\n");
		return -1;
	}
	
	FILE *vdfile;
	vdfile = fopen(trim_whitespace(args[1]), "r+");
	if(vdfile == NULL)
	{
		printf("No file named : %s\n",trim_whitespace(args[1]));
		return -1;
	}

	list_files(vdfile);

	return 0;
}
