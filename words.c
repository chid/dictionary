#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dictionary.h"
#define WORDMAX 80

int main (int argc, char** argv)
{
  struct dictionary* dict = dictInit();
  printf("%p", &dict);
  printDict(dict);
  printDict(dict);
  dictInsertWord(dict,"TEST");
  dictInsertWord(dict,"TESTING");
  dictInsertWord(dict,"Done");
  dictInsertWord(dict,"TEnt");
  dictInsertWord(dict,"TE");// broken
  printf("\n");
printEdge(dict->root,0);
dictFree(dict);
dict = dictInit();
  struct wlnode* wl = NULL;
  wl = wlIns(wl,(char *)"OK");
  wl = wlIns(wl,"Oweariej");
  wl = wlIns(wl,"OKfnmk");
  wl = wlIns(wl,"NOK");
  wl = wlIns(wl,"NOOK");
  wl = wlIns(wl,"BOOK");
  wl = wlIns(wl,"BOOKING");
printwl(wl);//struct 
  dictInsertWords(dict,wl);
  printEdge(dict->root,0)
;
  if (dictLookupN(dict->root,"OK") == True) {
    printf("looks like lookup working\n");
  }
  else {
    printf("BROKEN");
  }
  if (dictLookupN(dict->root,"OKf") == False) {
    printf("looks like lookup working\n");
  }
  else {
    printf("BROKEN");
  }
  printf("Looked up %s in tree returned: %d\n","OK",dictLookupN(dict->root,"OK"));
  printf("Looked up %s in tree returned: %d\n","OKf",dictLookupN(dict->root,"OKf"));
  printf("Looked up %s in tree returned: %d\n","OKf",dictLookupN(dict->root,"Kf"));
  printf("testing treeTraversal\n\t");
  dictTrav(dict->root);
  printf("\n");

  printf("testing treeListWords\n");
  dictList(dict);
  printf("\n");
  struct wlnode* b = wlIns(NULL,"HIHIHI");
  struct wlnode* a = dictToWl(dict->root,NULL,0,b);
  printwl(a);
printf("testing, completions\n");
  printwl(distCompletions(dict,"OK"));
  printwl(distCompletions(dict,"NO"));
  printwl(distCompletions(dict,"N"));
  // dictList(dict);
  // n is for internal

#if 0
  // allocate WORDMAX + 2: 1 for new-line character, 1 for NUL-terminator.
  char     word[WORDMAX + 2];
  int      len;
  struct wlnode* wl;
  struct wlnode* cur;
  struct wlnode* tmp;

  struct dictionary* dict = dictInit ();

  while (fgets (word, sizeof(word), stdin))
  {
    len = strlen (word);
    if (len > 0 && '\n' == word[len - 1])
      word[--len] = '\0';
    if (len > 0)
      dictInsertWord (dict, word);
  }

  // change string to get different results:
  wl = dictCompletions (dict, argc < 2 ? "" : argv[1]);
  for (cur = wl; NULL != cur; cur =  cur->next)
    fprintf (stdout, "%s\n", cur->word);

  // free the memory returned by dictCompletions ()
  for (cur = wl; NULL != cur; cur = tmp)
  {
    // save cur->next into tmp before we free cur.
    tmp = cur->next;

    free (cur->word);
    free (cur);
  }

  dictFree (dict);
#endif
  return EXIT_SUCCESS;
}
