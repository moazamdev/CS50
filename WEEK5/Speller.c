// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// global variable to count words
int word_counter = 0;

// TODO: Choose number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO

    // Creates copy of word on which hash function can be performed
    int n = strlen(word);
    char word_copy[LENGTH + 1];
    for (int i = 0; i < n; i++)
    {
        word_copy[i] = tolower(word[i]);
    }
    // Adds null terminator to end string
    word_copy[n] = '\0';

    int index = hash(word_copy);

    // create new node *cursor and set it to first element of the linked list
    node *cursor = table[index];

    // Check until the cursor is not NULL
    while (cursor != NULL)
    {
        // compare two strings case insensitively
        if (strcasecmp(cursor->word, word_copy) == 0)
        {
            // return true if words are same
            return true;
        }
        // assigning the address of next node to cursor
        else
        {
            cursor = cursor->next;
        }
    }

    return false;
}

// Hashes word to a number

// Using the djb2 hash function, can be found on GitHub and Reddit
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int value = 0;
    unsigned int key_len = strlen(word);
    for (int i = 0; i < key_len; i++)
    {
        value = (value << 2) ^ word[i];
    }
    return value % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO

    // Open dictionary file
    FILE *input_file = fopen(dictionary, "r");
    if (input_file == NULL)
    {
        printf("Unable to open file.\n");
        return false;
    }

    // Read strings from file one at a time
    char word[LENGTH + 1];
    while(fscanf(input_file, "%s", word) != EOF)
    {
        // Create a new node for each word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            unload();
            return false;
        }
        strcpy(n->word, word);
        // this part is necessary, otherwise you'll get a valgrind error
        n->next = NULL;

        // Hash word to obtain a hash value
        int index = hash(n->word);

        // Insert node into hash table at the location
        if (table[index] == NULL)
        {
            table[index] = n;
            word_counter++;
        }
        else
        {
            n->next = table[index];
            table[index] = n;
            word_counter++;
        }
    }

    fclose(input_file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // Iterating through the total number of buckets
    for (int i = 0; i < N; i++)
    {
        // creating a node *cursor for not losing the path to chained linked lists
        node *cursor = table[i];
        // tmp node is to free the linked list and then reassigning it back to the cursor
        node *tmp = cursor;

        // iterating through all linked lists(nodes) in the bucket until the end of each bucket
        while (cursor != NULL)
        {
            // assigning the cursor the address of next linked list
            cursor = cursor->next;
            // and deleting (freeing up memory) the previous linked list
            free(tmp);
            // and then moving the tmp forward so to delete all linked lists one by one
            tmp = cursor;
        }
    }
    return true;
}
