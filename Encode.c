#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "headers.h"

//	bits to store len	
int Encode(unsigned char len, unsigned char *temp_in, unsigned long long int bits_to_skip, FILE *file)
{ 

	//Declaring variable for Result
	unsigned long long int total_bits = 0;

	unsigned char bits_for_len = 0;
	if(len == 0 || len == 1)
	{
		len = 2;
	}
	
	bits_for_len = Count_Bits(len);


/*.... Creating Array of Lengths ....*///[THIS PART OF CODE IS CORRECT]

	unsigned char *lengths_arr;
	lengths_arr = (unsigned char*) malloc(sizeof(unsigned char) * 4);
	
	unsigned char val = len;
	unsigned char bit_cnt = 0;
	int count = 0;
	while(true)
	{
		bit_cnt = 0;
		*(lengths_arr + count) = val;
		while(val != 0)
		{
			bit_cnt += 1;
			val >>= 1;
		}
		
		val = bit_cnt;
		count += 1;
		if(bit_cnt <= 2) break;

	}


	//Reverse lengths_arr
	for(int i = 0; i < (count/2); i++)
	{
		val = *(lengths_arr + i);
		*(lengths_arr + i) = *(lengths_arr + (count - i - 1));
		*(lengths_arr + (count - i - 1)) = val;
	}

/*.... END OF Array of Lengths Creation....*/



/*.... Combining Lengths as a single bit sequence in *Out ....*/ //[THIS PART OF CODE IS CORRECT]
	unsigned char value = 0;
	unsigned char bits = 0;
	unsigned char rem_bits = 8;
	unsigned int pre_seq_bits = 0;

	unsigned char* out = (unsigned char*) calloc((sizeof(unsigned long long int) + 2), sizeof(unsigned char));
	unsigned char* temp_out = out;

	for(int i = 0; i < count; i++)//Iterating through all elements of Lengths_arr
	{
		value = *(lengths_arr + i);
		bits = Count_Bits(value);
		
		if( (rem_bits - (bits + 1)) > 0)
		{
			value <<= (rem_bits - bits);
			*temp_out |= value;
			rem_bits -= (bits + 1);
		}
		else if((rem_bits - (bits + 1)) < 0)
		{
			value >>= (bits - rem_bits);
			*temp_out |= value;

			value = *(lengths_arr + i);
			value <<= (8 - (bits - rem_bits));
			*(temp_out += 1) |= value;
			rem_bits = (8 - (bits - rem_bits)) - 1;
		}
		else
		{
			*temp_out |= value;
		}

		pre_seq_bits += (bits + 1);
	}

//	APPENDING SET BIT 1 AFTER LENGTH SEQUENCE	
	*(out + (pre_seq_bits / 8)) |= (1 << (8 - (pre_seq_bits % 8)));

	total_bits = (pre_seq_bits + len);

/*.... END OF Combining Lengths as a single bit sequence in *Out ....*/


/*... Removing Leading 0's from temp_in (Actual length binary seq.) and storing result to in  ...*/ //[LEADING ZERO'S ARE SUCCESSFULLY REMOVED]

	unsigned char terminator = ((len / 8) + !!(len % 8));
	unsigned char *in = (unsigned char*) calloc(terminator, sizeof(unsigned char));

	int remn = (len % 8);
	int k = 0;
	
	for(int i = 0; i < terminator; i++)
	{
		if(remn > 0)
		{
			*(in + i) = (*(temp_in + k) << (8 - remn));
			k += 1;
			if(k > terminator) break;
			*(in + i) |= *(temp_in + k) >> remn;
		}
		else
		{
			*(in + i) = *(temp_in + i);
		}		
	}

/*... END OF Removing Leading 0's from in ...*/	


/*.... Appending actual length sequence  ....*/ //[THIS PART OF CODE IS CORRECT]
	
	terminator = len / 8;
        terminator += (!!(len % 8));
	temp_out = out;
	// k variable which will point to byte of in in which value should be stored.
        k = (pre_seq_bits / 8);//start storing from byte where previous sequence is ended
        remn = (pre_seq_bits % 8); //remn will tell me that how many bits i've to skip in each byte so that previous sequence will be unchanged.
	
	for(int i = 0; i < terminator; i++)
        {
                value = *(in + i);
                *(temp_out + k) |= (value >> remn );
                k += 1;
                *(temp_out + k) = (value << (8 - remn) );
        }

/*.... END OF Appending actual length sequence ....*/


/*... STORING Encoded sequence TO FILE....*/ 

	//calculating byte position
	unsigned long long int byte_pos = (bits_to_skip / 8);
	fseek(file, byte_pos, SEEK_SET);

	terminator = total_bits / 8;
	terminator += !!(total_bits) % 8;

	unsigned char temp_ch,ch = fgetc(file);
	temp_ch = ch;
	fseek(file, -1, SEEK_CUR);	
	
	unsigned char filled_bits = bits_to_skip % 8;
	
	right_shift_on_array(filled_bits, out, terminator);
	*out |= ch;

	store_array_to_file(out, terminator + 1, file, byte_pos);


/*....END of STORING Encoded sequence....*/	
	
	return total_bits;
}

