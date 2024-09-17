#ifndef READER_H
#define READER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include "tst.h"

TST *read_file(TST *t, FILE *f);

typedef struct index Index;

TST *read_pages(TST *t, TST *stopwords, char *dir, Index *i);

Index *index_init();
void index_read(Index *i, FILE *f);
void print_index(Index *index);
void index_free(Index *index);

#endif