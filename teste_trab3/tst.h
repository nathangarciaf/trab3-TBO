#ifndef TST_H
#define TST_H

#define VAL_DEFAULT_ALLOC 2

typedef struct value Value;
typedef struct string String;
typedef struct node TST;

String *string_create(char *str);
int compare_from(String *s, String *t, int d);
void string_free(String *s);

TST *create_node();

TST* rec_insert(TST* t, String* key, String* val, int d);
TST* TST_insert(TST* t, String* key , String* val);

TST* rec_search(TST* t, String* key, int d);
Value *TST_search(TST* t, String* key);

Value *val_init();
Value *intersect_val(Value *commom, Value *v);
void Value_insert(Value *v, String *s);
void print_val(Value *v);
void TST_free(TST *t);
void Value_free_reduced(Value *v);
void Value_free(Value *v);
void print_results(char *s, Value *v);

#endif