// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26 * 4

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    unsigned int hashsum = 0;
    for (int i = 0; word[i] != '\0' && i < 4; i++)
    {
        if (tolower(word[i]) >= 'a' && tolower(word[i]) <= 'z')
        {
            hashsum += (tolower(word[i]) - 'a');
        }
    }
    return hashsum;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Bucket number to calculate it once for a give word and store for efficiency
    unsigned int bucket;

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // creating new node
        node *word_node = malloc(sizeof(node));
        if (!word_node)
        {
            return false;
        }
        // setting values for new node
        strcpy(word_node->word, word);
        word_node->next = NULL;
        // calculating bucket number;
        bucket = hash(word);
        // inserting node into hash-table
        if (hashtable[bucket])
        {
            for (node *ptr = hashtable[bucket]; ptr != NULL; ptr = ptr->next)
            {
                if (!ptr->next)
                {
                    ptr->next = word_node;
                    break;
                }
            }
        }
        else
        {
            hashtable[bucket] = word_node;
        }
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    unsigned long counter = 0;
    for (int i = 0; i < N; i++)
    {
        for (node *ptr = hashtable[i]; ptr != NULL; ptr = ptr->next)
        {
            counter++;
        }
    }
    return counter;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    unsigned int lookup_hash = hash(word);
    if (!hashtable[lookup_hash])
    {
        return false;
    }
    for (node *ptr = hashtable[lookup_hash]; ptr != NULL; ptr = ptr->next)
    {
        if (strlen(word) != (strlen(ptr->word)))
        {
            continue;
        }
        for (int i = 0, l = strlen(ptr->word); i < l; i ++)
        {
            if (tolower(word[i]) != tolower(ptr->word[i]))
            {
                break;
            }
            if ((l - i) == 1)
            {
                return true;
            }
        }
    }
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *ptr = hashtable[i];
        node *tmp;
        while(ptr != NULL)
        {
            tmp = ptr;
            ptr = ptr->next;
            free(tmp);
        }
    }
    return true;
}
