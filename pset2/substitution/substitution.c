#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>



int main(int argc, string argv[])
{
    string check_key = argv[1];

    //Check only 2 CLA
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }


    //Check for 26 characters
    if (strlen(check_key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }


    //Check only letters
    for (int i = 0, n = strlen(check_key); i < n; i++)
    {
        if (!(isalpha(check_key[i])))
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }
    }


    //Check for no repeating characters
    int total = 0;
    for (int i = 0, n = strlen(check_key); i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (check_key[i] == check_key[j])
            {
                total = total + 1;
            }
        }
    }
    //printf("%i\n", total);
    if (total > 26)
    {
        printf("Key must not contain repeated characters.\n");
        return 1;
    }

    //Prompt Plaintext
    string plain_text = get_string("plaintext: ");

    //Encipher Plaintext (same case)
    string valid_key = check_key;
    printf("ciphertext: ");
    for (int i = 0, n = strlen(valid_key); i < n; i++)
    {
        if (isupper(valid_key[i]))
        {
            valid_key[i] = tolower(valid_key[i]);
        }
    }
    //printf("%s\n", valid_key);

    for (int i = 0, n = strlen(plain_text); i < n; i++)
    {
        if (isupper(plain_text[i]))
        {
            int alpha_num = plain_text[i] - 65;
            char cipher_letter_low = valid_key[alpha_num];
            printf("%c", toupper(cipher_letter_low));
        }
        else if (islower(plain_text[i]))
        {
            int alpha_num = plain_text[i] - 97;
            char cipher_letter_up = valid_key[alpha_num];
            printf("%c", cipher_letter_up);
        }
        else
        {
            printf("%c", plain_text[i]);
        }
    }
    printf("\n");
}