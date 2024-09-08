#include<stdio.h>
#include "headers.h"

unsigned long long int store_data_bytes(unsigned long long int bytes_to_store, FILE *src , unsigned long long int bytes_to_skip, FILE *dest)
{
        int ch;
        char *ptr;
        ptr = (char*)&ch;
        unsigned char chr;


        //Moving destination file pointer to right position
        int pos = -1 * (bytes_to_store + bytes_to_skip);
        fseek(dest, pos, SEEK_END);

        int i = 0;
        while(i < bytes_to_store)
        {
                ch = fgetc(src);
                
		if(ch == EOF)
                        break;
                
		chr = *ptr;
                fputc(chr, dest);

                i += 1;
        }

	return i;
}
