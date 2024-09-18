#ifndef DOCUMENT_H
#define DOCUMENT_H
#include "string.h"


typedef struct document Document;

Document *document_init(String *s, int size);
Document *document_find(Document **d, int size, String *key);
void document_insert_linked(Document *d, Document *l);
void document_alloc_links(Document *d, int alloc);
void document_free(Document *d);
void document_print(Document *d);
void document_add_out(Document *d);
void document_report(Document **d, int size);
void document_insert_out(Document *d, int out);

#endif