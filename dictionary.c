#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
#include <string.h>

/* Initialise the dictionary structure
 */

void 
perr(char error[]) {
#define DEBUGP
#ifdef DEBUGP
  fprintf(stderr,"%s\n",error);
#endif
}


/* 
  unused functions
  used as a basis for the final functions :)
    */
void dictTrav(struct dictEdge* root);
void dictTrav(struct dictEdge* root) {
  // recursive first.
  if (root == NULL)
    return;
  printf("%c ",root->thisChar);
  dictTrav(root->child);
  dictTrav(root->sibling);
}

void 
dictList(struct dictionary* dict);
void 
dictListN(struct dictEdge* root,char* word,int level);
struct wlnode*
dictToWl(struct dictEdge* root,char* word,int level,struct wlnode* head);
void 
dictList(struct dictionary* dict) {
  dictListN(dict->root,NULL,0);
}
void dictListN(struct dictEdge* root,char* word,int level) {
  if (root == NULL)
    return;
  printf("%p\n",root);
  // word
  /*
  if (root->isTerminal == True) {
    printf("ISTERMINAL PRINTING OUT WORD len(%d)\n",strlen(word));
    printf("%s\n",word);
  } */

  dictListN(root->sibling,word,level);
 // if (root->thisChar == 0)
 // return; 
  assert(root->thisChar != '\0');

  if (word == NULL) {
//    word = malloc(sizeof(char)*2);
    word = malloc(sizeof(char)*82);
    assert(word != NULL);
    // *word = sprintf("%c\0",root->thisChar);
    word[0] = root->thisChar;
    // printf(">%c<",root->thisChar);
    word[1] = 0;
  } else {
    int i = level + 2; // the array size is strlen(word)+1
//    word = realloc (word, sizeof(char)*(i));
    word[i-1] = 0;
    word[i-2] = root->thisChar;
//    printf("ATTEMPTING TO REALLOC for >%c<",root->thisChar);
    // add the char to the end of word, and/or move the pointer:)
    // printf("%d vs %d\n",i,strlen(word));
  }
  if (root->isTerminal == True) {
    printf("ISTERMINAL PRINTING OUT WORD len(%d)\n",strlen(word));
    printf("%s\n",word);
  }
  dictListN(root->child,word,level+1);
}

/* begining of true functions */

struct wlnode* 
wlIns(struct wlnode* head,char* word);

struct wlnode*
dictToWl(struct dictEdge* root,char* word,int level,struct wlnode* head) {
  if (root == NULL) { // for some reason this works
    return head;
  }
  if (word == NULL) {
    word = malloc(sizeof(char)*2);
    assert(word != NULL);
    word[0] = root->thisChar;
    word[1] = 0;
  } else {
    int i = level + 2; // the array size is strlen(word)+1
    word = realloc (word, sizeof(char)*(i));
    word[i-1] = 0;
    word[i-2] = root->thisChar;
  }
  if (root->isTerminal == True) {
    //printf("adding word %s\n",word);
    char *str = malloc(sizeof(char)*(level + 2));
    assert(str != NULL);
    strcpy(str,word);
    head = wlIns(head,str);
  }
  dictToWl(root->child,word,level+1,head);
  dictToWl(root->sibling,word,level,head);
  return head;
}
// oop, typo :)
struct wlnode*
distCompletions (struct dictionary* dict,char* word);
void
distCompletionsN (struct dictEdge* root,char* word,char *store,
  int level, struct wlnode* head);

struct wlnode*
distCompletions (struct dictionary* dict,char* word) {
  struct wlnode* a = wlIns(NULL,"hi angel");
  char store[82];
  distCompletionsN(dict->root,word,store,0,a);
//  return a;
// if I want to see where the gap is between words
  struct wlnode* re = a->next;
  a->next = NULL;
  free(a);
  return re;
}

