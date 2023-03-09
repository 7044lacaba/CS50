#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int compute_letters(string book);
int compute_words(string book);
int compute_sent(string book);


int main(void)
{
    //Get string
    string book1 = get_string("Text: ");

    //Find number of letters
    double numletter = compute_letters(book1);

    //Find number of words
    double numword = compute_words(book1);

    //Find number of sentences
    double numsent = compute_sent(book1);

    //Letters per 100 words
    double pee = (numletter / numword);
    double poo = pee * 100;

    //Sentences per 100 words
    double sentper100 = (numsent / numword * 100);

    //Coleman-Liau formula
    double readlvl = ((0.0588 * poo) - (0.296 * sentper100) - 15.8);
    int final = (int) round(readlvl);

    if (final < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (final > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", final);
    }
}

//Function for letters
int compute_letters(string book)
{
    int total1 = 0;
    for (int i = 0, n = strlen(book); i < n; i++)
    {
        if (isalpha(book[i]))
        {
            total1 = total1 + 1;
        }
    }
    return total1;

}

//Function for words
int compute_words(string book)
{
    int total2 = 1;
    for (int o = 0, n = strlen(book); o < n; o++)
    {
        if (isspace(book[o]))
        {
            total2 = total2 + 1;
        }
    }
    return total2;
}

//Function for sentence
int compute_sent(string book)
{
    int total3 = 0;
    for (int p = 0, n = strlen(book); p < n; p++)
    {
        if (book[p] == 33 || book[p] == 46 || book[p] == 63)
        {
            total3 = total3 + 1;
        }
    }
    return total3;
}