## Project Overview
This project is a simple virtual disk storage system implemented in C. It uses a file as a virtual disk 
to store, retrieve, and list files. The project provides three executables:

- vdadd - Adds new files to the virtual disk.
- vdget - Retrives a specific file from the virtual disk.
- vdls - Lists all the files stored in the virtual disk.

## Scheme followed to store data
Length of each file is stored as Encoded Sequence from left side of the vdfile (virtual disk).
And Actual file data is stored on the right of the vdfile.

Eg. : File size = 10 Bytes, File name = Test

vdfile : | 110101110001 111100 ................................ Test This is file data |
           
## Features
- **File Storage :** Add files to the virtual disk.
- **File Retrieval :** Fetch specific files by their names from the virtual disk.
- **File Listing :** Display a list of all files currently stored on the virtual disk.

## Compilation
To compile the project, navigate to the project directory and run:

> make

This will generate the 3 executables: `vdadd`, `vdget`, and `vdls`.

## Usage
### 1. Add a file to the virtual disk:
Note : Create a file which contains path of all the files that you want to store.
> ./vdadd <file_paths> <virtual_disk_file>

### 2. List all files stored on the virtual disk:
> ./vdls <virtual_disk_file>

### 3. Retrieve a file from the virtual disk:
> ./vdget <file_name> <virtual_disk_file>

## Limitations
- Virtual Disk is of size 4 MB so the size of all files bieng stored can't exceed 4 MB.
- Deletion is not possible.

  
