#include <stdio.h>
#include "cstring.h"
#include "builder.h"
#include "selection.h"
#include <stdlib.h>
#include <time.h>


int filter(char * a) {
	int i = 0;
	while (a[i] != 0) i++;

	if (i < 2) return 0;

	return *(a + i - 1) == 'R' && *(a + i - 2) == '9';
}
int main() {
	srand(time(NULL));
	Word * tab;
	unsigned long int size = build_array("Lexique4.tsv", &tab, &filter);

	cstring selection = random_selection(size, tab);

	printf("%s\n", selection);
	cstring_free(selection);

	destroy_array(tab, size);
	return 0;
}
