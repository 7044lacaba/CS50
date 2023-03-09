// Implements a dictionary's functionality

#include <stdio.h>
#include <stdlib.h>

#include <cs50.h>
#include <stdint.h>
#include <math.h>
#include <string.h>

#include <ctype.h>
#include <stdbool.h>
#include <strings.h>

#include "dictionary.h"



// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

unsigned long word_count;
unsigned int hash_index;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    //Double check
    //node *cursor = malloc(sizeof(node));

    hash_index = hash(word);
    //pointer to a node !!!! you dont need to allocate, were not working with nodes
    node *cursor = table[hash_index];

    while (cursor != 0)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    //return toupper(word[0]) - 'A';
    unsigned long total = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        total = total + tolower(word[i]);
    }
    return (total % N);
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    //Open dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    //Define (did not need to allocate) (DO NOT UNDERSTAND)
    char wrd[LENGTH + 1];

    //Read strings from file
    //Loop through entire file (don't double copy?)
    while (fscanf(dict, "%s", wrd) != EOF)
    {
        //Create a new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }

        //Copy word into node

        //char *word = malloc(sizeof(strlen(wrd) + 1));
        //n->word = malloc(strlen(wrd) + 1);

        strcpy(n->word, wrd);


        //Hash word (hash is incomplete)
        hash_index = hash(wrd);

        //Insert node into hash table (NOT SURE)
        //n->next = table[hash_index];
        //table[hash_index] = n;

        //ASSUMING HASH TABLE SET TO NULL
        n->next = table[hash_index];
        table[hash_index] = n;
        word_count++;
    }


    //Return true if successful
    fclose(dict);
    return true;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    //Double check

    if (word_count > 0)
    {
        return word_count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO

    //Loop through array
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        //Loop through linked list
        while (cursor)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
        if (cursor == NULL)
        {
            return true;
        }
    }
    return false;
}
