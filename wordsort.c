/*
 * wordsort.c
 *
 *  Created on: Mar 5, 2011
 *      Author: eric
 */
#include "wordsort.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <readline/readline.h>

int main(int argc, char *argv[]) {
	word_list list;
	list_init(&list);
	/*
	 dynamic_add(&list, "0");
	 dynamic_add(&list, "1");
	 dynamic_add(&list, "2");
	 dynamic_add(&list, "4");
	 dynamic_add(&list, "5");
	 dynamic_add(&list, "6");
	 dynamic_add(&list, "7");
	 dynamic_add(&list, "8");
	 dynamic_add(&list, "9");
	 dynamic_add(&list, "10");
	 dynamic_add(&list, "11");
	 dynamic_add(&list, "12");
	 dynamic_add(&list, "13");
	 dynamic_add(&list, "14");
	 dynamic_add(&list, "15");
	 dynamic_add(&list, "16");
	 dynamic_add(&list, "Hello77");
	 dynamic_add(&list, "Hello");
	 dynamic_add(&list, "Hello");
	 dynamic_add(&list, "Hello wut wut");
	 dynamic_add(&list, "Hello moto");
	 dynamic_add(&list, "Hello Robot");
	 dynamic_add(&list, "Hello Logan");
	 dynamic_add(&list, "Hello Cory");
	 dynamic_add(&list, "Hello Tim");
	 dynamic_add(&list, "Hello Eric");
	 */

	while (true) {
		char *line = readline(">");
		parse_line(&list, line);
		int i;
		qsort(list.wordlist, list.size, sizeof(char *), cstring_cmp);

		for (i = 0; i < list.size; ++i) {
			printf("%d/%d %s\n", i + 1, list.capacity, *(list.wordlist + i));
		}
	}

	return EXIT_SUCCESS;
}

void parse_line(word_list *list, char *line) {
	int size = strlen(line);
	bool inString = false;
	int i;
	for (i = 0; i < size; i++) {
		if (isalpha(line[i])) {
			if (!inString) {
				inString = true;
				list_add(list, (line + i));
			}
		} else {
			inString = false;
			line[i] = '\0';
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

int cstring_cmp(const void *a, const void *b) {
	const char **ia = (const char **) a;
	const char **ib = (const char **) b;
	return strcmp(*ia, *ib);
}
