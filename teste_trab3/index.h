#ifndef INDEX_H
#define INDEX_H

#include "string.h"
#include "document.h"

typedef struct index Index;

Index *index_init();

Document **index_get_documents(Index *i);
int index_get_size(Index *index);
void index_free(Index *index);
void index_insert_document(Index *i, Document *d);
double page_rank(Document *d);

#endif