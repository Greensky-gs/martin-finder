#include <stdio.h>
#include "cstring.h"
#include "builder.h"
#include "selection.h"
#include <stdlib.h>
#include <time.h>
#include "utils.h"

#if _WIN32
	#include <Windows.h>
#else
	#include <unistd.h>
#endif

void wait_seconds(int seconds) {
	#if _WIN32
		Sleep(seconds * 1000);
	#else
		sleep(seconds);
	#endif
}

int in_args(int argc, char * argv[], char * target) {
	int i = 1;
	while (i < argc) {
		if (streq(target, argv[i])) return 1;
		i++;
	}
	return 0;
}

int filter(char * a) {
	int i = 0;
	while (a[i] != 0) i++;

	if (i < 2) return 0;

	return *(a + i - 1) == 'R' && *(a + i - 2) == '9';
}
static void generate(unsigned long int size, Word * tab) {
	cstring selection;
	if ((selection = random_selection(size, tab)) == NULL) {
		printf("Something went wrong\n");
		return;
	}

	printf("%s\n", selection);
	cstring_free(selection);
}
int main(int argc, char * argv[]) {
	srand(time(NULL));
	Word * tab;
	unsigned long int size = build_array("Lexique4.tsv", &tab, &filter);

	if (size == 0 || tab == NULL) {
		printf("Something went wrong\n");
		return 1;
	}

	if (in_args(argc, argv, "-i") || in_args(argc, argv, "--infinite")) {
		while (1) {
			generate(size, tab);
			wait_seconds(2);
		}
	} else {
		generate(size, tab);
	}

	destroy_array(tab, size);
	return 0;
}
