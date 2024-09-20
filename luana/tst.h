#ifndef TST_H
#define TST_H

#include "string.h"
#include "document.h"

#define VAL_DEFAULT_ALLOC 2

typedef struct value Value;
typedef struct node TST;

TST *create_node();

TST* rec_insert(TST* t, String* key, Document* val, int d);
TST* TST_insert(TST* t, String* key , Document* val);

TST* rec_search(TST* t, String* key, int d);
Value *TST_search(TST* t, String* key);

Value *Value_init();
Value *intersect_val(Value *commom, Value *v);
void Value_insert(Value *v, Document *s);
void Value_print(Value *v);
void Value_print_pagerank(Value *v);
void TST_free(TST *t);
void Value_free_reduced(Value *v);
void Value_free(Value *v);
Document ** Value_get_files(Value *v);
int Value_get_size(Value *v);

#endif