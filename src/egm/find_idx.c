/*
  Function : find_idx.c
  Purpose  : External Galaxy Model.
             Get index for keyword search.
  History  : Began: 6 October 1992. Last edit: 16 December 1993.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : See comments in keyword.h.
*/

#include  "keyword.h"

int find_idx(char *word)
{
  int i, index;

  index = NOT_A_WORD;

  for (i=0; i<NUM_KEYWORDS; i++) {
    if (!strcmp(word,keyword[i])) {
      index = i;
      break;
    }
  }
  
  return index;
}
/*---------------------------------------------------------------------------*/
