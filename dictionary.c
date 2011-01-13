#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
#include <string.h>

/* xkcd.com/844 describes this code perfectly */
/*
  the way I should have coded this was write two functions

  lookupAndReturnNode (struct dictionary *dict, char *word)
    which returns the final node that could be found
    and also the levels it has traversed (no of times it called node->child)

  generateWl (dictEdge *node, char* prefix)
    which returns a wordlist of all words under node
    and prepending the prefix

  after these two functions are written, all other functions can be called just by using these two

  lookup
    lookupAndReturnNode
    if (strlen(word) == i + 1) // i indexed from 0
      return True
    return False
  dictCompletions
    lookupAndReturnNode
    word[i+1] = 0
    generateWl (node, word);
  printdict
    generateWl (node, "")
    printwl (wl)
  insert
    lookupAndReturnNode
    while (i < strlen(word))
      node->child = dictEdgeNew(word[i + 1])
      node = node->child
      ++i

  should've written it all iteratively
*/

struct wlnode* wlRev(struct wlnode*);
void printEdge(struct dictEdge* dnode, long n);
void printDict(struct dictionary* dict) {
  printEdge(dict->root,0);
}
void printEdge(struct dictEdge* dnode, long n) {
  int i;
  if (dnode == NULL) {
    return;
  }
  for (i=0;i != n;++i)
    printf("  ");
  if (dnode->isTerminal == True) {
    printf("\033[1;33m%c\033[m\n",dnode->thisChar);
  } else {
    printf("%c\n",dnode->thisChar);

  }
  printEdge(dnode->child, n+1); 
  printEdge(dnode->sibling,n);
}

// insert into wlist and return the head
struct wlnode* 
wlIns(struct wlnode* head,char* word);

// oops, typo :)
struct wlnode*
distCompletions (struct dictionary* dict,char* word);
void
distCompletionsN (struct dictEdge* root,char* word,char *store,
  int level, struct wlnode* head);

// converts all the items in a dictionary into a linked list of words
// this isn't that bad
void
dictToWlNew (struct dictEdge* root,char *store,
  int level, struct wlnode* head) {
  if (root == NULL) 
    return;// terminating case :)
  assert(store != NULL); // store should be defined already
  int i = level + 2; 
  // space for new char + null
  store[i-1] = 0;
  store[i-2] = root->thisChar;
  if (root->isTerminal == True) {
    char *str = malloc(sizeof(char)*(level + 2)); 
    assert(str != NULL); // we have enough memory
    strcpy(str,store); // copy everything
    wlIns(head,str);
  } // do it in order :)
  dictToWlNew (root->child,store,level+1,head);
  dictToWlNew (root->sibling,store,level,head);
}

// Sorry about that, it's a bit dodgy the ordering
struct wlnode*
distCompletions (struct dictionary* dict,char* word) {
  struct wlnode* a = wlIns(NULL,"");
  char store[82];
  store[0] = 0; // do I need this? // this is stupid
  if (word[0] == 0) { // meaning that the word is blank
    dictToWlNew(dict->root,store,0,a);
  }
  else {
    distCompletionsN(dict->root,word,store,0,a);
  }
  struct wlnode* re = a->next;
  a->next = NULL;
  free(a);
  return re;
}

