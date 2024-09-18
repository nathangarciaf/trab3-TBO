#include "reader.h"
#include <sys/types.h>
#include <stdlib.h>
#include "string.h"
#include <string.h>

TST *read_dir_files(TST *t, TST *stopwords, char *dir, Index* i, FILE *index){
    char *dir_buffer = NULL;
    size_t dir_len = 0;
    int nread = 0;

    while ((nread = getline(&dir_buffer, &dir_len, index)) != -1) {
        int buffer_len = strlen(dir_buffer);
        if( dir_buffer[buffer_len - 1] == '\n') { dir_buffer[buffer_len - 1] = '\0'; }

        String *buffer_str = string_create(dir_buffer);
        Document *d = document_init(buffer_str);
        index_insert_document(i,d);

        int path_len = strlen(dir) + strlen(dir_buffer) + 2;
        char *path = (char*)calloc(path_len, sizeof(char));
        strcpy(path, dir);
        strcat(path, "/");
        strcat(path, dir_buffer);

        FILE *f = fopen(path,"r");
        if(!f){
            printf("Arquivo %s inexistente\n", path);
            exit(1);
        }

        char *buffer = NULL;
        size_t len = 0;

        while ((nread = getline(&buffer, &len, f)) != -1) {
            char *str = strtok(buffer, " \n");

            while (str != NULL) {
                String *s = string_create(str);
                Value *val = TST_search(stopwords, s);
                
                if(!val) { 
                    String *value = string_create(dir_buffer);
                    t = TST_insert(t, s, value); 
                }
                    
                str = strtok(NULL, " \n");
                string_free(s);
            }
        }
        free(buffer);
        fclose(f);
        free(path);
    }
    free(dir_buffer);
    return t;
}

TST *read_stopwords(TST *t, FILE *f){
    char *buffer = NULL;
    size_t len = 0;
    int nread = 0;

    while ((nread = getline(&buffer, &len, f)) != -1) {
        String *s = string_create(buffer);
        String *val = string_create("");
        t = TST_insert(t,s, val);
        string_free(s);
    }

    free(buffer);
    return t;
}

void read_graph(Index *i, FILE *f){
    char *buffer = NULL;
    size_t len = 0;
    int nread = 0;

    //printf("\n");

    while ((nread = getline(&buffer, &len, f)) != -1) {
        char *token = strtok(buffer, " \n");
        Document *current_doc = NULL;
        Document *linked_docs = NULL;
        int col = 0;
        while(token){
            //printf("COL: %d\nTOKEN: %s\n\n", col,token);
            int convert = atoi(token);
            if(col == 1){
                //printf("ATOI: %d\n", convert);
                document_alloc_links(current_doc,convert);
            }
            else {
                String *tk = string_create(token);
                linked_docs = document_find(index_get_documents(i), index_get_size(i), tk);
                if(!col){
                    current_doc = linked_docs;
                    //document_print(current_doc);
                }
                else{
                    document_insert_linked(current_doc, linked_docs);
                    document_add_out(linked_docs);
                }
                string_free(tk);
            }
            col++;
            token = strtok(NULL, " \n");
        }
        //printf("\n");
    }
    free(buffer);
    document_report(index_get_documents(i), index_get_size(i));
}