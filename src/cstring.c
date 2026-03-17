#include <stdlib.h>
#include "cstring.h"

cstring cstring_create(SIZE_T size) {
	if (size == 0) return NULL;
	size_t margin = sizeof(SIZE_T) * 2;
	SIZE_T total_size = (SIZE_T)margin + size + 1;

	cstring p;
	if ((p = malloc(total_size)) == NULL) return NULL;

	p[0] = size;
	*(p + sizeof(SIZE_T)) = size;
	*(p + margin + size) = 0;
	return p + margin;
}

SIZE_T cstring_length(cstring string) {
	return *(string - sizeof(SIZE_T));
}
SIZE_T cstring_max(cstring string) {
	return *(string - 2 * sizeof(SIZE_T));
}
void cstring_free(cstring string) {
	free(string - sizeof(SIZE_T) * 2);
}

char cstring_reverse(cstring string, SIZE_T n) {
	SIZE_T size = cstring_length(string);
	return *(string + size - n);
}

SIZE_T cstring_fill(cstring string, char * content) {
	SIZE_T index = 0;
	SIZE_T max = cstring_max(string);

	while (content[index] != 0 && index < max) {
		string[index] = content[index];
		index++;
	}

	*(string - sizeof(SIZE_T)) = index;
	string[index] = 0;
	return index;
}
