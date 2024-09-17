#include "reader.h"

#define INDEX_ALLOC 8
#define INDEX_LINE_LENGTH 128

struct index {
    char **docs;
    int size, alloc;
};

TST *read_pages(TST *t, TST *stopwords, char *dir, Index *idx){
    char *buffer = NULL;
    size_t len = 0;
    int nread = 0;

    for(int i = 0; i < idx->size; i++){
        int path_len = strlen(dir) + strlen(idx->docs[i]) + 2;
        char *path = (char*)calloc(path_len, sizeof(char));
        strcpy(path, dir);
        strcat(path, "/");
        strcat(path, idx->docs[i]);
        
        FILE *f = fopen(path,"r");
        if(!f){
            printf("Arquivo %s inexistente\n", path);
            exit(1);
        }

        while ((nread = getline(&buffer, &len, f)) != -1) {
            char *str = strtok(buffer, " \n");

            while (str != NULL) {
                printf("TOKEN: %s\n", str);
                String *s = string_create(str);
                t = TST_insert(t, s, 1);
                str = strtok(NULL, " \n");
                string_free(s);
            }
            //String *s = string_create(buffer);
            //printf("%s\n", buffer);
            //t = TST_insert(t,str, 1);
        }
        fclose(f);
        free(path);
    }

    free(buffer);
    return t;
}

TST *read_file(TST *t, FILE *f){
    char *buffer = NULL;
    size_t len = 0;
    int nread = 0;

    while ((nread = getline(&buffer, &len, f)) != -1) {
        String *s = string_create(buffer);
        t = TST_insert(t,s, 1);
        string_free(s);
    }

    free(buffer);
    return t;
}

Index *index_init(){
    Index *i = (Index*)calloc(1,sizeof(Index));
    i->docs = (char**)calloc(INDEX_ALLOC, sizeof(char*));
    i->size = 0;
    i->alloc = INDEX_ALLOC;
    return i;
}

void index_read(Index *i, FILE *f){
    char *buffer = NULL;
    size_t len = 0;
    int nread = 0;

    while ((nread = getline(&buffer, &len, f)) != -1) {
        if (i->size == i->alloc) {
            i->alloc *= 2;
            i->docs = (char**)realloc(i->docs, i->alloc * sizeof(char*));
        }

        i->docs[i->size] = (char*)calloc((nread + 1), sizeof(char));
        
        //\n
        int buffer_len = strlen(buffer);
        buffer[buffer_len - 1] = '\0'; 
        strcpy(i->docs[i->size], buffer);    
        i->size++;
    }

    free(buffer);
}

void print_index(Index *index){
    for(int i =0; i < index->size; i++){
        printf("STR %d: %s\n", i, index->docs[i]);
    }
}

void index_free(Index *index){
    for(int i = 0; i < index->size; i++){
        free(index->docs[i]);
    }
    free(index->docs);
    free(index);
}