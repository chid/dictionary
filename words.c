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

  //struct 
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
