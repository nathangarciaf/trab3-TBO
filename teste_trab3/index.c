
#include "index.h"
#include <stdio.h>
#include <stdlib.h>

#define ALFA 0.85

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

double page_rank(Document *d){

}

void index_insert_document(Index *i, Document *d){
    if(i->alloc == i->size){
        i->alloc *=2;
        i->d = (Document**)realloc(i->d,i->alloc*sizeof(Document*));
    }
    i->d[i->size] = d;
    i->size++;
}

Document **index_get_documents(Index *i){
    return i->d;
}

int index_get_size(Index *index){
    return index->size;
}

void index_free(Index *index){
    for(int i = 0; i < index->size; i++){
        document_free(index->d[i]);
    }
    free(index->d);
    free(index);
}