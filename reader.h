#ifndef READER_H
#define READER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tst.h"

TST *read_file(TST *t, FILE *f);
TST *read_dir_files(TST *t, TST *stopwords, char *dir, FILE *index);

#endif