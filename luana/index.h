#ifndef INDEX_H
#define INDEX_H

#include "string.h"
#include "tst.h"
#include "document.h"

typedef struct index Index;

Index *index_init();

Document ** index_get_documents(Index *i);
int index_get_size(Index *index);
void index_free(Index *index);
void index_insert_document(Index *i, Document *d);
void index_pageranks(Index *i);
void index_print(Index *i);

void print_results(char *s, Value *v, Index *i);

#endif