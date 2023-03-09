#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start;
    do
    {
        start = get_int("Start Size: ");
    }
    while (start < 9);

    // TODO: Prompt for end size
    int end;
    do
    {
        end = get_int("End Size: ");
    }
    while (end < start);

    // TODO: Calculate number of years until we reach threshold
    int years = 0;
    int born, die, change;
    do
    {
        born = start / 3;
        die = start / 4;
        change = born - die;
        start = start + change;
        years++;
    }
    while (start < end);

    // TODO: Print number of years
    {
        printf("Years: %i\n", years);
    }
}
