#ifndef UTILS_H

#define UTILS_H

//unsigned char bytes_for_count = 4;

struct DecodeResult
{
        unsigned long long int bits_to_skip;
        unsigned long long int bytes_to_skip;
};



unsigned char Count_Bits(unsigned long long int e);

int Encode(unsigned char bits, unsigned char* in, unsigned long long int bits_to_skip, FILE *file);

struct DecodeResult computeSkipOffset(FILE *vdfile, unsigned int count, unsigned long long int bytes_for_count);

struct DecodeResult Decode(FILE *vdfile, unsigned long long int bits_to_skip);

unsigned long long int count_bytes(FILE *fp);

unsigned long long int count_lines(FILE *fp);


void make_file(unsigned char* f_name, unsigned long long int size);

void store(FILE *paths, FILE *vdfile);

char *trim_whitespace(char *str);

unsigned long long int store_length_seq(unsigned long long int bits_to_skip, unsigned long long int num, FILE *file);

unsigned long long int store_data_bytes(unsigned long long int bytes_to_store, FILE *src , unsigned long long int bytes_to_skip, FILE *dest);

void right_shift_on_array(unsigned char bit_cnt, unsigned char *arr, int count);

int store_array_to_file(unsigned char* arr, unsigned int count, FILE *file, int byte_pos);

//RETURN TYPE WILL VARY IF vdfile SIZE IS MORE THAN 4GB
unsigned int fetch_count_from_vdfile(FILE *vdfile);

void print_file_name(FILE *fp, int byte_pos, unsigned int bytes);

void list_files(FILE *vdfile);

void get_file(FILE *vdfile, unsigned char* file_name);

unsigned char* get_file_name(FILE *fp, int byte_pos, unsigned int bytes);

void copy_file_data(FILE *src, int byte_pos, unsigned long long int bytes_to_store, FILE *dest);

#endif
