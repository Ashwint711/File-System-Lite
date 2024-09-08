#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "headers.h"


struct DecodeResult Decode(FILE *vdfile, unsigned long long int bits_to_skip)
{
	struct DecodeResult result;
	result.bits_to_skip = 0;
	result.bytes_to_skip = 0;

	unsigned char val = 0,temp = 0;
	unsigned char cur_bits = 2;
	unsigned char rem_bits = 8;
	unsigned char bits_visited = 0;
	int bit_seq_len = 0;
	int fp_pos = 0;

	unsigned char ch;
	

/*... FETCHING count of Bits in which Count/Length is stored. ...*/
	
		// INITIALIZATION	
		bits_visited = (bits_to_skip % 8);
		rem_bits = (8 - bits_visited);
		cur_bits = 2;
		bit_seq_len = 0;
		
		fp_pos = (bits_to_skip / 8);
		fseek(vdfile, fp_pos, SEEK_SET);

		ch = fgetc(vdfile);
		//Check ch
		fseek(vdfile, -1, SEEK_CUR);

		while(true)
		{
			if( (rem_bits - (cur_bits + 1)) >= 0 )
			{
				val = (ch) >> (8 - (bits_visited + cur_bits));
				val &= (0xff >> (8 - cur_bits));

				temp = (ch);
				temp >>= (8 - ((cur_bits + 1) + bits_visited));

				bits_visited += (cur_bits + 1);
				rem_bits -= (cur_bits + 1);
			}
			else
			{
				val = (ch) << (8 - rem_bits);
				
				fseek(vdfile, 1, SEEK_CUR);
				ch = fgetc(vdfile);
				fseek(vdfile, -1, SEEK_CUR);

				val |= (ch) >> rem_bits;
				val >>= (8 - cur_bits);

				temp = (ch);
				temp >>= (8 - ((cur_bits + 1) - rem_bits));

				bits_visited = (cur_bits + 1) - rem_bits;
				rem_bits = 8 - bits_visited;
			}
			bit_seq_len += (cur_bits + 1);
			if(temp & 1) break;
			cur_bits = val;
		}

		/*... END of FETCHING count of Bits in which Count/Length is stored. ...*/

		/* val - Number of bits in which Length/Count is stored. */
		/* bit_seq_len - Number of bits taken to store sequence of Length/Count. */

		/*... DECODING actual COUNT/LENGTH ...*/

		//TOTAL bits to store whole encoded sequence
		unsigned int total_seq_bits = val + bit_seq_len;
		unsigned int total_bits = (total_seq_bits + bits_to_skip); //total bits from first Byte

		unsigned char remn = total_bits % 8;
		//to be removed : int k = (total_bits/8) + !!(total_bits % 8);
		//to be removed : k -= 1 ;

		int size = ((val / 8) + !!(val % 8));

		unsigned char value = 0;
		unsigned char *res =  (unsigned char*) calloc(size, sizeof(unsigned char));
		
	/*.. Moving File Pointer to Last Byte of Sequence. ..*/
		fp_pos = (total_bits) % 8 == 0 ? ((total_bits) / 8) - 1 : (total_bits) / 8;
		fseek(vdfile, fp_pos, SEEK_SET);


		for(int i = (size - 1); i >= 0; i--)
		{
			ch = fgetc(vdfile); 
			//check if fgetc() succeeded or not
			fseek(vdfile, -1, SEEK_CUR);

			if(remn > 0)
			{
				*(res + i) = ((ch) >> (8 - remn));
				fseek(vdfile, -1, SEEK_CUR);
				//if(k < 0) break; //[maybe dead code]
				ch = fgetc(vdfile);
				fseek(vdfile, -1, SEEK_CUR);

				*(res + i) |= (ch << remn);
			}
			else
			{
				*(res + i) = (ch);
				fseek(vdfile, -1, SEEK_CUR);
			}
		}

		*(res) &= (0xff >> ((!!(val % 8)) * (8 - (val % 8))));//Don't shift when remainder is 0.

		/*... END of FETCHING actual COUNT/LENGTH ...*/


		/*... DECODED SEQUENCE to Number...*/

		unsigned long long int length = 0;
		unsigned char* ptr = (unsigned char*) &length;
		for(int i = 0; i < size; i++)
		{
			*(ptr + (size - 1 - i)) = *(res + i);
		}

		/*... END ...*/

		result.bits_to_skip = total_seq_bits;
		result.bytes_to_skip = length;

	return result;
}
