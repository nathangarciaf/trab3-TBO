#include "tst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct string {
    char *c;
    int len;
};

struct value {
    String **files;
    int size,alloc;
};

struct node {
    Value *val;
    unsigned char c;
    TST *l, *m, *r;
};

String *string_create(char *str) {
    String *s = (String*)calloc(1, sizeof(String));
    int len = strlen(str);

    if ((len > 0 && str[len - 1] == '\n') || (len > 0 && str[len - 1] == '\t') ) {
        str[len - 1] = '\0';
        len--; 
    }

    s->c = (char*)calloc((len + 1), sizeof(char));
    strcpy(s->c, str);

    for(int i = 0; i < len; i++){
        if(isupper(s->c[i]))
            s->c[i] = tolower(s->c[i]);
    }
    s->len = len;

    return s;
}

void string_free(String *s){
    free(s->c);
    free(s);
}

Value *val_init(){
    Value *v = (Value*)calloc(1,sizeof(Value));
    v->alloc = 2;
    v->files = (String**)calloc(v->alloc, sizeof(String*));
    v->size = 0;
    return v;
}

TST *create_node(){
    TST *t = (TST*)calloc(1, sizeof(TST));
    t->l = t->r = t->m = NULL;
    t->val = NULL;
    t->c = '\0';
    return t;
}

void TST_add_value(TST *t, String *val){
    Value *v = t->val;
    if(v->alloc == v->size){
        v->alloc *= 2;
        v->files = (String**)realloc(v->files, v->alloc * sizeof(String*) ) ;
    }
    v->files[v->size] = val;
    v->size++;
}

TST* rec_insert(TST* t, String* key, String* val, int d) {
    unsigned char c = key->c[d];
    if (t == NULL) { t = create_node(); t->c = c;}
    if (c < t->c) {  t->l = rec_insert(t->l, key, val, d); }
    else if (c > t->c) { t->r = rec_insert(t->r, key, val, d); }

    else if (d < key->len - 1) {
        t->m = rec_insert(t->m, key, val, d+1);
    } 
    else {
        if(!t->val)
            t->val = val_init();
        TST_add_value(t, val);
        
    }
    return t;
}

TST* TST_insert(TST* t, String* key , String* val) {
    return rec_insert(t, key, val, 0);
}

TST* rec_search(TST* t, String* key, int d) {
    if (t == NULL) { return NULL; }
    unsigned char c = key->c[d];

    if (c < t->c) { return rec_search(t->l, key, d); }
    else if (c > t->c) { return rec_search(t->r, key, d); }
    else if (d < key->len - 1) {
        return rec_search(t->m, key, d+1);
    } 
    else { return t; }
}

Value *TST_search(TST* t, String* key) {
    t = rec_search(t, key, 0);
    if (t == NULL) { return 0; }
    else { return t->val; }
}

void val_free(Value *v){
    for(int i = 0; i < v->size; i++){
        string_free(v->files[i]);
    }
    free(v->files);
    free(v);
}

void print_val(Value *v){
    String **s = v->files;
    for (int i = 0; i < v->size; i++){
        printf("ARQUIVO: %s\n", s[i]->c);
    }
    return;
}

void TST_free(TST *t){
    if(t == NULL) { return; }
    TST_free(t->l);
    TST_free(t->m);
    TST_free(t->r);

    if(t->val)
        val_free(t->val);
    free(t);
}

