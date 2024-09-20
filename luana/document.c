#include "document.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ALFA 0.85

struct document {
    String *c;

    // Vetor dos documentos que APONTAM para o documento atual
    Document **linked_documents;
    int size, alloc;

    int amount_out; // Número de documentos que o documento atua aponta
    long double pagerank, prev_pagerank;
};

Document *document_init(String *s, int size){
    Document *d = (Document*)calloc(1, sizeof(Document));
    d->c = s;

    d->alloc = 0;
    d->amount_out = 0;
    
    d->linked_documents = NULL;
    d->prev_pagerank = 1.0 / size;
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
    printf(" %s",string_get(d->c));
}

void document_print_pagerank(Document *d){
    printf(" %Lf", d->pagerank);
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

long double calculate_pagerank(Document *d, int docs){
    long double sum = 0;

    if(d->amount_out != 0){
        for(int i = 0; i < d->size; i++){
            Document *curr = d->linked_documents[i];
            sum += curr->prev_pagerank / curr->amount_out;
        }
        d->pagerank = ((1 - ALFA) / docs) + (ALFA * sum);

        return fabs(d->pagerank - d->prev_pagerank);

    } else {
        for(int i = 0; i < d->size; i++){
            Document *curr = d->linked_documents[i];
            sum += curr->prev_pagerank/ curr->amount_out;
        }
        d->pagerank = ((1-ALFA) / docs) + (ALFA * d->prev_pagerank) + (ALFA * sum);

        return fabs(d->pagerank - d->prev_pagerank);
    }
}

long double document_get_pagerank(Document *d){
    return d->pagerank;
}

void document_set_pagerank(Document *d, long double pagerank){
    d->pagerank = 0;
    d->prev_pagerank = pagerank;
}

void document_atualize_prev_pagerank(Document *d, long double prev){
    d->prev_pagerank = prev;
}

int compare_pagerank(const void *a, const void *b){
    Document *doc1 = *(Document**)a;
    Document *doc2 = *(Document**)b;

    if(doc1->pagerank < doc2->pagerank){
        return 1;
    } else if(doc1->pagerank > doc2->pagerank){
        return -1;
    } else {
        if(strcmp(string_get(doc1->c), string_get(doc2->c)) < 0)
            return -1;
        else
            return 1;
    }
}

String *document_get_name(Document *d){
    return d->c;
}

void sort_documents_by_pagerank(Document **d, int size){
    if(size != 0 && d){
        qsort(d, size, sizeof(Document*), compare_pagerank);
    }
}