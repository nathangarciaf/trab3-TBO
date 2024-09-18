#ifndef INDEX_H
#define INDEX_H

#include "string.h"

typedef struct document Document;
typedef struct index Index;

Index *index_init();
Document *document_init(String *s);
Document *document_find(Document **d, int size, String *key);
Document **index_get_documents(Index *i);
int index_get_size(Index *index);
void document_insert_linked(Document *d, Document *l);
void document_alloc_links(Document *d, int alloc);
void document_free(Document *d);
void index_free(Index *index);
void index_insert_document(Index *i, Document *d);
void index_print(Index *index);
void document_print(Document *d);
void document_add_out(Document *d);
void document_report(Document **d, int size);

#endif