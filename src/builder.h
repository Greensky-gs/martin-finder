#ifndef __BUILDER_H__
#define __BUILDER_H__ 1
#include "cstring.h"


typedef enum {
	WordUnknown = 0,
	WordName = 1,
	WordVer = 2,
	WordAdj = 3
} WordType;
typedef enum {
	WordMasc = 0,
	WordFem = 1
} WordGenre;

struct WordEntry {
	cstring word;
	cstring phono;
	WordType type;
	WordGenre genre;
};
typedef struct WordEntry * Word;

extern Word create_word(SIZE_T, SIZE_T, WordType, WordGenre);
extern void destroy_word(Word);

extern unsigned long int build_array(const char *, Word **, int filter(char *));
extern void destroy_array(Word *, unsigned long int);

#endif
