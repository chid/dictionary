/* COMP1927
 *
 * DO NOT MODIFY!
 */

#ifndef DICTIONARY_TYPE_H
#define DICTIONARY_TYPE_H

/* We represent dictionaries as multi-branch tree with labelled edges.  Any 
 * path from the root that ends in an edge whose `isTerminal' flag is set is 
 * a valid word in the dictionary.  Dictionary nodes are implicitly
 * represented by a set of edges connected via `sibling' links.
 *
 * Siblings are ordered by character index. The value of `thisChar` is
 * different for every edge of a single dictionary node.  Sibling lists
 * and tree paths are terminated by NULL links.
 */

struct dictEdge
{
  char     thisChar;		/* character labelling this edge */
  bool     isTerminal;		/* a word may end with character */
  struct dictEdge* child;       /* suffix dictionary */
  struct dictEdge* sibling;	/* next sibling edge */
};

struct dictionary
{
  struct dictEdge* root;        /* The root of the dictionary */
}

#endif /* ! DICTIONARY_TYPE_H */
