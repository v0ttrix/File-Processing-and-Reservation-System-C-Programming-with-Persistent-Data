//Jaden Mardini - PROG71990 - SEC1 - STUDENT#8762993

//two line command that writes a file copy program 
//use the tolower() function from ctype.h to convert all text
//incoprate standard I / O with text mode

#define _CRT_SECURE_NO_WARNINGS
#define MAXSIZE 100  //max size for the buffer (limit the number of characters read at once)

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
    //first, let's make sure the user gave us exactly two arguments (source and destination files)
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;  //exit if the arguments are not correct
    }

    //try to open the source file in read mode. If it fails, print an error and stop.
    FILE* sourceFile = fopen(argv[1], "r");
    if (sourceFile == NULL)
    {
        perror("Error opening source file");
        return 1;  //exit if the source file can't be opened
    }

    //try to open the destination file in write mode. If it fails, print an error and stop.
    FILE* destinationFile = fopen(argv[2], "w");
    if (destinationFile == NULL)
    {
        perror("Error opening destination file");
        fclose(sourceFile);  //don't forget to close the source file before we exit
        return 1;  //exit if the destination file can't be opened
    }

    char temp[MAXSIZE];  //buffer to store the current line from the source file

    //read the source file line by line using fgets
    //fgets reads up to MAXSIZE characters ,and we process each line one by one
    while (fgets(temp, MAXSIZE, sourceFile))
    {
        // Go through each character in the buffer (temp) and convert it to lowercase
        for (int i = 0; temp[i] != '\0'; i++)
        {
            temp[i] = tolower(temp[i]);  //convert each character to lowercase
        }

        //after converting the line to lowercase, write it to the destination file
        fputs(temp, destinationFile);
    }

    //don't forget to close both files 
    fclose(sourceFile);
    fclose(destinationFile);

    //print a success message after everything is finished
    printf("Files copied successfully with all text converted to lowercase.\n");

    return 0;  //everything went well, so we return 0 to indicate success
}
