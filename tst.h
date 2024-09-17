#ifndef TST_H
#define TST_H

#define VAL_DEFAULT_ALLOC 2

typedef struct value ValueV;

typedef struct string String;
typedef int Value;
typedef struct node TST;

String *string_create(char *str);
void string_free(String *s);

TST *create_node();

TST* rec_insert(TST* t, String* key, Value val, int d);
TST* TST_insert(TST* t, String* key , Value val);

TST* rec_search(TST* t, String* key, int d);
Value TST_search(TST* t, String* key);

void TST_free(TST *t);

#endif