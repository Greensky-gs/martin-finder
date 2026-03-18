#include "utils.h"

int streq(char * a, char * b) {
	int i = 0;
	while (a[i] != 0 && b[i] != 0) {
		if (a[i] != b[i]) return 0;
		i++;
	}

	return a[i] == b[i];
}

int parse_int(char * str, int * res) {
	int num = 0;
	int i = 0;
	while (str[i] != 0) {
		char x = str[i];
		if (x > 57 || x < 48) return 0;

		num = num * 10 + (x - 48);
		i++;
	}

	*res = num;
	return 1;
}

int strsize(char * a) {
	int i = 0;
	while (a[i] != 0) {
		i++;
	} 
	return i;
}
