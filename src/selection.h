#ifndef __SELECTION_H__
#define __SELECTION_H__ 1
#include "builder.h"
#include "cstring.h"
#include <stdlib.h>

extern cstring random_start(WordGenre, WordType, cstring);
extern cstring random_sentence(Word); 
extern cstring random_selection(unsigned long int, Word *);

#endif
