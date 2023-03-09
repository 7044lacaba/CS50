#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Get height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    //Row
    for (int i = 0; i < height; i++)
    {
        //Space
        for (int k = 0; k < height - i - 1; k++)
        {
            printf(" ");
        }
        //Column
        for (int j = 0; j < i + 1; j++)
        {
            //Print
            printf("#");
        }
        printf(" ");
        printf(" ");
        //Next Ladder
        for (int l = 0; l < i + 1; l++)
        {
            printf("#");
        }
        //Next Row
        printf("\n");
    }
}