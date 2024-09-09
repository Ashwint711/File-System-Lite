#include<stdio.h>
#include<string.h>
#include "headers.h"


void store(FILE *file_paths, FILE *vdfile)
{
	unsigned char buffer[256];
	FILE *data_file;

/*.. Declaring a variable which will fix initial k bytes for COUNT | SETTING IT AS 4 BYTES AS 4 BYTES WILL BE ENOUGH FOR 4 MB ..*/
	unsigned int bytes_for_count = 4;

	unsigned int count = fetch_count_from_vdfile(vdfile);

/*.. Fetching number of files from file-paths ..*/

	unsigned long long len_in_byte = 0;
	unsigned long long file_cnt = 0;

	file_cnt = count_lines(file_paths);

/*.. END OF Fetching number of files from file-paths ..*/
	

/*.. Struct Object to store result returned by Decode ..*/
	struct DecodeResult skip_offset;
	skip_offset.bits_to_skip = 0;
	skip_offset.bytes_to_skip = 0;

	fseek(vdfile, bytes_for_count, SEEK_SET);

        skip_offset = computeSkipOffset(vdfile, count, bytes_for_count);


/*.. Storing total BITS from left and BYTES from right to skip ..*/

	unsigned long long int bits_from_left = skip_offset.bits_to_skip;
//	unsigned long long int bits_from_left = (bytes_for_count * 8);
	unsigned long long int bytes_from_right = skip_offset.bytes_to_skip;


	len_in_byte = 0;
	
	//Putting file pointer at the start
	fseek(file_paths, 0, SEEK_SET);
	
	//Storing all Length sequences & data sequences
	while(fgets(buffer, sizeof(buffer), file_paths) != NULL)
	{
		//Trim leading & trailing white spaces
		char* trimmed_path = trim_whitespace(buffer);	

		data_file = fopen(trimmed_path, "r");
		if(data_file == NULL)
		{
			printf("store : Failed to open %s!\n",trimmed_path);
			return;
		}

/*..	1. Storing Actual data Sequence's 	..*/
		
		//i. Length sequence
		len_in_byte = count_bytes(data_file);
		bits_from_left += store_length_seq(bits_from_left, len_in_byte, vdfile);

		//ii. Storing Bytes from data_file to vdfile
		bytes_from_right += store_data_bytes(len_in_byte, data_file, bytes_from_right, vdfile);


/*..	2. Storing Meta data sequences ..*/
		//Removing Path from file name : ../Folder/file_name -> file_name
		int fname_start = 0;

		len_in_byte = strlen(buffer);
		for(int i = 0; i < len_in_byte; i++)
		{
			if(buffer[i] == '/')
			{
				fname_start = i + 1;
			}
		}
		unsigned char* fname = (unsigned char*)(buffer + fname_start);
		len_in_byte -= fname_start;

		//len_in_byte contains Number of characters in File Name	
		bits_from_left += store_length_seq(bits_from_left, len_in_byte, vdfile);

		
		//updating bytes_from_right as File Name is also added from right	
		bytes_from_right += len_in_byte;

		//storing File Name from Buffer to vdfile Before actual file data.	
		store_array_to_file(fname, len_in_byte, vdfile, (-1 * bytes_from_right));

/*.. 	DONE STORING  	..*/

	}

/*.. Storing New count to vdfile ..*/

	fseek(vdfile, 0, SEEK_SET);
	count += file_cnt;
	if(fwrite(&count, sizeof(count), 1, vdfile) != 1)
	{
		perror("store : Failed to Update count in vdfile!\n");
		return;
	}

/*.. END of Storing New count to vdfile ..*/	

}
