#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include "headers.h"

void get_file(FILE *vdfile, unsigned char* file_name)
{
	//This should be defined in a global file and accessed from there.
	unsigned int bytes_for_count = 4;
	
	bool gotFile = false;

	int count = 0;
	count = fetch_count_from_vdfile(vdfile);	

	struct DecodeResult result;
	result.bits_to_skip = 0;
	result.bytes_to_skip = 0;

	unsigned long long int bits_to_skip = (bytes_for_count * 8);
	unsigned long long int data_byte_count = 0;
	unsigned long long int file_length = 0;

	unsigned long long byte_pos = 0;
	unsigned int name_byte_count = 0;

	for(int i = 0; i < count; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			result = Decode(vdfile, bits_to_skip);
				
			bits_to_skip += result.bits_to_skip;
			if(j == 0)
			{
				data_byte_count += result.bytes_to_skip;
				file_length = result.bytes_to_skip;
			}
			else
			{
				name_byte_count = result.bytes_to_skip;
			}
		}

		data_byte_count += name_byte_count;
	
		if(strcmp(file_name, get_file_name(vdfile, (-1 * data_byte_count), name_byte_count)) == 0)
		{
			gotFile = true;
			break;
		}
	}

	if(gotFile)
	{
		FILE *file;
		file = fopen(file_name, "w");
		if(file == NULL)
		{
			printf("get_file : Failed to open file!\n");
			return;
		}

		copy_file_data(vdfile, (-1 * (data_byte_count - name_byte_count)), file_length, file);
	}
	else
	{
		printf("File not found!\n");
	}
}
