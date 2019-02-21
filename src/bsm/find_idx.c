/*
  Function : find_index.c
  Purpose  : Bahcall - Soneira Galaxy Model.
             Get index for keyword search.
  History  : Began: 26 June 1991. Last edit: 30 June 1994.
  Author   : P.J.C.Hodder (hodder@geop.ubc.ca)
  Comments : 1. See comments in keyword.h.
*/

#include "keyword.h"

int find_index(char *word)
{
  int i;
  int index;

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