void
distCompletionsN (struct dictEdge* root,char* word,char *store,
  int level, struct wlnode* head) {
//  if (root == NULL || root == 0x19) { // for some reason this works
  if (root == NULL) {
    // free(store);
    return;
  }
  if (store == NULL) {
    //store = malloc(sizeof(char)*2);
    store = malloc(sizeof(char)*82);
    assert(store != NULL);
    store[0] = root->thisChar;
    store[1] = 0;
  } else {
    int i = level + 2; // the array size is strlen(word)+1
    //store = realloc (store, sizeof(char)*(i));
    store[i-1] = 0;
    store[i-2] = root->thisChar;
  }
  // FIX
  if (root->isTerminal == True) {
    if (strlen(word) - 1 == level) {
      if (word[level] == root->thisChar) {
        // oh my. this is a bug :)
        char *str = malloc(sizeof(char)*(level + 2));
        assert(str != NULL);
        strcpy(str,store);
        //head = wlIns(head,str);
        head = wlIns(head,str);
      }
    }
  }

  if (root->isTerminal == True) {
    if (strlen(word) - level == 1 && word[level] == root->thisChar) {
      printf("maybe I should add %s level: %d\n",word,level);
    }
  }
  if (root->isTerminal == True 
    && (word[level] == root->thisChar || level >= strlen(word))
    && (level >= strlen(word) )) { 
    if (strlen(store) == 0) {
      // free(store);
      assert(1 != 0);
      return;
//      this looks like a bug
    }
    printf("adding store %s\n",store);
    char *str = malloc(sizeof(char)*(level + 2));
    assert(str != NULL);
    strcpy(str,store);
    printf("adding str %s %p len: %d\n",str,str,strlen(str));
    head = wlIns(head,str);
  }
  if (level < strlen(word) && word[level] == root->thisChar) {
   // printf("we have a hit for %c!\n",word[level]);
    distCompletionsN (root->child,word,store,level+1,head);
  } else if (level >=strlen(word)) {
    // printf("here");
    distCompletionsN (root->child,word,store,level+1,head);
    // since I add child first, it is in ORDER :)
    distCompletionsN (root->sibling,word,store,level,head);
  } else {
    distCompletionsN (root->sibling,word,store,level,head);
  }
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

struct dictionary*
dictInit () {
  // we create a new dictionary
  // and then we return it
  struct dictionary* ndict = malloc(sizeof(struct dictionary));
  // ndict->root = dictEdgeNew('\0');
  ndict->root = NULL;
 // ndict->root = dictEdgeNew('y');
  return ndict;
}

void printEdge(struct dictEdge* dnode, long n);
void printDict(struct dictionary* dict) {
  printEdge(dict->root,0);
  return;
  printf("%p",&dict);
  if (dict->root == NULL) {
    return;
  }
  assert(dict->root != NULL);
  printf("%c",dict->root->thisChar);
}

void printEdge(struct dictEdge* dnode, long n) { // attempt to create a PreOrde
  if (dnode == NULL) {
    return;
  }
  int i;
  //printf("%li\n",n);

  for (i=0;i != n;++i)
    printf("  ");
  
  if (dnode->isTerminal == True) {
    //printf("TERMIN");
    printf("\033[1;33m%c\033[m\n",dnode->thisChar);
  } else {
    //printf("%c.%d\n",dnode->thisChar,n);
    printf("%c\n",dnode->thisChar);

  }
  /*
  if (dnode->thisChar == '\0') {
    // we are at the root node :)
    // print a * for fun
    printf("*\n");
  } */ // FOR FUCKS SAKE FIX
  printEdge(dnode->child, n+1); 
  printEdge(dnode->sibling,n);
  return;
  struct dictEdge * rover = dnode;
  while (rover->sibling != NULL) {
    //printf("%c ",rover->thisChar);
    printEdge(rover->sibling, n);
    rover = rover->sibling;
  }
}

struct dictEdge* dictEdgeNew(char thisChar) {
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
  // make sure I can actually do operations on the word.
/*  printf("%d",strlen(word));
  int i = 0;
  while (word[i] != 0) {
    printf("%c\n",word[i]);
    ++i;
  } */
  
  // assume I'm not in the list.
  if (dict->root == NULL) {
    dict->root = dictEdgeNew(word[0]);
  }

  // oh my FUCK this is icky
  if (dict->root->thisChar > word[0]) {
    perr("noes :( fixing node");
    struct dictEdge* newp = dictEdgeNew(word[0]);
    newp->sibling = dict->root;
    dict->root = newp;
  }
  else {
    //perr("yays ;)");
  }
  printf("comparing %d with %d\n",dict->root->thisChar,word[0]);
  //printf("OH MY GOSH FUCK YOU");

  insertWordR (dict->root, word); 
  return;

  int i = 0;
  struct dictEdge* rover = dict->root;
  while (word[i] != 0) {
    rover = dict->root;
    while (rover->child != NULL) {
      rover = rover->child;
    }
    rover->child = dictEdgeNew(word[i]);
    printf("new child pointing to %p\n",rover->child);
    //dict->rootword[i];
    ++i;
  }
}

void 
insertWordR (struct dictEdge * node, char* word) {
  assert(node != NULL);
// oh I remember again, to prevent against sloppy code ;)
// passing a null edge is silly

// forgot why I had this assertion :$
/*
  if (word[1] == 0) {
    node->isTerminal = True;
  } */
  // FIX
  // Forgot about insert in order
  /*
  if (word[0] == 0) {
    // terminating
    printf("a triggering\n");
    node->isTerminal = True;
    return;
  }
  */
  printf("input string-> %s\n",word);
  char first = word[0];
  bool found = False;
  
  struct dictEdge* roverPapa = NULL;
  //stopping case, word[0] == \0
  if (word[0] != '\0') {
    struct dictEdge* rover = node;
  
    if (node->thisChar > word[0]) {
      perr("we have a fucking problem");
      assert(1 == 0);
    }

    while (rover != NULL && !found) {
      // we search until we find a match or not
      
// new
      if (rover->thisChar > word[0]) {
        // ie it's not in the list, since we assume it's ordered

        // insert it in order
        assert(roverPapa != NULL);
        struct dictEdge* newp = dictEdgeNew(word[0]);
        roverPapa->sibling = newp;
        newp->sibling = rover;
        
        // recurse.
        if (word[1] == 0) {
          newp->isTerminal = True;
        } else {       
          struct dictEdge* newcp = dictEdgeNew(word[1]);
          newp->child = newcp;
          insertWordR(newcp,&word[1]);
        }
        return;

      }

      if (rover->thisChar == first) {
        found = True;
        // printf("FOUND YAY");
      } else {
        roverPapa = rover;
        rover = rover->sibling;
      }
    }
    if (found == False) { // not found :)
      printf("not found with arg %s\n",word);
      // just add the whole word in.
      rover = node; 
      while (rover->sibling != NULL) {
        rover = rover->sibling;
      }
      rover->sibling = dictEdgeNew(word[0]);
      node = rover->sibling;

      int i = 1;
      while (word[i] != 0) {
        struct dictEdge* rover = node;
        int j;
        for (j=0;j<i-1;j++) {
          assert(rover->child != NULL);
          rover = rover->child;
        }
        rover->child = dictEdgeNew(word[i]);      
     //  printf("new child pointing to %p\n",rover->child);
      //dict->rootword[i];
         ++i;
         if (word[i] == '\0') {
           rover->child->isTerminal = True;
       }
       if (i == 1) { // bug fix.
    // we didn't enter loop
    // then the node is the final element
         node->isTerminal = True;
         } // seems to make sense to put this at the front :) 
       }

     }
     else {
      // looks like a bug here;
      if (rover->child != NULL) {
        if (word[1] == '\0') { 
           rover->isTerminal = True; 
        }
        else {
          // new FIX
          if (rover->child->thisChar > word[1]) {
            // we need to create
            struct dictEdge* newp = dictEdgeNew(word[1]);
            newp->sibling = rover->child;
            rover->child = newp;
          }
          insertWordR(rover->child,&word[1]); 
        }
      }
      else {
        printf("->>%s\n",word);
        if (word[1] == '\0') { 
//         printf("WHY ISN'T THIS WORKING");
           //return;
           rover->isTerminal = True;
        }
        else {
           rover->child = dictEdgeNew(word[1]);
           insertWordR(rover->child,&word[1]);
        }
      }
    }
  }
 return;
}

/* Insert a list of words into the dictionary 
 */
void
dictInsertWords (struct dictionary* dict, struct wlnode* words) {
  // UNTESTED
  // FIX
  while (words != NULL) {
    dictInsertWord(dict,words->word);
    words = words->next;
  }
  
}

/* Check whether a given word is in the dictionary
 */

bool
dictLookup (struct dictionary* dict, char* word) {
  // TODO: this
  // is there a more efficient way.
  // FIX
  // I will recursively define it.
  // UNTESTED
  char first = word[0];
  struct dictEdge *rover = dict->root;
  while (rover != NULL) { 
  if (first == rover->thisChar) {
    return dictLookupN(rover->child,&word[1]);
  } else {
    // USE A GOTO :D

  }
  rover = rover->sibling;
  }
  // still have a lot to do with this one.
  return False;
}

// n for internal? new?
bool
dictLookupN (struct dictEdge* node,char* word) {
  // terminating case.
  //return False; 
  // this code is good :)
  if (word[1] == '\0') {
    if (node->isTerminal == True) {
      return True;
    } else {
      return False;
    }
  }
  bool found = False;
  char first = word[0];
  struct dictEdge *rover = node;
  while (rover != NULL) { 
    if (first == rover->thisChar) {
      return dictLookupN(rover->child,&word[1]);
    } else {
      rover = rover->sibling;
    }
  }
  if (!found) {
    return False;
  } else {
    // return dictLookupN(rover->child,&word[1]);
  }
  assert(1 != 1); // I don't think I should by here
  return False;
}

/* Extract all words in the dictionary (the order does not matter).
 *
 * Complexity: see constraint in the assignment specification.
 */
struct wlnode*
dictCompletions (struct dictionary* dict, char* word) {
//  struct wlnode * re = NULL;

  // return re;
  return distCompletions(dict,word);
}

/* testing functions for the above */
void
printwl (struct wlnode* wl) {
  /*
   struct wlnode * cur;
   for (cur = wl; NULL != cur; cur =  cur->next)
      fprintf (stdout, "%s\n", cur->word);
      */
   struct wlnode * cur;
   cur = wl;
   //while (cur != NULL && cur != 0x65646e61) {
   while (cur != NULL) { 
       cur = cur->next;
       printf("cur %p\n",cur);
   }
   //return;
   //for (cur = wl; NULL != cur && cur != 0x65646e61; cur = cur->next)
   for (cur = wl; NULL != cur; cur = cur->next)
      fprintf (stdout, "%s %p\n", cur->word, cur->word);
}


/* Erase all dictionary entries and release all memory allocated for the
 * dictionary.
 */
void
dictFree (struct dictionary* dict) {
  // the plan, free all the nodes then free the dictionary :)

  /*
  struct dictEdge* rover = dict->root;
  rover->thisChar = '\0'; // just for fun
  rover->thisChar = '\0'; // just for fun
  rover->thisChar = '\0'; // just for fun

  while (rover->sibling != NULL) {
    edgeFree(rover->sibling);
    rover = rover->sibling;
  }
  */
  edgeFree(dict->root);

  // free the dictionary is easy
  free(dict);
}

// internal call

// recursively free all the nodes
void
edgeFree(struct dictEdge *node) {
  if (node != NULL) {   
    edgeFree(node->sibling);
    edgeFree(node->child);
    free(node);
  }
}

/* Return the root of the trie (i.e. dictionary). 
 * If the dictionary is empty, then return NULL. 
 * Otherwise, return the root of the trie. 
 */ 
struct dictEdge*
dictGetRoot (struct dictionary* dict) { 
  return dict->root;
}

// word list functions below :)

struct wlnode* 
wlIns (struct wlnode* wl, char* word) {
  // I am a singularly linked list
  printf("inserting word %s %p\n",word,word);
  if (wl == NULL) {
    struct wlnode* new = malloc(sizeof(struct wlnode));
    assert(new != NULL);
    new->word = word;
    new->next = NULL;
    return new;
  }
  else {
    struct wlnode* rover = wl;
    // assert(rover != NULL);
//    printwl(rover);
// dcollien what's wrong with this line?
    while (rover->next != NULL) {
      rover = rover->next;
    }
    struct wlnode* new = malloc(sizeof(struct wlnode));
    rover->next = new;
    new->next = NULL;
    new->word = word;
    assert(new != NULL);
    return wl;
  }
}
/*
void
wlPrint (struct wlnode* wl) {
  printf("starting wlprint\n");
  while (wl != NULL) {
    printf("%s\n",wl->word);
    wl = wl->next;
  }
} */ // silly me :(

void
wlfree (struct wlnode* wl) {
  if (wl == NULL) {
    return;
  }
  wlfree(wl->next);
//  free(wl->word);
// why don't I have to free the pointer to the word?
  // free(wl->word);
  free(wl);
}
