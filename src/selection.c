#include "cstring.h"
#include "builder.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static int random_number(int min, int max) {
	return (rand() % (max - min)) + min;
}

static cstring random_name(WordGenre genre, cstring mot, int il) {
	char * bank_tu[] = {
		"tu as tellement de ",
		genre == WordMasc ? "tu es un " : "tu es une ",
		genre == WordMasc ? "tu adores le " : "tu adores la ",
		genre == WordMasc ? "tu fais du " : "tu fais de la",
	};
	char * bank_il[] = {
		"il a tellement de ",
		genre == WordMasc ? "il est un " : "il est une ",
		genre == WordMasc ? "il adore le " : "il adore la ",
		genre == WordMasc ? "il fait du " : "il fait de la ",
	};

	int randint = random_number(0, il ? 4 : 4);
	char * start = (il ? bank_il : bank_tu)[randint];

	char * end = " : Martin ";

	int totalsize = strlen(start) + 2 * strlen(mot) + strlen(end);
	cstring string;
	if ((string = cstring_create(totalsize)) == NULL) return NULL;

	string[0] = 0;
	strcat(string, start);
	strcat(string, mot);
	strcat(string, end);
	strcat(string, mot);

	*(string - sizeof(SIZE_T)) = (SIZE_T)totalsize;

	return string;
}
static cstring random_verbe(WordGenre genre, cstring mot, int il) {
	char * bank_tu[] = {
		"tu es en train de ",
		"tu ne peux pas t'empecher de "
		"tu ne fais que ",
		"tu ne pense qu'a " 
	};
	char * bank_il[] = {
		"il est en train de ",
		"il ne peut pas s'empecher de ",
		"il ne fait que ",
		"il ne pense qu'a "
	};

	int randint = random_number(0, il ? 4 : 4);
	char * start = (il ? bank_il : bank_tu)[randint];

	char * end = " : Martin ";

	int totalsize = strlen(start) + 2 * strlen(mot) + strlen(end);
	cstring string;
	if ((string = cstring_create(totalsize)) == NULL) return NULL;

	string[0] = 0;
	strcat(string, start);
	strcat(string, mot);
	strcat(string, end);
	strcat(string, mot);

	*(string - sizeof(SIZE_T)) = (SIZE_T)totalsize;

	return string;
}
static cstring random_adj(WordGenre genre, cstring mot, int il) {
	char * bank_tu[] = {
		"tu as trop de ",
		"tu es tellement ",
		"tu n'es pas ",
		"tu as l'air "
	};
	char * bank_il[] = {
		"il a trop de ",
		"il est tellement ",
		"il n'est pas ",
		"il a l'air "
	};

	int randint = random_number(0, il ? 4 : 4);
	char * start = (il ? bank_il : bank_tu)[randint];

	char * end = " : Martin ";

	int totalsize = strlen(start) + 2 * strlen(mot) + strlen(end);
	cstring string;
	if ((string = cstring_create(totalsize)) == NULL) return NULL;

	string[0] = 0;
	strcat(string, start);
	strcat(string, mot);
	strcat(string, end);
	strcat(string, mot);

	*(string - sizeof(SIZE_T)) = (SIZE_T)totalsize;

	return string;

}

cstring random_start(WordGenre genre, WordType type, cstring mot, int il) {
	char * joiners[] = {
		"et ",
		"mais "
	};
	
	cstring start;
	switch (type) {
		case WordVer:
			start = random_verbe(genre, mot, il);
			break;
		case WordAdj:
			start = random_adj(genre, mot, il);
			break;
		default:
		case WordName:
			start = random_name(genre, mot, il);
			break;
	}
	if (start == NULL) return NULL;

	int randint = random_number(0, 2);
	char * joiner = joiners[randint];

	int totalsize = strlen(joiner) + cstring_length(start);

	cstring result;
	if ((result = cstring_create(totalsize)) == NULL) {
		cstring_free(start);
		return NULL;
	};

	result[0] = 0;
	strcat(result, joiner);
	strcat(result, start);

	cstring_free(start);
	*(result - sizeof(SIZE_T)) = (SIZE_T)totalsize;

	return result;
}

cstring random_sentence(Word word) {
	int il = random_number(0, 2);

	cstring start;
	if ((start = random_start(word->genre, word->type, word->word, il)) == NULL) return NULL;

	char * entry = il ? "Il est prof de philo des sciences " : "Tu es prof de philo des sciences ";

	int totalsize = strlen(entry) + cstring_length(start);
	cstring total;
	if ((total = cstring_create(totalsize)) == NULL) {
		cstring_free(start);
		return NULL;
	}

	total[0] = 0;
	strcat(total, entry);
	strcat(total, start);

	*(total - sizeof(SIZE_T)) = totalsize;
	cstring_free(start);
	return total;
}

cstring random_selection(unsigned long int size, Word * list) {
	unsigned long int index = random_number(0, size);

	Word selected = list[index];
	return random_sentence(selected);
}
