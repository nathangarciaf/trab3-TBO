#ifndef READER_H
#define READER_H

#include <stdio.h>
#include "tst.h"
#include "index.h"

TST *read_stopwords(TST *t, FILE *f);
TST *read_dir_files(TST *t, TST *stopwords, char *dir,Index* i, FILE *index);
void read_graph(Index *i, FILE *f);

#endif