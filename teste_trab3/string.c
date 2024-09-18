#include "string.h"

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

    s->c = (char*)calloc((len + 1), sizeof(char));
    strcpy(s->c, str);

    for(int i = 0; i < len; i++){
        if(isupper(s->c[i]))
            s->c[i] = tolower(s->c[i]);
    }
    s->len = len;

    return s;
}

void string_array_print(String **s, int size){
    for(int i = 0; i < size; i++){
        printf("%s ", s[i]->c);
    }
}

void string_print(String *s){
    printf("STRING: %s\n", s->c);
}

char string_get_char(String *s, int d){
    return s->c[d];
}

int string_len(String *s){
    return s->len;
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