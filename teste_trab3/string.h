#ifndef STR_H
#define STR_H

typedef struct string String;

String *string_create(char *str);
int compare_from(String *s, String *t, int d);
void string_free(String *s);
char string_get_char(String *s, int d);
int string_len(String *s);
void string_print(String **s, int size);

#endif