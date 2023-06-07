## Project Objectives.

The main goal of this project was to learn the following concepts :-

- How to create a multipurpose hashtable with chainlinks.
- Function pointers.
- Dynamic memory allocation using `mallocs` , `callocs` and `free`.
- Makefiles for automatic code compilation and testing.
- Accessing and manipulating files in a native device.
- Creating files to native device.
- Error handling.
- Creating static and dynamic memories - also through makefiles.
- Creating an efficient hashfunction for efficient memory indexing.

## Other Functionalities.

- Hashtable lookup.
- Hashtable deelete - for deleting selected data.
- hashtable destroy function.

## Program Functionality.

- Program starts by determining if it has read, write permissions for the CSV data file to be analysed.
- Next the program creates a hash table.
- Opens the CSV file in read mode, then skips the first line.
- It then parses the successive lines while extracting the fileds.
- It creates a new recors and assigns the correct values.
- It then inserts the records into the hashtable by utilising the `hashtable_insert` function in the hashtable.c file.
- It performs a simple analysis in this case determining the average age of the members. (Version 1).
- It then creates an output file where it gives the average of the ages.

## How to use the Program

Method 1.
- Download all the files in this repo.
- Download and run the parser.exe executable.
- The data.csv file will be used as a test.

Method 2.
- Download all the files in this repo and ensure they are all in the same directory.
- Compile the code by gcc using the command `gcc parser.c hashtable.c -o parser` this will produce the parser.exe executable which you can run.
- Ypu can get the gcc compiler by downloading and installing the MingW program from their official website and setting the environment variables as required.

Contact me for any querries.

Talk to me on twitter `arnold0duor`