/*
 * wordsort.c
 *
 *  Created on: Mar 5, 2011
 *      Author: Eric Nelson
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct {
	int size;
	int capacity;
	char **wordlist;
} word_list;

void parse_string(word_list *list, char *line);
void list_init(word_list *list);
void list_add(word_list *list, char *word);
void list_free(word_list *list);

int cstring_cmp_asc(const void *a, const void *b);
int cstring_cmp_desc(const void *a, const void *b);

int main(int argc, char *argv[]) {
	word_list list;
	list_init(&list);
	int capacity = 10;
	int size = 0;
	char *data = malloc(capacity * sizeof(char));
    char c;
    while ((c = getchar()) && (c != EOF)){
    	data[size] = c;
    	size++;
    	if(size >= capacity){
    		capacity = (capacity * 3) / 2 + 10;
    		data = realloc(data, capacity);
    	}
    }
	parse_string(&list, data);
	free(data);
	int i;

	if (argc == 2 && strcmp(argv[1],"-d") == 0) {
		qsort(list.wordlist, list.size, sizeof(char *), cstring_cmp_desc);
	} else {
		qsort(list.wordlist, list.size, sizeof(char *), cstring_cmp_asc);
	}

	for (i = 0; i < list.size; ++i) {
		printf("%s\n", *(list.wordlist + i));
	}
	list_free(&list);

	return EXIT_SUCCESS;
}

void parse_string(word_list *list, char *string) {
	int size = strlen(string);
	bool in_string = false;
	char *word_start = NULL;
	int i;
	for (i = 0; i <= size; i++) {
		if (isalpha(string[i])) {
			if (!in_string) {
				in_string = true;
				word_start = string + i;
			}
		} else {
			in_string = false;
			string[i] = '\0';
			if (word_start != NULL) {
				char *newWord = malloc(strlen(word_start) * sizeof(char));
				strcpy(newWord, word_start);
				list_add(list, newWord);
				word_start = NULL;
			}
		}
	}
}

void list_add(word_list *list, char *word) {
	if (list->size < list->capacity) {
		*(list->wordlist + list->size) = (char*) word;
		list->size++;
	} else {
		list->capacity = (list->capacity * 3) / 2 + 10;
		list->wordlist
				= realloc(list->wordlist, sizeof(char*) * list->capacity);

		*(list->wordlist + list->size) = (char*) word;
		list->size++;
	}
}

void list_init(word_list *list) {
	list->size = 0;
	list->capacity = 10;
	list->wordlist = malloc(sizeof(char*) * list->capacity);
}
void list_free(word_list *list) {
	int ptr;
	for (ptr = list->size - 1; ptr >= 0; --ptr) {
		free(list->wordlist[ptr]);
	}
	free(list->wordlist);
	list->size = 0;
	list->capacity = 0;
}

int cstring_cmp_asc(const void *a, const void *b) {
	const char **ia = (const char **) a;
	const char **ib = (const char **) b;
	return strcmp(*ia, *ib);
}
int cstring_cmp_desc(const void *a, const void *b) {
	const char **ia = (const char **) a;
	const char **ib = (const char **) b;
	return -strcmp(*ia, *ib);
}
