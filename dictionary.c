#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <dictionary.h>/*
struct wlnode
{
  char* word;
  struct wlnode * next;
};

struct lnode
{
  char* word;
  struct lnode* next;
};

*/

/* Initialise the dictionary structure
 */

struct dictEdge* dictEdgeNew(char thisChar);

struct dictionary*
dictInit () {
  // we create a new dictionary
  // and then we return it
  struct dictionary* ndict = malloc(sizeof(struct dictionary));
  ndict->root = dictEdgeNew('\0');
  ndict->root = dictEdgeNew('\0');
  ndict->root = dictEdgeNew('y');
  return ndict;
}

void printDict(struct dictionary* dict) {
  printf("%p",&dict);
  assert(dict->root != NULL);
  printf("%c",dict->root->thisChar);
}

struct dictEdge* dictEdgeNew(char thisChar) {
  struct dictEdge *ndictEdge = malloc(sizeof(struct dictEdge));
  assert(ndictEdge != NULL);
  ndictEdge->thisChar = thisChar;
  return ndictEdge;
}
/* Insert a single word into the dictionary 
 */
void
dictInsertWord (struct dictionary* dict, char* word);

/* Insert a list of words into the dictionary 
 */
void
dictInsertWords (struct dictionary* dict, struct wlnode* words);

/* Check whether a given word is in the dictionary
 */

bool
dictLookup (struct dictionary* dict, char* word);

/* Extract all words in the dictionary (the order does not matter).
 *
 * Complexity: see constraint in the assignment specification.
 */
struct wlnode*
dictCompletions (struct dictionary* dict, char* word);

/* Erase all dictionary entries and release all memory allocated for the
 * dictionary.
 */
void
dictFree (struct dictionary* dict);

/* Return the root of the trie (i.e. dictionary). 
 * If the dictionary is empty, then return NULL. 
 * Otherwise, return the root of the trie. 
 */ 
struct dictEdge*
dictGetRoot (struct dictionary* dict) ; 



