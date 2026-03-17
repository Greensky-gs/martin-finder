#include <stdio.h>
#include "cstring.h"
#include "builder.h"

int filter(char * a) {
	int i = 0;
	while (a[i] != 0) i++;

	if (i < 2) return 0;

	return *(a + i - 1) == 'R' && *(a + i - 2) == '9';
}

int main() {
	Word * tab;
	unsigned long int size = build_array("Lexique4.tsv", &tab, &filter);

	unsigned long int i = 0;
	while (i < size) {
		printf("name = %s, phono is %s\n", tab[i]->word, tab[i]->phono);
		i++;
	}

	destroy_array(tab, size);
	return 0;
}
