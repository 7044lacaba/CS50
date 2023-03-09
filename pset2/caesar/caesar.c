#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool only_digits(string pee);

int main(int argc, string argv[])
{

    //Check if the Key is all numbers (1 of 2)

    string key = argv[1];
    /*
    int total = 0;
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (isdigit(key[i]))
        {
            total = total + 0;
        }
        else
        {
            total = total + 1;
        }
    }
    */
    //Check if Key has one user input and check if Key is all numbers (2 of 2)
    int keynum;
    if ((argc == 2) && (only_digits(key) == true))
    {
        keynum = atol(argv[1]);
        //Get string
        string plain = get_string("plaintext: ");

        //Sort and Encipher Text
        printf("ciphertext: ");
        for (int a = 0, b = strlen(plain); a < b; a++)
        {
            if (isupper(plain[a]) && (isalpha(plain[a])))
            {
                char x = plain[a] - 65;
                char xx = (x + keynum) % 26;
                char xxx = xx + 65;
                printf("%c", xxx);
            }
            else if (islower(plain[a]) && (isalpha(plain[a])))
            {
                char y = plain[a] - 97;
                char yy = (y + keynum) % 26;
                char yyy = yy + 97;
                printf("%c", yyy);
            }
            else
            {
                char z = plain[a];
                printf("%c", z);
            }
        }
        printf("\n");
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}

bool only_digits(string pee)
{
    for (int i = 0, n = strlen(pee); i < n; i++)
    {
        if (! isdigit(pee[i]))
        {
            return false;
        }
    }
    return true;
}

