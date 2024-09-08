#include<stdio.h>
#include<stdbool.h>
#include "headers.h"

void list_files(FILE *vdfile)
{
	//This should be defined in a global file and accessed from there.
	unsigned int bytes_for_count = 4;
	
	int count = 0;
	count = fetch_count_from_vdfile(vdfile);	

	struct DecodeResult result;
	result.bits_to_skip = 0;
	result.bytes_to_skip = 0;

	unsigned long long int bits_to_skip = (bytes_for_count * 8);
	unsigned long long int data_byte_count = 0;

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
			}
			else
			{
				name_byte_count = result.bytes_to_skip;
			}
		}

		data_byte_count += name_byte_count;
		print_file_name(vdfile, (-1 * data_byte_count), name_byte_count);
	}
}
