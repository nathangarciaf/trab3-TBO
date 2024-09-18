
#include "index.h"
#include <stdio.h>
#include <stdlib.h>

struct document {
    String *c;
    Document **linked_out_documents;
    int size_out, alloc_out;

    Document **linked_in_documents;
    int size_in, alloc_in;
};


struct index {
    Document **d;
    int size, alloc;
};

Index *index_init(){
    Index *i = (Index*)calloc(1,sizeof(Index));
    i->size = 0;
    i->alloc = 2;
    i->d = (Document**)calloc(i->alloc, sizeof(Document*));
    return i;
}

void index_insert_document(Index *i, Document *d){
    if(i->alloc == i->size){
        i->alloc *=2;
        i->d = (Document**)realloc(i->d,i->alloc*sizeof(Document*));
    }
    i->d[i->size] = d;
    i->size++;
}

Document *document_init(String *s){
    Document *d = (Document*)calloc(1, sizeof(Document));
    d->c = s;

    d->alloc_in = 2;
    d->alloc_out = 2;
    
    d->linked_in_documents = (Document**)calloc(d->alloc_in, sizeof(Document*));
    d->linked_out_documents = (Document**)calloc(d->alloc_out,sizeof(Document*));

    d->size_in = 0;
    d->size_out = 0;
    return d;
}

void document_free(Document *d){
    free(d->linked_in_documents);
    free(d->linked_out_documents);
    string_free(d->c);
    free(d);
}

void index_print(Index *index){
    for(int i = 0; i < index->size; i++){
        string_print(index->d[i]->c);
    }
    
}

void index_free(Index *index){
    for(int i = 0; i < index->size; i++){
        document_free(index->d[i]);
    }
    free(index->d);
    free(index);
}