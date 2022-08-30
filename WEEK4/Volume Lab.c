// Modifies the volume of an audio file

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

    // TODO: Copy header from input file to output file
    // creating a header array of 44 size (bytes)
    uint8_t header[HEADER_SIZE];
    // writing the data from file to buffer(header)
    fread(header, HEADER_SIZE, 1, input);
    // writing the data from buffer(header) to file
    fwrite(header, HEADER_SIZE, 1, output);


    // TODO: Read samples from input file and write updated data to output file
    // creating a variable buffer
    int16_t buffer;
    // looping through the input data one by one and writing it in the buffer variable until all data is completely copied to buffer
    while (fread(&buffer, sizeof(int16_t), 1, input))
    {
        // updating the volume by factor
        buffer *= factor;
        // writing updated data to file from buffer variable
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
