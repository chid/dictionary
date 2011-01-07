#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
#include <string.h>

/* Initialise the dictionary structure
 */

struct wlnode* wlRev(struct wlnode*);
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
#if 0

void printDict(struct dictionary* dict) {
  printEdge(dict->root,0);
  return;
}

void 
dictList(struct dictionary* dict);

void 
dictListN(struct dictEdge* root,char* word,int level);

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
#endif
/* begining of true functions */

// insert into slist and return the head
struct wlnode* 
wlIns(struct wlnode* head,char* word);

// oop, typo :)
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
  store[i-1] = 0;
  store[i-2] = root->thisChar;
  if (root->isTerminal == True) {
    char *str = malloc(sizeof(char)*(level + 2)); 
    // space for new char + null
    assert(str != NULL); // we have enough memory
    strcpy(str,store); // copy everything
    wlIns(head,str);
  } // do it in order :)
  dictToWlNew (root->child,store,level+1,head);
  dictToWlNew (root->sibling,store,level,head);
}

struct wlnode*
distCompletions (struct dictionary* dict,char* word) {
//  printf("strlen of word is %d\n",strlen(word));return;
  struct wlnode* a = wlIns(NULL,"hi");
  char store[82];
  // this is stupid
  if (word[0] == 0) { // meaning that the word is blank
    // printf("doing old routine");
    dictToWlNew(dict->root,store,0,a);
  //  return a->next;
  }
  else {
    distCompletionsN(dict->root,word,store,0,a);
  }
  // if I want to see where the gap is between words
  struct wlnode* re = a->next;
  a->next = NULL;
  free(a);
  return re;
}

void
distCompletionsN (struct dictEdge* root,char* word,char *store,
  int level, struct wlnode* head) {
  if (root == NULL) {
    // free(store);
    return;
  }
  assert(store != NULL);
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
        char *str = malloc(sizeof(char)*(level + 2));
        assert(str != NULL);
        strcpy(str,store);
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
/*    char test[level + 2];
    char *str;
    str = test; */ // this code doesn't seem to work at all :(
    assert(str != NULL);
    strcpy(str,store);
//    printf("adding str %s %p len: %d\n",str,str,strlen(str));
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
    
void printEdge(struct dictEdge* dnode, long n) {
  if (dnode == NULL) {
    return;
  }
  int i;
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
    perr("noes :( fixing node");
    struct dictEdge* newp = dictEdgeNew(word[0]);
    newp->sibling = dict->root;
    dict->root = newp;
  } // TODO, make sure this won't leave any extra nodes
//  printf("comparing %d with %d\n",dict->root->thisChar,word[0]);
  assert(dict->root->thisChar <= word[0]); // make sure that the root is okay :)
  insertWordR (dict->root, word); 
}


// the amount of time this takes is dependant both on size of word and size of trie

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
//  printf("input string-> %s\n",word);
  //char first = word[0];
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
// I do believe that kitten's algorithm was a lot better
      if (rover->thisChar == word[0]) {
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
        //printf("->>%s\n",word);
        if (word[1] == '\0') { 
           rover->isTerminal = True;
        }
        else {
           rover->child = dictEdgeNew(word[1]);
           insertWordR(rover->child,&word[1]);
        }
      }
    }
  }
}

/* Insert a list of words into the dictionary 
 */
void
dictInsertWords (struct dictionary* dict, struct wlnode* words) {
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
  // by using two loops, this can be implemented
  // thanks to Ian Craig who showed me :)
  assert(dict != NULL);
  return dictLookupN(dict->root,word);
}

// n for internal? new?
bool
dictLookupN (struct dictEdge* node,char* word) {
  // todo this code still seems bugged like fuck
  if (node == NULL) {
    // very special case, dictionary is empty, clearly not in dictionary
    return False;
  }
  // terminating case.
  if (word[0] == 0) { // shouldn't really go in here... 
    return False;
  }
  // if it's the last letter
  if (word[1] == '\0') {
      struct dictEdge *rover = node;
      //printf("searching for %c %c\n",word[0],rover->thisChar);
      // while (word[0] < rover->thisChar && rover->sibling != NULL) {
      // while (rover->sibling != NULL && word[0] < rover->thisChar) // damn I had this, it's broken so badly 
      while (rover->sibling != NULL && word[0] > rover->thisChar) 
      {
// and then it took me a while to figure why it's rover->sibling not rover
        // wow, terrible coding, I didn't even think of the first 
        // check
        //printf("PASS\n");
        rover = rover->sibling;
      }
      if (word[0] == rover->thisChar && rover->isTerminal == True) {
        return True;
      }
      // bugged here
      return False;
  }
  struct dictEdge *rover = node;
  while (rover != NULL) { 
    if (word[0] == rover->thisChar) {
      // rover child could be null
      if (rover->child == NULL) {
        return False; // no more children, therefore it can't be found
      }
      return dictLookupN(rover->child,&word[1]);
    } else {
      rover = rover->sibling;
    }
  }
  // if it gets here it means no matches in the siblings
  return False;
}

/* Extract all words in the dictionary (the order does not matter).
 *
 * Complexity: see constraint in the assignment specification.
 */
struct wlnode*
dictCompletions (struct dictionary* dict, char* word) {
  return wlRev(distCompletions(dict,word));
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
  edgeFree(dict->root);
  // free the dictionary is easy
  free(dict);
}

// internal call
// recursively free all the nodes
// Complexity O(n) // linearly dependant on size of trie
void
edgeFree(struct dictEdge *node) {
  if (node != NULL) {   
    edgeFree(node->sibling);
    edgeFree(node->child);
    node->sibling = NULL;
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

/*
struct wlnode* 
wlIns (struct wlnode* wl, char* word) {
  struct wlnode* new = malloc(sizeof(struct wlnode));
  // something about this routine looks strange to me :$
  assert(new != NULL);
  new->word = word;
  new->next = NULL;
  if (wl == NULL) {
    wl = new;
  }
  else {
    struct wlnode* rover = wl; // coming back to this, I
    // was just thinking, what the heck am I doing here ;D
    // since there was no requirement for it to be ordered
    while (rover->next != NULL) {
      rover = rover->next;
    }
    rover->next = new;
  }
  return wl;
}*/


/* This function does NOT do what it says on the tin :) */
// due to the fact that the initial complexity was O(n)
// Complexity, O(1)
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

struct wlnode* wlRev(struct wlnode* wl) {
  // done in lab 1
  struct wlnode* new = wlIns(NULL,"");
  struct wlnode* rover = wl;
  /*
  for (rover = wl;rover != NULL;rover = rover->next) {
    rover->next = new->next;
    new->next = rover;
    
  } */
  while (rover != NULL) {
    struct wlnode* store = rover->next; 
      // do I get better performance if I store this variable outside the loop?
    rover->next = new->next;
    new->next = rover;
    rover = store; 
  }
  rover = new->next;
  new->next = NULL;
  free(new);
  return rover;
}

//unused
// Complexity O(n)
void
wlfree (struct wlnode* wl) {
  if (wl == NULL) {
    return;
  }
  wlfree(wl->next);
  free(wl);
}
