#include "args.h"
#include "utils.h"

int in_args(int argc, char * argv[], char * target) {
	int i = 1;
	while (i < argc) {
		if (streq(argv[i], target)) return 1;
		i++;
	}
	return 0;
}

int arg_int(int argc, char * argv[], char * target, int * result) {
	int i = 1;
	while (i < argc - 1) {
		if (streq(argv[i], target)) {
			if (!parse_int(argv[i + 1], result)) return -1;
			return 1;
		}
		i++;
	}
	return 0;
}
