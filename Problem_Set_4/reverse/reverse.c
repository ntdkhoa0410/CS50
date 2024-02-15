#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3){
        printf("Usage: reverse inputfile outputfile\n");
        return 1;
    }

    //Take user's inputs
    char* infile = argv[1];
    char* outfile = argv[2];

    // Open input file for reading
    FILE *inptr = fopen(infile, "rb");
    if (inptr == NULL){
        printf("Can not open file %s\n", infile);
        fclose(inptr);
        return 2;
    }

    // Read header
    WAVHEADER bf;
    fread(&bf, sizeof(WAVHEADER), 1, inptr);

    // Use check_format to ensure WAV format
    if (check_format(bf) == 1){
        printf("This is not wav format\n");
        return 4;
    }

    // Open output file for writing
    FILE *outptr = fopen(outfile, "wb");
    if (outptr == NULL){
        printf("Can not open file %s\n", outfile);
        fclose(inptr);
        fclose(outptr);
        return 5;
    }

    // Write header to file
    fwrite(&bf, sizeof(WAVHEADER), 1, outptr);

    // Use get_block_size to calculate size of block
    int block_size = get_block_size(bf);

    // Write reversed audio to file
    // TODO #8
    BYTE buffer[block_size];
    fseek(inptr, block_size, SEEK_END);
    while (ftell(inptr) - 2*block_size >= sizeof(bf)){
        if (fseek(inptr, -2*block_size, SEEK_CUR)){
            return 1;
        }
        fread(&buffer, sizeof(block_size), 1, inptr);
        fwrite(&buffer, sizeof(block_size), 1, outptr);
    }
     //Close file
    fclose(inptr);
    fclose(outptr);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    if (header.format[0] == 'W' && header.format[1]== 'A' && header.format[2]== 'V' && header.format[3]== 'E'){
        return 0;
    }
    return 1;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    int size = header.numChannels*header.bitsPerSample / 8;
    return size;
}