/*
 * wordsort.h
 *
 *  Created on: Mar 5, 2011
 *      Author: eric
 */

#ifndef WORDSORT_H_
#define WORDSORT_H_

typedef struct {
	int size;
	int capacity;
	char **wordlist;
} word_list;

void parse_line(word_list *list, char *line);
void list_init(word_list *list);
void list_add(word_list *list, char *word);

int cstring_cmp(const void *a, const void *b);

#endif /* WORDSORT_H_ */
