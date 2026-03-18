#include <stdio.h>
#include "cstring.h"
#include "builder.h"
#include "selection.h"
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include "args.h"

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
	Word * tab;
	unsigned long int size = build_array("Lexique4.tsv", &tab, &filter);

	if (size == 0 || tab == NULL) {
		printf("Something went wrong\n");
		return 1;
	}

	if (in_args(argc, argv, "-i") || in_args(argc, argv, "--infinite")) {
		int delay = 2;
		if (arg_int(argc, argv, "-d", &delay) != 1) arg_int(argc, argv, "--delay", &delay);

		long int i = 0;
		while (1) {
			printf("%ld ", i);
			i++;
			generate(size, tab);
			wait_seconds(delay);
		}
	} else {
		generate(size, tab);
	}

	destroy_array(tab, size);
	return 0;
}
