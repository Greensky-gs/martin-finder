#ifndef __CSTRING_H__
#define __CSTRING_H__ 1

#define SIZE_T long

typedef char * cstring;

cstring cstring_create(SIZE_T);
SIZE_T cstring_length(cstring);
SIZE_T cstring_max(cstring);
void cstring_free(cstring);
SIZE_T cstring_fill(cstring, char *);

char cstring_reverse(cstring, SIZE_T);

#endif
