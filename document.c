#include "document.h"
#include <stdio.h>
#include <stdlib.h>

struct document {
    String *c;

    Document **linked_documents;
    int size, alloc, amount_out;
};

Document *document_init(String *s){
    Document *d = (Document*)calloc(1, sizeof(Document));
    d->c = s;

    d->alloc = 0;
    d->amount_out = 0;
    
    d->linked_documents = NULL;

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

void document_add_out(Document *d){
    d->amount_out++;
}

void document_insert_linked(Document *d, Document *l){
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
        printf("DOCUMENTOS LINKADOS: ");
        for(int j = 0; j < curr->size; j++){
            Document *l = curr->linked_documents[j];
            printf("%s ", string_get(l->c));
        }
        printf("\n");
        printf("DOCUMENTOS COM LINK PARA O DOCUMENTO ATUAL: %d\n\n", curr->amount_out);
    }
}