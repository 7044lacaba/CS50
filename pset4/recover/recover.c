#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <time.h>



#define BLOCK_SIZE 512
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //valid command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover infile\n");
        return 1;
    }

    //open memory card
    FILE *raw_file = fopen(argv[1], "r");
    if (raw_file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    BYTE buffer[BLOCK_SIZE];
    FILE *img;
    int file_counter = 0;
    char *filename = malloc(8);

    //repeat until end of card
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        //store the block into a buffer
        //fread(buffer, sizeof(BYTE), BLOCK_SIZE, raw_file);

        //check to see if it is the start of a JPEG
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) ==  0xe0))
        {
            //check if it is first JPEG
            if (file_counter == 0)
            {
                //create a new JPEG file to store this block into into
                sprintf(filename, "%03i.jpg", file_counter);
                file_counter++;

                //write the buffer into the JPEG we just opened
                img = fopen(filename, "w");
                if (img == NULL)
                {
                    return 1;
                }
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
            }
            //if not first then close current and open a new one
            else
            {
                //close file and start a new one
                fclose(img);

                sprintf(filename, "%03i.jpg", file_counter);
                file_counter++;

                img = fopen(filename, "w");
                if (img == NULL)
                {
                    return 1;
                }
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);

            }
        }

        //not the start of a new JPEG
        else
        {
            //if already found JPEG keep writing to it (the is the next block)
            if (file_counter > 0)
            {
                fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
            }
            //if not then skip
        }
    }

    //close files
    free(filename);
    fclose(img);
    fclose(raw_file);
}