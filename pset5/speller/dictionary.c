// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// dictionary size
int dictionarySize = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    //save word in temp location
    char temp[LENGTH + 1];
    //get length
    int len = strlen(word);
    //loop through the word and assign to temp
    for (int i = 0; i < len; i++)
    {
        temp[i] = tolower(word[i]);
    }
    //assign temp last index end line
    temp[len] = '\0';

    //find word array index
    int index = hash(temp);

    //if table index is empty return false
    if (table[index] == NULL)
    {
        return false;
    }
    // allocate memory to our cursor
    node *cursor = table[index];
    //loop if cursor is not equal null
    while (cursor != NULL)
    {
        //use strcasecmp to compare words and be case insensitive
        if (strcmp(temp, cursor->word) == 0)
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
    // TODO
    int index;
    //check if the first index of word is alpha
    if (isalpha(word[0]))
    {
        //convert to lower case and return ascii as index
        index = tolower(word[0] - 'a' + 1);
        return index;
    }
    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    //open dictionary
    FILE *file = fopen(dictionary, "r");
    //check if file is null
    if (file == NULL)
    {
        return false;
    }
    //create word array
    char word[LENGTH + 1];
    //loop and Read Strings from file
    while (fscanf(file, "%s", word) != EOF)
    {
        //keep track of dictionary size by appending every scanned file
        dictionarySize++;
        //init new node using malloc
        node *new_node = malloc(sizeof(node));
        //copy word into new node using strcpy
        strcpy(new_node->word, word);
        //use the hash function to get an index integer
        int hashed = hash(word);

        // if hashtable is empty at index, insert
        if (table[hashed] == NULL)
        {
            table[hashed] = new_node;
            new_node->next = NULL;
        }// if hashtable is not empty at index, append
        else
        {
            new_node->next = table[hashed];
            table[hashed] = new_node;
        }


    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dictionarySize;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    int index = 0;
    //loop through hashtable
    while (index < N)
    {
        //check if hashtable index is null and move to next index
        if (table[index] == NULL)
        {
            index++;
        }
        else
        {
            while (table[index] != NULL)
            {
                //else create pointer to index
                node *cursor = table[index];
                //move to next index
                table[index] = cursor->next;
                //free index memory
                free(cursor);
            }
            //move to next index
            index++;
        }
    }
    return true;
}
