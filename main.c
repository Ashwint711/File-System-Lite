#include<stdio.h>
#include "headers.h"

int main(int argc, void *args[])
{
	if(argc < 3)
	{
		printf("Invalid input!\n");
		return -1;
	}


	FILE *file_paths;
	FILE *vdfile;
	
	//Accessing SOURCE file
	file_paths = fopen(args[1], "r");
	if(file_paths == NULL)
	{
		printf("Failed to open Source file!\n");
		return -1;
	}

/*.. Creating vdfile if does not Exist ..*/
	
	if((vdfile = fopen(args[2], "r+")) == NULL)
	{
		make_file(args[2], 4194304); // 4 MB
					     
		if ((vdfile = fopen(args[2], "r+")) == NULL) 
		{
       		 printf("Failed to open Destination file!\n");
        	 return -1;
    		}
	}				     
	

	store(file_paths, vdfile);
}
