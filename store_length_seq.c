#include<stdio.h>
#include<stdlib.h>
#include "headers.h"

union un
{
	unsigned long long int num;
	unsigned char num_arr[sizeof(unsigned long long int)];
};

unsigned long long int store_length_seq(unsigned long long int bits_to_skip, unsigned long long int num, FILE *file)
{
	/*... STORING from long long int to char array ...*/
		union un obj;
		obj.num = num;
		int bits = Count_Bits(obj.num);
		int bytes = (bits / 8) + !!(bits % 8);
		int size = bytes;
		unsigned char* in;
		in = (unsigned char*) malloc(size * sizeof(unsigned char));

		for(int i = size - 1; i >= 0; i--)
		{
			*(in + (size - 1 - i)) = obj.num_arr[i];
		}

	/*... END of STORING from long long int to char array ...*/
	
	return Encode(bits, in, bits_to_skip, file);
}
