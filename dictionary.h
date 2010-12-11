/* COMP1927 - Dictionary interface 
 *
 * DO NOT MODIFY!
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H
/* Boolean values
 */
typedef enum
{
  False,
  True
}
bool;

#include <dictionary_type.h>
/* Linked list of words
 */	

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



/* Initialise the dictionary structure
 */
struct dictionary*
dictInit ();

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

#endif /* ! DICTIONARY_H */


