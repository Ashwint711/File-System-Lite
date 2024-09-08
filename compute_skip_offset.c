#include<stdio.h>
#include "headers.h"


struct DecodeResult computeSkipOffset(FILE *vdfile, unsigned int count, unsigned long long int bytes_for_count)
{
	struct DecodeResult finalResult;
	finalResult.bits_to_skip = (bytes_for_count * 8);
	finalResult.bytes_to_skip = 0;
	

/*... FETCHING count of Bits in which Count/Length is stored. ...*/
	
	for(int a = 0; a < count; a++)
	{
		struct DecodeResult decodeResult;
		decodeResult.bits_to_skip = 0;
		decodeResult.bytes_to_skip = 0;
		
		for(int j = 0; j < 2; j++)
		{
			decodeResult = Decode(vdfile, finalResult.bits_to_skip);

			finalResult.bits_to_skip += decodeResult.bits_to_skip;
			finalResult.bytes_to_skip += decodeResult.bytes_to_skip;
		}
	}

	return finalResult;
}