void
distCompletionsN (struct dictEdge* root,char* word,char *store,
  int level, struct wlnode* head) {
  if (root == NULL) {
    return; // if the root is null we are done!
  }
  assert(store != NULL); // since I declared it before
  int i = level + 2; // the array size is strlen(word)+1
  store[i-1] = 0;
  store[i-2] = root->thisChar; 
  // what this does is append root->thisChar to then end of stored string
  // FIX

  if (root->isTerminal == True) {
    if (strlen(word) - 1 == level) {
      if (word[level] == root->thisChar) {
        char *str = malloc(sizeof(char)*(level + 2));
        assert(str != NULL);
        strcpy(str,store);
        head = wlIns(head,str);
      }
    }
  }

  if (root->isTerminal == True // signifying end of word
    && (word[level] == root->thisChar || level >= strlen(word)) 
    && (level >= strlen(word) )) { 
    
    if (strlen(store) == 0) {
      return; // since the string is empty, we don't add it
    }
    char *str = malloc(sizeof(char)*(level + 2));
    assert(str != NULL);
    strcpy(str,store);
    head = wlIns(head,str);
  } // just because we added a word doesn't mean we're finished!

  if (level < strlen(word) && word[level] == root->thisChar) {
    // case what we're looking for is directly below
    
    distCompletionsN (root->child,word,store,level+1,head);
  } else if (level >=strlen(word)) {
    // if we've already 'made it' past checking the word
    // level is 0 indexed, strlen starts at 1 (so to speak)
    // hence the equality
    distCompletionsN (root->child,word,store,level+1,head);
    // since I add child first, it is in ORDER :)
    distCompletionsN (root->sibling,word,store,level,head);
  } else {
    // go onto the next sibling then
    distCompletionsN (root->sibling,word,store,level,head);
  } 
  /* these three cases

  */
}
// just to test out a few algorithms.
struct wlnode* 
wlIns(struct wlnode* head,char* word);
void 
insertWordR (struct dictEdge * node, char* word);
bool
dictLookupN (struct dictEdge* node,char* word) ;
void
edgeFree(struct dictEdge *node);
struct dictEdge* dictEdgeNew(char thisChar);
void 
printDict(struct dictionary *dict);

/* Initialise the dictionary structure
 */
struct dictionary*
dictInit () {
  // we create a new dictionary and then we return it
  struct dictionary* ndict = malloc(sizeof(struct dictionary));
  assert(ndict != NULL); 
  ndict->root = NULL;
  return ndict;
}

struct dictEdge* 
dictEdgeNew(char thisChar) {
  struct dictEdge *ndictEdge = malloc(sizeof(struct dictEdge));
  assert(ndictEdge != NULL);
  ndictEdge->thisChar = thisChar;
  ndictEdge->child = NULL;
  ndictEdge->sibling = NULL;
  ndictEdge->isTerminal = 0;
  return ndictEdge;
}
    
/* Insert a single word into the dictionary 
 */
void
dictInsertWord (struct dictionary* dict, char* word) {
  // assume I'm not in the list.
  if (dict->root == NULL) {
    dict->root = dictEdgeNew(word[0]);
  }
// todo this code still seems bugged like fuck
  // oh my this is icky
  // well, I suppose it's required though
  if (dict->root->thisChar > word[0]) {
    struct dictEdge* newp = dictEdgeNew(word[0]);
    newp->sibling = dict->root;
    dict->root = newp;
  } 
  assert(dict->root->thisChar <= word[0]); // make sure that the root is okay :)
  insertWordR (dict->root, word); 
}


// the amount of time this takes is dependant both on size of word and size of trie

