#include "tst.h"
#include "string.h"

#include <stdio.h>
#include <stdlib.h>

struct value {
    Document **files;
    int size,alloc;
};

struct node {
    Value *val;
    unsigned char c;
    TST *l, *m, *r;
};

TST *create_node(){
    TST *t = (TST*)calloc(1, sizeof(TST));
    t->l = t->r = t->m = NULL;
    t->val = NULL;
    t->c = '\0';
    return t;
}

TST* rec_insert(TST* t, String* key, Document* val, int d) {
    unsigned char c = string_get_char(key, d);
    if (t == NULL) { t = create_node(); t->c = c;}
    if (c < t->c) {  t->l = rec_insert(t->l, key, val, d); }
    else if (c > t->c) { t->r = rec_insert(t->r, key, val, d); }

    else if (d < string_len(key) - 1) {
        t->m = rec_insert(t->m, key, val, d+1);
    } 
    else {
        if(!t->val)
            t->val = Value_init();
        Value_insert(t->val, val);
        
    }
    return t;
}

TST* TST_insert(TST* t, String* key , Document* val) {
    return rec_insert(t, key, val, 0);
}

TST* rec_search(TST* t, String* key, int d) {
    if (t == NULL) { return NULL; }
    unsigned char c = string_get_char(key, d);

    if (c < t->c) { return rec_search(t->l, key, d); }
    else if (c > t->c) { return rec_search(t->r, key, d); }
    else if (d < string_len(key) - 1) {
        return rec_search(t->m, key, d+1);
    } 
    else { return t; }
}

Value *TST_search(TST* t, String* key) {
    t = rec_search(t, key, 0);
    if (t == NULL) { return 0; }
    else { return t->val; }
}

Value *Value_init(){
    Value *v = (Value*)calloc(1,sizeof(Value));
    v->alloc = 2;
    v->files = (Document**)calloc(v->alloc, sizeof(Document*));
    v->size = 0;
    return v;
}

void Value_insert(Value *v, Document *s){
    if(v->alloc == v->size){
        v->alloc *= 2;
        v->files = (Document**)realloc(v->files, v->alloc * sizeof(Document*));
    }
    v->files[v->size] = s;
    v->size++;
}

Value *intersect_val(Value *commom, Value *v){
    if(!commom){
        commom = Value_init();
        //printf("SIZE V: %d\n", v->size);
        for(int i = 0; i < v->size; i++){
            Value_insert(commom, v->files[i]);
            //printf("string atual: %s\n", commom->files[i]->c);
        }
    }
    else{
        Value *result = Value_init();
        for(int i = 0; i < commom->size; i++){
            for(int j = 0; j < v->size; j++){
                //printf("STR 1:%s\nSTR 2: %s\n", commom->files[i]->c, v->files[j]->c);
                if(!compare_from(document_get_name(commom->files[i]), document_get_name(v->files[j]), 0)){
                    Value_insert(result, commom->files[i]);
                    break;
                }
            }
        }
        Value_free_reduced(commom);
        return result;
    }

    return commom;
}

void Value_print(Value *v){
    if(!v)
        return;

    Document **d = v->files;
    int size = v->size;

    sort_documents_by_pagerank(d, size);

    for(int i = 0; i < size; i++){
        document_print(d[i]);
    }
}

void Value_print_pagerank(Value *v){
    if(!v)
        return;

    Document **d = v->files;
    int size = v->size;

    for(int i = 0; i < size; i++){
        document_print_pagerank(d[i]);
    }
}

void Value_free_reduced(Value *v){
    if(v){ free(v->files); free(v); } 
}

void Value_free(Value *v){
    free(v->files);
    free(v);
}

void TST_free(TST *t){
    if(t == NULL) { return; }
    TST_free(t->l);
    TST_free(t->m);
    TST_free(t->r);

    if(t->val)
        Value_free(t->val);
    free(t);
}

Document ** Value_get_files(Value *v){
    return v->files;
}

int Value_get_size(Value *v){
    return v->size;
}