#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
void open_file(int counter, FILE **output);



int main(int argc, char *argv[])
{
    int counter = 000;
    const int BLOCK_SIZE = 512;
// check command line arguments
    if (argc != 2)
    {
        printf("usage: ./recover filename\n");
        return 1;
    }
// read input file
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("couldn't open input file\n");
        return 2;
    }
    FILE *output = NULL;

// malloc memory for a buffer of size 512 for storing blocks of data
    uint8_t *buffer = malloc(BLOCK_SIZE);

// skips the FAT32's 512 bytes of formatting, and prints location in file for checking
    fseek(input, 512, ftell(input));
    printf("%li\n", ftell(input));

// reads every block of data, and sends it to buffer
    while (fread(buffer, 1, 512, input) == 512)
    {
        // checks if the first 4 bytes of a block are jpg format bytes
        if ((*buffer == 255) && (*(buffer + 1) == 216) && (*(buffer + 2) == 255) && (*(buffer + 3) >= 224))
        {
            printf("image found!\n");
            // checks if there is an output file open, and closes it in prep for a new jpg file
            if (output != NULL)
            {
                fclose(output);
            }
            // opens the new jpg file and writes the block to it
            open_file(counter, &output);
            printf("file name: %p\n", output);
            fwrite(buffer, 1, 512, output);
            counter++;
        }
        // checks if the first 4 bytes of a block aren't the standard jpg starting bytes, if we have a file open
        // then these bytes belong to the already opened file, if not then they aren't bytes of interest
        else
        {
            if (output != NULL)
            {
                fwrite(buffer, 1, 512, output);
                printf("file name: %03d.jpg\n", counter);
            }
        }
    }
    // frees allocated memory, and closes opened files, and prints the count of files
    printf("number of files recovered: %d\n", counter);
    free(buffer);
    fclose(input);
    fclose(output);
    return 0;
}

//opens a new output file and assigns it a name out of 3 digits
void open_file(int counter, FILE **output)
{
    //mallocs 8 bytes of data, 3 for the name, 4 for the extension, 1 for the nul byte
    char *name = malloc(8);
    sprintf(name, "%03d.jpg", counter);
    printf("new output file opened!\n");
    *output = fopen(name, "w");
    free(name);
    if (*output == NULL)
    {
        printf("couldn't open output file\n");
    }
}