void 
insertWordR (struct dictEdge * node, char* word) {
  assert(node != NULL);
  // oh I remember again, to prevent against sloppy code ;)
  // passing a null edge is silly
  // should've done this iteratively
  bool found = False; // since I need to break out two levels
  struct dictEdge* roverPapa = NULL;
  if (word[0] != '\0') {
    struct dictEdge* rover = node;
    if (node->thisChar > word[0]) { // just checking the structure
      assert (node->thisChar <= word[0]);
    }
    while (rover != NULL && !found) {
      // we search until we find a match or not
      // if we've found the place to put it
      if (rover->thisChar > word[0]) {
        // ie it's not in the list, since we assume it's ordered
        // insert it in order
        assert(roverPapa != NULL);
        struct dictEdge* newp = dictEdgeNew(word[0]);
        // dodgy, I meant roverYoungerSibling
        roverPapa->sibling = newp;
        newp->sibling = rover;
        
        // recurse.
        if (word[1] == 0) {
          newp->isTerminal = True;
        } else {       
          // since we added a new node, it has no children, we make one :)
          struct dictEdge* newcp = dictEdgeNew(word[1]);
          newp->child = newcp;
          insertWordR(newcp,&word[1]);
        }
        return;
      }
      if (rover->thisChar == word[0]) {
        found = True; // we've found the word, and rover now holds this
      } else {
        roverPapa = rover;
        rover = rover->sibling;
      }
    }
    // we add it to the end of the siblingsList ;)
    if (found == False) { // not found :) && not placed in order
      // fprintf(stderr,"not found with arg %s\n",word);
      // just add the whole word in.
      rover = node; 
      while (rover->sibling != NULL) {
        rover = rover->sibling;
      }
      rover->sibling = dictEdgeNew(word[0]);
      node = rover->sibling;

      int i = 1;
      struct dictEdge* rover = node;
      while (word[i] != 0) {
         rover->child = dictEdgeNew(word[i]);      
         ++i;
         if (word[i] == '\0') {
           rover->child->isTerminal = True;
         }
         rover = rover->child;
       }
       if (i == 1) { 
       // we didn't enter loop
       // then the node is the final element
         node->isTerminal = True;
       } // seems to make sense to put this at the front :) 
       // case for notentering the loop
       // could just use, rover->isTerminal = True it 'should' work
     }
     else { 
      // found == True
      if (rover->child != NULL) {
        if (word[1] == '\0') { 
           rover->isTerminal = True; 
        }
        else {
          // inorderFix, create the node and set the pointer
          if (rover->child->thisChar > word[1]) {
            // if we need to insert it at the beginning
            struct dictEdge* newp = dictEdgeNew(word[1]);
            newp->sibling = rover->child;
            rover->child = newp;
          }
          insertWordR(rover->child,&word[1]); 
        }
      }
      else {
        if (word[1] == '\0') { 
           rover->isTerminal = True;
        }
        else {
           rover->child = dictEdgeNew(word[1]);
           insertWordR(rover->child,&word[1]);
           // this could be done with a forloop
           // since all we're doing is spawning children
        }
      }
    }
  }
}

/* Insert a list of words into the dictionary 
 */
void
dictInsertWords (struct dictionary* dict, struct wlnode* words) {
  while (words != NULL) {
    dictInsertWord(dict,words->word); // icky
    words = words->next;
  }
}

/* Check whether a given word is in the dictionary
 */
bool
dictLookup (struct dictionary* dict, char* word) {
  // is there a more efficient way.
  // by using two loops, this can be implemented
  // thanks to Ian Craig who showed me :)
  if (dict == NULL) {
    return False; // or should I throw an error?
  }
  return dictLookupN(dict->root,word);
}

// n for internal? new?
bool
dictLookupN (struct dictEdge* node,char* word) {
  // todo this code still seems bugged like fuck
  // terminating case. // dictionary/word is NULL/\0
  if (node == NULL) {
    // very special case, dictionary is empty, clearly not in dictionary
    return False;
  }
  if (word[0] == 0) { // shouldn't really go in here... 
    return False;
  }

  if (word[1] == '\0') {  // if it's the last letter
      struct dictEdge *rover = node;
      //printf("searching for %c %c\n",word[0],rover->thisChar);
      // while (word[0] < rover->thisChar && rover->sibling != NULL) 
      // while (rover->sibling != NULL && word[0] < rover->thisChar) // damn I had this, it's broken so badly 
      while (rover->sibling != NULL && word[0] > rover->thisChar) 
      {
        rover = rover->sibling;
      }
      if (word[0] == rover->thisChar && rover->isTerminal == True) {
        return True;
      }
      return False;
  }
  struct dictEdge *rover = node;
  while (rover != NULL) { // could be 'optimized'
    if (word[0] == rover->thisChar) {
      // if we are here we know that word[1] != 0
      // therefore we have not finished
      if (rover->child == NULL) {
        return False; // no more children, therefore it can't be found
      }
      return dictLookupN(rover->child,&word[1]); // move to the subproblem :)
    } else {
      rover = rover->sibling;
    }
  }
  // if it gets here it means no matches in the siblings
  return False;
}

