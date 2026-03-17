#include "cstring.h"
#include <string.h>
#include <stdio.h>
#include "builder.h"
#include <stdlib.h>

#define MAX_LINE_SIZE 2048

Word create_word(SIZE_T a, SIZE_T b) {
	Word word;
	if ((word = malloc(sizeof(struct WordEntry))) == NULL) return NULL;

	if ((word->word = cstring_create(a)) == NULL) {
		free(word);
		return NULL;	
	}
	if ((word->phono = cstring_create(b)) == NULL) {
		cstring_free(word->word);
		free(word);
		return NULL;
	}

	return word;
}
void destroy_word(Word word) {
	cstring_free(word->word);
	cstring_free(word->phono);
	free(word);
}

static void put_null_atfs(char * s) {
	int i = 0;
	while (s[i] != 0 && s[i] != '	') {
		i++;
	}
	if (s[i] == '	') s[i] = 0;
}
static char * slice_to_next(char * str) {
	int i = 0;
	while (str[i] != 0 && str[i] != '	') i++;
	if (str[i] == 0) return str;

	while (str[i] == '	') i++;
	return str + i;
}

unsigned long int build_array(const char * file_path, Word  ** p, int filter(char *)) {
	FILE * stream;
	if ((stream = fopen(file_path, "rt")) == NULL) return 0;

	char buffer[MAX_LINE_SIZE + 1];

	unsigned long int count = 0;
	while (fgets(buffer, MAX_LINE_SIZE, stream) != NULL) {
		char * phono = slice_to_next(buffer);
		char * name = buffer;

		put_null_atfs(phono);
		put_null_atfs(name);

		if (filter(phono)) count++;
	}

	if (count <= 1) return 0; // headers
	count--;
	fseek(stream, 0, SEEK_SET);

	if ((*p = malloc(sizeof(Word) * count)) == NULL) {
		fclose(stream);
		return 0;
	}

	unsigned long int index = 0;
	int skipped = 0;
	while (fgets(buffer, MAX_LINE_SIZE, stream) != NULL) {
		if (!skipped) {
			skipped = 1;
			continue;
		}

		char * phono = slice_to_next(buffer);
		char * name = buffer;

		put_null_atfs(phono);
		put_null_atfs(name);

		if (!filter(phono)) continue;

		int a = strlen(name);
		int b = strlen(phono);

		if (((*p)[index] = create_word(a, b)) == NULL) {
			printf("Error with index %ld, skipping\n", index);
			index++;
			continue;
		}

		cstring_fill((*p)[index]->word, name);
		cstring_fill((*p)[index]->phono, phono);
		index++;
	}

	fclose(stream);
	return index;
}

void destroy_array(Word * p, unsigned long int size) {
	unsigned long int i = 0;
	while (i < size) {
		destroy_word(p[i]);
		i++;
	}

	free(p);
}
