final:
	gcc vdadd.c store.c compute_skip_offset.c Decode.c store_length_seq.c Encode.c store_data_seq.c utils.c create_file.c -o vdadd
	gcc vdls.c list_files.c Decode.c utils.c -o vdls
	gcc vdget.c utils.c get_file.c Decode.c -o vdget
