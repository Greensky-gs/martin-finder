#ifndef __BUILDER_H__
#define __BUILDER_H__ 1
#include "cstring.h"


struct WordEntry {
	cstring word;
	cstring phono;
};
typedef struct WordEntry * Word;

extern Word create_word(SIZE_T, SIZE_T);
extern void destroy_word(Word);

extern unsigned long int build_array(const char *, Word **, int filter(char *));
extern void destroy_array(Word *, unsigned long int);

#endif
