#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "headers.h"

void copy_file_data(FILE *src, int byte_pos, unsigned long long int bytes_to_store, FILE *dest)
{
        if(byte_pos < 0)
                fseek(src, byte_pos, SEEK_END);
        else
                fseek(dest, byte_pos, SEEK_SET);

        unsigned char ch;

        for(int i = 0; i < bytes_to_store; i++)
        {
                ch = fgetc(src);
                fputc(ch, dest);
        }
}


void print_file_name(FILE *fp, int byte_pos, unsigned int bytes)
{
        fseek(fp, byte_pos, SEEK_END);

        unsigned char file_name[50];

        fread(file_name, 1, bytes, fp);

        printf("%s\n",file_name);
}

unsigned char* get_file_name(FILE *fp, int byte_pos, unsigned int bytes)
{
        fseek(fp, byte_pos, SEEK_END);

        unsigned char file_name[50];

        int len = fread(file_name, 1, bytes, fp);
	file_name[len] = '\0';

        unsigned char* name = file_name;

        return name;
}

unsigned int fetch_count_from_vdfile(FILE *vdfile)
{
        unsigned int count = 0;

        fseek(vdfile, 0, SEEK_SET);
        if(fread(&count, sizeof(count), 1, vdfile) != 1)
        {
                printf("fetch_count : Failed to fetch count!\n");
                return 0;
        }

        return count;
}


/* Stores given array to file from n'th byte from start of the file. */
int store_array_to_file(unsigned char* arr,unsigned int count, FILE *file, int byte_pos)
{
        if(file == NULL)
                return -1;

        if(byte_pos > 0)
                fseek(file, byte_pos, SEEK_SET);
        else
                fseek(file, byte_pos, SEEK_END);

        unsigned char ch;

        for(int i = 0; i < count; i++)
        {
                ch = *(arr + i);
                fputc(ch, file);
        }

        return 1;
}

void right_shift_on_array(unsigned char bit_cnt, unsigned char *arr, int count)
{
        if(bit_cnt < 1 || bit_cnt > 8)
                return;
        unsigned char p_val = 0;
        unsigned char c_val;

        for(int i = 0; i <= count; i++)
        {
                c_val = *(arr + i);
                *(arr + i) = (*(arr + i) >> bit_cnt);
                *(arr + i) = (*(arr + i) | (p_val << (8 - bit_cnt)));

                p_val = c_val;
        }
}

unsigned char Count_Bits(unsigned long long int e)
{
        unsigned char bits = 0;
        while(e != 0)
        {
                bits += 1;
                e >>= 1;
        }

        return bits;
}

unsigned long long int count_bytes(FILE *fp)
{
        if(fp == NULL)
        {
                perror("Failed to open file!\n");
                return -1;
        }

        fseek(fp, -1, SEEK_END);

        unsigned long long int position = ftell(fp);

        fseek(fp, 0, SEEK_SET);
        return position;
}

unsigned long long int count_lines(FILE *fp)
{
        unsigned long long int lines = 0;

        int ch;
        while((ch = fgetc(fp)) != EOF)
        {
                if(ch == '\n')
                {
                        lines += 1;
                }
        }

        fseek(fp, 0, SEEK_SET);
        return lines;
}

char *trim_whitespace(char *str) {
    char *end;

    // Trim leading space
    while (isspace((unsigned char)*str)) str++;

    // All spaces?
    if (*str == 0)
        return str;

    // Trim trailing space
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator
    *(end + 1) = '\0';

    return str;
}
