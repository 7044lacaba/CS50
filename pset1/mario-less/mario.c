#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height, row, column, space;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // For each row

    for (row = 0; row < height; row++)
    {
        for (space = 0; space < height - row - 1; space++)
        {
            printf(" ");
        }
        // For each column
        for (column = 0; column < row + 1 ; column++)
        {
            // Print a brick
            printf("#");
        }
        // Move to next row
        printf("\n");
    }
}




