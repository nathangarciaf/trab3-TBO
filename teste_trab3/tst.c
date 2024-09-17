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

int compare_from(String *s, String *t, int d) {
    int min = s->len < t->len ? s->len : t->len;
    for (int i = d; i < min; i++) {
        if (s->c[i] < t->c[i]) { return -1; }
        if (s->c[i] > t->c[i]) { return 1; }
    }
    return s->len - t->len;
}


void string_free(String *s){
    free(s->c);
    free(s);
}

TST *create_node(){
    TST *t = (TST*)calloc(1, sizeof(TST));
    t->l = t->r = t->m = NULL;
    t->val = NULL;
    t->c = '\0';
    return t;
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
        Value_insert(t->val, val);
        
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

Value *val_init(){
    Value *v = (Value*)calloc(1,sizeof(Value));
    v->alloc = 2;
    v->files = (String**)calloc(v->alloc, sizeof(String*));
    v->size = 0;
    return v;
}

void Value_insert(Value *v, String *s){
    if(v->alloc == v->size){
        v->alloc *= 2;
        v->files = (String**)realloc(v->files, v->alloc * sizeof(String*));
    }
    v->files[v->size] = s;
    v->size++;
}

Value *intersect_val(Value *commom, Value *v){
    if(!commom){
        commom = val_init();
        //printf("SIZE V: %d\n", v->size);
        for(int i = 0; i < v->size; i++){
            Value_insert(commom, v->files[i]);
            //printf("string atual: %s\n", commom->files[i]->c);
        }
    }
    else{
        Value *result = val_init();
        for(int i = 0; i < commom->size; i++){
            for(int j = 0; j < v->size; j++){
                //printf("STR 1:%s\nSTR 2: %s\n", commom->files[i]->c, v->files[j]->c);
                if(!compare_from(commom->files[i], v->files[j], 0)){
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

void print_results(char *s, Value *v){
    printf("search:%s\n", s);
    printf("pages:");
    print_val(v);
    printf("\n");
    printf("pr:");
    printf("\n");
}

void print_val(Value *v){
    if(!v)
        return;
    String **s = v->files;
    for (int i = 0; i < v->size; i++){
        printf("%s ", s[i]->c);
    }
}

void Value_free_reduced(Value *v){
    if(v){ free(v->files); free(v); } 
}

void Value_free(Value *v){
    for(int i = 0; i < v->size; i++){
        string_free(v->files[i]);
    }
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

