#include "document.h"
#include <stdio.h>
#include <stdlib.h>

struct document {
    String *c;

    // Vetor dos documentos que APONTAM para o documento atual
    Document **linked_documents;
    int size, alloc;

    int amount_out;
    double pagerank, prev_pagerank;
};

Document *document_init(String *s, int size){
    Document *d = (Document*)calloc(1, sizeof(Document));
    d->c = s;

    d->alloc = 0;
    d->amount_out = 0;
    
    d->linked_documents = NULL;
    d->prev_pagerank = 0;
    d->pagerank = 1.0 / size;

    d->size = 0;
    return d;
}

Document *document_find(Document **d, int size, String *key){
    for(int i = 0; i < size; i++){
        //printf("STR 1: %s, STR 2: %s\n", string_get(d[i]->c), string_get(key));
        if(!compare_from(d[i]->c,key, 0))
            return d[i];
    }
    return NULL;
}

void document_print(Document *d){
    printf("ARQUIVO RESGATADO %s\n",string_get(d->c));
}

void document_free(Document *d){
    string_free(d->c);
    free(d->linked_documents);
    free(d);
}

void document_insert_out(Document *d, int out){
    d->amount_out = out;
}

void document_add_out(Document *d){
    d->amount_out++;
}

void document_insert_linked(Document *d, Document *l){
    if(!d->linked_documents){
        d->alloc = 2;
        d->linked_documents = (Document**)calloc(d->alloc,sizeof(Document*));
    }

    if(d->alloc == d->size){
        d->alloc *= 2;
        d->linked_documents = (Document**)realloc(d->linked_documents,d->alloc*sizeof(Document*));
    }
    //printf("SIZE: %d\nALLOC: %d\n", d->size,d->alloc);
    d->linked_documents[d->size] = l;
    d->size++;
}

void document_alloc_links(Document *d, int alloc){
    if(!d)
        exit(1);
    d->alloc = alloc;
    d->linked_documents = (Document**)calloc(d->alloc, sizeof(Document*));
}

void document_report(Document **d, int size){
    for(int i = 0; i < size; i++){
        Document *curr = d[i];
        printf("DOCUMENTO ATUAL: %s\n", string_get(curr->c));
        printf("DOCUMENTOS QUE APONTAM PARA O ATUAL: ");
        for(int j = 0; j < curr->size; j++){
            Document *l = curr->linked_documents[j];
            printf("%s ", string_get(l->c));
        }
        printf("\n");
        printf("NUMERO DE DOCUMENTOS QUE O DOC ATUAL APONTA: %d\n\n", curr->amount_out);
    }
}