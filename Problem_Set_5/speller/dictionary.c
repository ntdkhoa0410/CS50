// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

//Global variable of word count
unsigned int word_count = 0;
void free_list(node* head);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    unsigned int index = hash(word);
    if (table[index] == NULL){
        return false;
    }
    else {
        node* temp  = table[index];
        while (temp!= NULL){
            if (strcasecmp(temp->word, word) == 0){
                return true;
            }
            temp = temp->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    return toupper(word[0]) - 'A';
}

void add_new_node(int index, char *word){
    node* new_node = malloc(sizeof(node));
    strcpy(new_node->word, word);
    if (table[index] == NULL){
        new_node->next = NULL;
    }
    else {
        new_node->next = table[index];
    }
    table[index] = new_node;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // I check if the file is opened correctly
    FILE *file = fopen(dictionary,"r");
    char new_word[LENGTH + 1];
    if (!file){
        return false;
    }
    else {
        //Go through each word and hash them

        while (fscanf(file,"%s", new_word)!=EOF){
            unsigned int index = hash(new_word);
            word_count ++;
            //Create new node for the new word
            add_new_node(index, new_word);
        }
        //Closing after open the file
        fclose(file);
        return true;
    }
    return true;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}
void free_list(node* head){
    if(head->next!=NULL){
        free_list(head->next);
    }
    free(head);
}
// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++){
        if (table[i]!=NULL){
            free_list(table[i]);
        }
    }
    return true;
}
