#include<stdio.h>
#include "headers.h"

void make_file(unsigned char* f_name, unsigned long long int size)
{
        FILE *file;
        file = fopen(f_name, "w+");

        if(file == NULL)
        {
                perror("Failed to make_file!\n");
        }

        //Populating file with NULL 00000000 value.
        int d = 0;
        for(unsigned int i = 0; i < size; i++){
                if(fputc(d, file) == -1)
                {
                        perror("failed to insert!\n");
                        return;
                }
        }

        fclose(file);

}
