#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

//define block size 512
#define BLOCK_SIZE 512

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    char *infile = argv[1];

    //open memory card file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 4;
    }

    //declare buffer of size 512 array
    BYTE buffer[512];
    //declare imageCount
    int imageCount = 0;

    //declare filename
    char filename[8];
    //declare output file and assign null value
    FILE *outptr = NULL;

    //run while loop until end of card
    while (true)
    {
        // read a block of the memory card image and store in bytes using size_t datatype
        size_t bytesRead = fread(buffer, sizeof(BYTE), BLOCK_SIZE, inptr);

        // break out of the loop when we reach the end of the card image
        if (bytesRead == 0 && feof(inptr))
        {
            break;
        }

        // check if we found a JPEG
        bool containsJpegHeader = buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;

        // if we found a yet another JPEG, we must close the previous file
        if (containsJpegHeader && outptr != NULL)
        {
            fclose(outptr);
            imageCount++;
        }

        // if we found a JPEG, we need to open the file for writing
        if (containsJpegHeader)
        {
            sprintf(filename, "%03i.jpg", imageCount);
            outptr = fopen(filename, "w");
        }

        // write anytime we have an open file
        if (outptr != NULL)
        {
            fwrite(buffer, sizeof(BYTE), bytesRead, outptr);
        }
    }

    // close last jpeg file
    fclose(outptr);

    // close infile
    fclose(inptr);

    // success
    return 0;
}
