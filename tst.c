#include "tst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct string {
    char *c;
    int len;
};

String *string_create(char *str) {
    String *s = (String*)calloc(1, sizeof(String));
    int len = strlen(str);

    if ((len > 0 && str[len - 1] == '\n') || (len > 0 && str[len - 1] == '\t') ) {
        str[len - 1] = '\0';
        len--; 
    }
    for(int i = 0; i < len; i++){
        if(isupper(str[i]))
            str[i] = tolower(str[i]);
    }
    s->c = (char*)calloc((len + 1), sizeof(char));
    strcpy(s->c, str);
    s->len = len;

    return s;
}

void string_free(String *s){
    free(s->c);
    free(s);
}

struct node {
    Value val;
    unsigned char c;
    TST *l, *m, *r;
};

TST *create_node(){
    TST *t = (TST*)calloc(1, sizeof(TST));
    t->l = t->r = t->m = NULL;
    t->val = 0;
    t->c = '\0';
    return t;
}

TST* rec_insert(TST* t, String* key, Value val, int d) {
    unsigned char c = key->c[d];
    if (t == NULL) { t = create_node(); t->c = c;}
    if (c < t->c) {  t->l = rec_insert(t->l, key, val, d); }
    else if (c > t->c) { t->r = rec_insert(t->r, key, val, d); }

    else if (d < key->len - 1) {
        t->m = rec_insert(t->m, key, val, d+1);
    } 
    else {
        if( t->val)
            t->val++;
        else
            t->val = val; 
    }
    return t;
}

TST* TST_insert(TST* t, String* key , Value val) {
    return rec_insert(t, key, val, 0);
}

TST* rec_search(TST* t, String* key, int d) {
    if (t == NULL) { return NULL; }
    unsigned char c = key->c[d];
    /*printf("CARAC ATUAL: %c\n", c);
    printf("TAMANHO DA CHAVE: %d\n", key->len);
    printf("VAL ATUAL: %d\n", t->val);
    printf("IDX ATUAL: %d\n\n", d);*/

    if (c < t->c) { return rec_search(t->l, key, d); }
    else if (c > t->c) { return rec_search(t->r, key, d); }
    else if (d < key->len - 1) {
        return rec_search(t->m, key, d+1);
    } 
    else { return t; }
}

Value TST_search(TST* t, String* key) {
    t = rec_search(t, key, 0);
    if (t == NULL) { return 0; }
    else { return t->val; }
}

void TST_free(TST *t){
    if(t == NULL) { return; }
    TST_free(t->l);
    TST_free(t->m);
    TST_free(t->r);
    free(t);
}

