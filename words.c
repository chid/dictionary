#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dictionary.h"
#define WORDMAX 80

int main (int argc, char** argv)
{
  #if 0
struct wlnode* wl = NULL;
wl = wlIns(wl,"comma");
wl = wlIns(wl,"commande");
wl = wlIns(wl,"commandeer");
wl = wlIns(wl,"commandeergIng");
wl = wlIns(wl,"13456789013");
wl = wlIns(wl,"apple");
wl = wlIns(wl,"apt");
wl = wlIns(wl,"ape");
wl = wlIns(wl,"sillyc");
wl = wlIns(wl,"1");
wl = wlIns(wl,"12");
wl = wlIns(wl,"1235678");
wl = wlIns(wl,"12416819");
wl = wlIns(wl,"124819241");
wl = wlIns(wl,"1231241211");
wl = wlIns(wl,"1235"); // this breaks :(
wl = wlIns(wl,"125"); 
wl = wlIns(wl,"comm"); 
wl = wlIns(wl,"sell"); 
//wl = wlIns(wl,"commandinger's"); 
wl = wlIns(wl,"commandinger1237128937129873hirs"); 
wl = wlIns(wl, "commaaaa");
wl =wlIns(wl,"short");
/* 
char* word = "word";
wl = wlIns(wl,word);
*/
//printwl(wl);
struct dictionary* dict = dictInit();
dictInsertWords(dict,wl);
printDict(dict);
printwl(dictCompletions(dict,"13")); return 0;
printwl(dictCompletions(dict,"sil"));
printwl(dictCompletions(dict,"s"));
printwl(dictCompletions(dict,"comma"));
dictFree(dict);
// wlfree(wl);
return 0;
#if 0
struct dictionary* dict = dictInit();
dictInsertWords(dict,wl);
printwl(dictCompletions(dict,"comm"));
  return 0;
#endif
#ifdef DEBUG
  struct dictionary* dict = dictInit();
  printf("%p", &dict);
  printDict(dict);
  printDict(dict);
  dictInsertWord(dict,"TEST");
  dictInsertWord(dict,"TESTING");
  dictInsertWord(dict,"Done");
  dictInsertWord(dict,"TEnt");
  dictInsertWord(dict,"TE");// broken
  printf(wl = wlIns(wl,"comma");
wl = wlIns(wl,"commande");
wl = wlIns(wl,"commandeer");
wl = wlIns(wl,"commandeergIng");
wl = wlIns(wl,"13456789013");
wl = wlIns(wl,"apple");
wl = wlIns(wl,"apt");
wl = wlIns(wl,"ape");
wl = wlIns(wl,"sillyc");
wl = wlIns(wl,"1");
wl = wlIns(wl,"12");
wl = wlIns(wl,"1235678");
wl = wlIns(wl,"12416819");
wl = wlIns(wl,"124819241");
wl = wlIns(wl,"1231241211");"\n");
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
  printwl(dictCompletions(dict,"OK"));
  printwl(dictCompletions(dict,"NO"));
  printwl(dictCompletions(dict,"N"));
  // dictList(dict);
  // n is for internal
#endif
#endif
#define REL
#ifdef REL 
  // allocate WORDMAX + 2: 1 for new-line character, 1 for NUL-terminator.
  char     word[WORDMAX + 2];
  int      len;
  struct wlnode* wl;
  struct wlnode* cur;
  struct wlnode* tmp;
  struct wlnode* lookupTest;

  struct dictionary* dict = dictInit ();
 // struct wlnode* test = NULL;
  while (fgets (word, sizeof(word), stdin))
  { 
    len = strlen (word);
    if (len > 0 && '\n' == word[len - 1])
      word[--len] = '\0';
    if (len > 0) {
      dictInsertWord (dict, word);
  //    test = wlIns(test,word); 
      char *wor = malloc(sizeof(char)*82);
      strcpy(wor,word);
      lookupTest = wlIns(lookupTest,wor);
    }


  }
 /* 
  struct wlnode* b = wlIns(NULL,"HIHIHI");
  struct wlnode* a = dictToWl(dict->root,NULL,0,b);
  printwl(a);return; */
  //printDict(dict);return;
 //  printEdge(dict->root,0);return;
  // change string to get different results:
//  printwl(test);
  wl = dictCompletions (dict, argc < 2 ? "" : argv[1]);
  
  //return;
  for (cur = wl; NULL != cur; cur =  cur->next)
    fprintf (stdout, "%s\n", cur->word);
  // return;
  // free the memory returned by dictCompletions ()
  for (cur = wl; NULL != cur; cur = tmp)
  {
    // save cur->next into tmp before we free cur.
    tmp = cur->next;
    printf("freeing %p\n",&cur->word);
    printf("freeing %p\n",cur->word);
    free (cur->word);
    free (cur);
  }
  wl = lookupTest;
  printf("Test for Lookup\n");
  for (cur = wl; NULL != cur; cur = tmp)
  {
    // save cur->next into tmp before we free cur.
    printf("Looking Up %s, %d\n",cur->word,dictLookup(dict,cur->word));
    int len = strlen(cur->word);
    cur->word[--len] = 'a';
    cur->word[++len] = '\0';
    printf("Looking Up %s, %d\n",cur->word,dictLookup(dict,cur->word));
    cur->word[--len] = '\0';
    printf("Looking Up %s, %d\n",cur->word,dictLookup(dict,cur->word));
    char t[] = "zoon";
    printf("Looking Up %s, %d\n",t,dictLookup(dict,t));
    tmp = cur->next;
    free (cur->word);
    free (cur);
  }
  dictFree (dict);
#endif
  return EXIT_SUCCESS;
}
