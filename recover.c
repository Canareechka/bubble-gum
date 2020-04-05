#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define FS_BLOCK 512
#define JPEG_HEADER 4

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }
    
    FILE *infile = fopen(argv[1], "r");
    if (!infile)
    {
        fprintf(stderr, "Can't open file %s\n", argv[1]);
        return 2;
    }
    
    uint8_t *chunk = malloc(FS_BLOCK);
    uint8_t header[JPEG_HEADER];
    int jpeg_count = 0;
    bool found = false;
    FILE *jpeg_file;
    char *filename = malloc(8);
    
    while (fread(chunk, FS_BLOCK, 1, infile) == 1)
    {
        // for (int i = 0; i < JPEG_HEADER; i++)
        // {
        //     header[i] = *chunk++;
        // }
        // chunk -= JPEG_HEADER;
        if (chunk[0] == 0xff && chunk[1] == 0xd8 && chunk[2] == 0xff && ((chunk[3] & 0xf0) == 0xe0))
        {
            if (jpeg_count > 0)
            {
                fclose(jpeg_file);
            }
            found = true;
            sprintf(filename, "%03d.jpg", jpeg_count);
            jpeg_count++;
            if ((jpeg_file = fopen(filename, "w")))
            {
                fwrite(chunk, FS_BLOCK, 1, jpeg_file);
            }
            else
            {
                fprintf(stderr, "Can't write to %s", filename);
                return 2;
            }
        }
        else if (found)
        {
            fwrite(chunk, FS_BLOCK, 1, jpeg_file);
        }
    }
    free(chunk);
    free(filename);
    // printf("Found %i JPEG-files in file %s\n", jpeg_count, argv[1]);
    fclose(infile);
    return 0;
}
