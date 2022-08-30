#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    const int BLOCK_SIZE = 512;
    // check that they argument count is 2
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open input file for reading
    FILE *input_file = fopen(argv[1], "r");
    // Check that the input file is valid
    if (input_file == NULL)
    {
        printf("Error! Could not open file\n\n");
        return 1;
    }

    // Store blocks of 512 bytes in an array
    unsigned char buffer[BLOCK_SIZE];

    // Track number of images generated
    int count_image = 0;

    // File pointer for recovered images
    FILE *output_file = NULL;

    // char filename[8]
    char *filename = malloc(8 * sizeof(char));

    // Read the blocks of 512 bytes
    while (fread(buffer, sizeof(char), BLOCK_SIZE, input_file))
    {
        // check if the bytes indicate a start of a JPEG
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            // Closing previously opened output_file, if opened any
            if (count_image > 0)
            {
                fclose(output_file);
            }

            // Creating the JPEG filenames
            sprintf(filename, "%03i.jpg", count_image);

            // Open output_file for writing
            output_file = fopen(filename, "w");

            // Count number of images found
            count_image++;
        }

        // At this stage our output file is opened so we want to write into it 
        // Check if output_file has been used for valid input
        if (output_file != NULL)
        {
            // writing from buffer to output file
            fwrite(buffer, sizeof(char), BLOCK_SIZE, output_file);
        }
    }

    // Closing opened files and free dynaming allocated memory
    fclose(input_file);
    fclose(output_file);
    free(filename);

    return 0;

}