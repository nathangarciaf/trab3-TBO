#ifndef INDEX_H
#define INDEX_H

#include "string.h"

typedef struct document Document;
typedef struct index Index;

Index *index_init();
Document *document_init(String *s);
void document_free(Document *d);
void index_free(Index *index);
void index_insert_document(Index *i, Document *d);
void index_print(Index *index);

#endif