bool
dictLookupIter (struct dictionary* dict, char* word) {
  int i = 0; // loop through elements of the word (counts what letter we're on
  struct dictEdge* node = dict->root;
  struct dictEdge* rover;
  while (i != strlen(word)) {
    for (rover = node;
      rover != NULL;
      rover = rover->sibling) {
      if (word[i] == rover->thisChar) { // if equal
        if (word[i + 1] == 0) { 
          if (rover->isTerminal) {
            return True;
          }
        }
        node = rover->child;
        break; // break out of loop
      }
      // if we've reached the end of the word and we haven't found it then
      if (rover->sibling == NULL || word[i] < rover->thisChar) {
        // don't really need the second one but saves time
        return False;
      }
    }
    ++i; // look up the next letter with parent node
  }
  return False;
}

/* Extract all words in the dictionary (the order does not matter).
 * Should return them in alphabetical order
 * Complexity: see constraint in the assignment specification.
 */
struct wlnode*
dictCompletions (struct dictionary* dict, char* word) {
  return wlRev(distCompletions(dict,word)); // fun fix
  // return distCompletions(dict,word);
}

/* testing functions for the above */
void
printwl (struct wlnode* wl) {
   struct wlnode * cur;
   for (cur = wl; NULL != cur; cur =  cur->next)
      fprintf (stdout, "%s\n", cur->word);
}

/* Erase all dictionary entries and release all memory allocated for the
 * dictionary.
 */
// Complexity O(n) // linearly dependant on size of trie
void
dictFree (struct dictionary* dict) {
  // free all the nodes then free the dictionary
  edgeFree(dict->root);
  dict->root = NULL;
  free(dict); // freeing the dictionary is easy
}

// recursively free all the nodes
// Complexity O(n) // linearly dependant on size of trie
void
edgeFree(struct dictEdge *node) {
  if (node != NULL) {   
    edgeFree(node->sibling);
    edgeFree(node->child);
    node->sibling = NULL; // null out the pointers
    node->child = NULL;
    free(node);
  }
}

/* Return the root of the trie (i.e. dictionary). 
 * If the dictionary is empty, then return NULL. 
 * Otherwise, return the root of the trie. 
 */ // complexity O(1)
struct dictEdge*
dictGetRoot (struct dictionary* dict) { 
  return dict->root;
}

// word list functions below :)
/* This function does NOT do what it says on the tin */
// due to the fact that the initial complexity was O(n)
// Complexity, O(1)
// I was thinking of moving the mallocing to this function but then thought
// I might break something
/* This function inserts a word by reference in the second position, (or first if wlnode is NULL */
struct wlnode* 
wlIns (struct wlnode* wl, char* word) {
  struct wlnode* new = malloc(sizeof(struct wlnode));
  assert(new != NULL);
  // since we store the first node with dictCompletion
  new->word = word;
  if (wl == NULL) {
    new->next = wl;
    wl = new;
  }
  else {
    new->next = wl->next;
    wl->next = new;
  }
  return wl;
}

// Operation Complexity O(n)
// Space Requirement, O(1)
// In place reversing of a linked list
struct wlnode* 
wlRev(struct wlnode* wl) {
  // done in lab 1
  struct wlnode* new = wlIns(NULL,"");
  struct wlnode* rover = wl;
  while (rover != NULL) {
    // do I get better performance if I store this variable outside the loop?
    struct wlnode* store = rover->next; 
    rover->next = new->next;
    new->next = rover;
    rover = store; 
  }
  rover = new->next; // saves defining another variable :)
  new->next = NULL;
  free(new);
  return rover;
}

