// Modifies the volume of an audio file
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);
    char *header = malloc(HEADER_SIZE * sizeof(char));

    if (fread(header, sizeof(char), HEADER_SIZE, input) == HEADER_SIZE)
    {
        fwrite(header, sizeof(char), HEADER_SIZE, output);
    }
    free(header);
    printf("%li\n", sizeof(int16_t));
    //printf("%li\n", ftell(output));

    // TODO: Read samples from input file and write updated data to output file
    int16_t *buffer = malloc(2);
    while (fread(buffer, 2, 1, input) == 1)
    {
        *buffer *= factor;
        fwrite(buffer, 2, 1, output);
    }
    free(buffer);
    // Close files
    fclose(input);
    fclose(output);
}
