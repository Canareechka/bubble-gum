// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
    int resize_factor = atoi(argv[1]);
    if (!resize_factor || (resize_factor < 1 && resize_factor > 100))
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // if resize factor is 1, just copy file to target
    if (resize_factor == 1)
    {
        fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
        fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

        int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }

            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            }
        }
        fclose(inptr);
        fclose(outptr);
        return 0;
    }
    else
    {
        // printf("Width - %i, Height - %x, Image Size - %i, File Size - %i\n", bi.biWidth, bi.biHeight, bi.biSizeImage, bf.bfSize);

        // creating new headers
        BITMAPFILEHEADER bf_r = bf;
        BITMAPINFOHEADER bi_r = bi;

        // calculating width, height and image size
        bi_r.biWidth = bi.biWidth * resize_factor;
        bi_r.biHeight = 0xffffffff - (abs(bi.biHeight) * resize_factor - 1);
        
        // calculating padding for in-file and for out-file
        int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
        int padding_r = (4 - (bi_r.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
        
        // calculating image size
        bi_r.biSizeImage = (bi_r.biWidth * 3 + padding_r) * abs(bi_r.biHeight);
        bf_r.bfSize = bi_r.biSizeImage + sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER);
        // printf("Width - %i, Height - %x, Image Size - %i, File Size - %i\n", bi_r.biWidth, bi_r.biHeight, bi_r.biSizeImage, bf_r.bfSize);
        
        // write new headers to the file
        fwrite(&bf_r, sizeof(BITMAPFILEHEADER), 1, outptr);
        fwrite(&bi_r, sizeof(BITMAPINFOHEADER), 1, outptr);
        
        // iterate over lines
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
        {
            for (int z = 0; z < resize_factor; z++)
            {
                // get to the beginning of pixel-line if we are finished first iteration over pixel-line
                if (z > 0)
                {
                    fseek(inptr, -(bi.biWidth * sizeof(RGBTRIPLE)), SEEK_CUR);
                }
                // iterate over pixels in scanline
                for (int j = 0; j < bi.biWidth; j++)
                {
                    // temporary storage
                    RGBTRIPLE triple;
                    RGBTRIPLE *triple_n = malloc(sizeof(RGBTRIPLE) * resize_factor);
                    
                    // read RGB triple from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                    // printf("current RGB byte - %x, %x, %x\n", triple.rgbtRed, triple.rgbtGreen, triple.rgbtBlue);
                    for (int k = 0; k < resize_factor; k++)
                    {
                        triple_n[k] = triple;
                    }
                    
                    // write RGB triple to outfile
                    fwrite(triple_n, sizeof(RGBTRIPLE) * resize_factor, 1, outptr);
                    
                    // free pointer
                    free(triple_n);
                }
    
                // then add it back (to demonstrate how)
                for (int k = 0; k < padding_r; k++)
                {
                    fputc(0x00, outptr);
                }
            }
            // skip over padding, if any in in-file
            fseek(inptr, padding, SEEK_CUR);
        }
        fclose(inptr);
        fclose(outptr);
        return 0;
    }
}
