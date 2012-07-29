/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>

#include "dictionary.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//A comment to test git, remove me

int hash(const char *word);

char word[LENGTH +1] ;
int word_count = 0;

typedef struct node 
{
  char *word;
  struct node *next;
} node;

node *hasht[HT_SIZE];

/*
 * Returns true if word is in dictionary else false.
 */

bool
check(const char *word)
{
  char temp_word[LENGTH +1];
  node *nodep;

  //Convert to lower case

  int len = strlen(word);

  for(int i = 0; i < len; i++) {
    int low = tolower(word[i]);
    temp_word[i] = (char)low;
  }

  // Add the terminating char
  temp_word[len] = '\0';
		    

  int hv = hash(word);
  nodep = hasht[hv];
  if (!nodep ) return false;//Not even a hash node created.
  
  // Else search in list


  while( nodep ) {
    if (!strcmp(word,nodep->word)) {
	return true;
    }
    nodep = nodep->next;
  }

  return false;

}


/*
 * Loads dictionary into memory.  Returns true if successful else false.
 */

bool
load(const char *dictionary)
{
  FILE *fp = NULL;
  int hv; //Hash Value
  
  // Initialize hash table
  for (int i = 0; i<HT_SIZE; i++) {
    hasht[i] = NULL;
  }

    

  if (!(fp = fopen(dictionary, "r"))) {
      return false;
  }
  

  while (fscanf(fp,"%s\n",word) != EOF) {
      
    // Insert word into a node
    node *nodep = malloc(sizeof(node));
    nodep->word = malloc(strlen(word) +1);//Note the +1 for terminating null
    strcpy(nodep->word,word);
    
    hv = hash(word);

    printf( "%s hash = %d\n",word,hv);   
    word_count ++;
    if(hasht[hv] == NULL) { // Insert as head of list
	hasht[hv] = nodep;
	nodep->next = NULL;
    }
    else { //Insert node at head of list
	nodep->next = hasht[hv];
	hasht[hv] = nodep;
    }
	
	
  }

  printf( "Total word count = %d\n",word_count);
  
  return true;

}



/*
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */

unsigned int
size(void)
{

  return word_count;
}


/*
 * Unloads dictionary from memory.  Returns true if successful else false.
 */

bool
unload(void)
{

  // Walk hash table deleting nodes
  // Note need to delete both the node and the word pointed in the node.
  for (int i = 0; i<HT_SIZE; i++) {
      nodep = hasht[i];
      while (nodep) {
	nextnodep  = nodep->next;
	free(nodep);
	nodep = nextnodep;
       
    hasht[i] = NULL;
  }


    // TODO
    return false;
}


int hash(const char *word) 
{
  int len = strlen(word);
  int hash = 0;

  for(int i = 0; i < len; i++) {
    hash += word[i];
  }
  return hash%HT_SIZE;
}
      
