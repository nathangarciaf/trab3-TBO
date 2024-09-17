#include "reader.h"

TST *read_dir_files(TST *t, TST *stopwords, char *dir, FILE *index){
    char *dir_buffer = NULL;
    size_t dir_len = 0;
    int nread = 0;

    while ((nread = getline(&dir_buffer, &dir_len, index)) != -1) {
        //\n
        int buffer_len = strlen(dir_buffer);
        dir_buffer[buffer_len - 1] = '\0'; 
        //printf("BUFFER: %s\n", buffer);

        int path_len = strlen(dir) + strlen(dir_buffer) + 2;
        char *path = (char*)calloc(path_len, sizeof(char));
        strcpy(path, dir);
        strcat(path, "/");
        strcat(path, dir_buffer);
        //printf("PATH: %s\n", path);

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
            //String *s = string_create(buffer);
            //printf("%s\n", buffer);
            //t = TST_insert(t,str, 1);
        }
        free(buffer);
        fclose(f);
        free(path);
    }
    free(dir_buffer);
    return t;
}

TST *read_file(TST *t, FILE *f){
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