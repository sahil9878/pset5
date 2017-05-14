/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"

// dectalion of string to store words from dictionary
#define HASHTABLE 27
char WORD[LENGTH + 1];
typedef struct node
{
    char *word;
    struct node* next_node;
}
node;
node *list [HASHTABLE];
int hashf(const char*node);
/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
  
    int trgt = hashf(word);
    
    // Declaring a temporary node pointer to check misspelled words
    node* temp = list[trgt];
    
    // Searching word in the target list 
    while (temp != NULL)
    {
        // comparing without case sensitivity
        if (strcasecmp (temp->word, word) == 0)
        {
            return true;
        }
        // switching to next node
        temp = temp->next_node;
    }

    return false;
}
// counter to count the number of words in dictionary

int dicounter;
/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // open the dictionary file 
    FILE* dict = fopen(dictionary, "r");
    
    // to check any case of failure while opening file
    if (dict == NULL)
    {
        return false;
    }

    // iterating word by word through the dictionnary
    while (fscanf(dict, "%s\n", WORD) != EOF)
    {
        // Allocating memory for a new node
        node *nodeb = malloc(sizeof(node));

        int strln = strlen(WORD);
        
        // Allocating memory to hold a New word
        nodeb->word = (char* ) malloc(strln + 1);
        
        // Copying word to node's element
        strcpy(nodeb->word, WORD);
        
        // hashing the word
        int hashed = hashf(WORD);

        // In case the head of this linked list is empty
        if (list[hashed] == NULL)
        {
            list[hashed] = nodeb;
            
            nodeb->next_node = NULL;
        }
        
        else
        {
            nodeb->next_node = list[hashed];
            
            list[hashed] = nodeb;
        }
        // incrementing counter after loading each word in dict
        dicounter++;
    }
    // Closing file
    fclose(dict);
    // success
    return true;
    printf("%d",dicounter);
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
   // returning total loaded words.
    return dicounter;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0; i < HASHTABLE; i++)
    {
        // Initiating refpt to move inside all lists
        node *refpt = list[i];
        
        // Clearing all the allocated memory
        while (refpt != NULL)
        {
            node* temp1 = refpt;
            
            char* temp2 = refpt->word;
            
            refpt = refpt->next_node;
            
            // freeing all the memory reserved by node elements
            free(temp1);
            
            free(temp2);
        }
    }
    return true;
}
// hash function
int hashf(const char* word)
{
    int index = 0;
    // finding out index value
    for (int i = 0; word[i] != '\0'; i++)
    {
        index = index + tolower(word[i]);
    }
    
    // mod by size to stay within limits
    index = index % HASHTABLE;

    return index;
}