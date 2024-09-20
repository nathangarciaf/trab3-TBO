
#include "index.h"
#include <stdio.h>
#include <stdlib.h>

#define EPSILON 1e-6

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

void index_pageranks(Index *i){
    int docs = i->size;
    long double error = 0.0;

    //initialize pagerank
    for(int j = 0; j < docs; j++){
        document_set_pagerank(i->d[j], 1.0/docs);
    }

    while(1){
        for(int j = 0; j < docs; j++){
            double prev = document_get_pagerank(i->d[j]);
            error += calculate_pagerank(i->d[j], docs);
            document_atualize_prev_pagerank(i->d[j], prev);
        }
        error = error/docs;

        if(error < EPSILON){
            break;
        }
        
        error = 0.0;
    }
}

void index_print(Index *i){
    for(int j = 0; j < i->size; j++){
        document_print(i->d[j]);
    }
}

void print_results(char *s, Value *v, Index *i){
    printf("search:%s\n", s);

    printf("pages:");
    Value_print(v);
    printf("\n");

    printf("pr:");
    Value_print_pagerank(v);
    printf("\n");
}